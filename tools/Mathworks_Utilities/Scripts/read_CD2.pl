#!/usr/bin/perl -w
use strict;
use DBI;
use Config;

#parameters
my $output_file_h = 'cdata.h';
my $output_file_c = 'cdata.c';
my $output_file_m = 'cdata.m';
my $output_file_a = 'ap_cdata.cpp';
my $machine_default_col_name = undef;
my $machine_data_col_name = undef;
my $use_num_suffix = 0;
my $main_table_name_default = 'cdata';
my @main_table_names;
my $check_database_timestamp = 0;
my $use_header_timestamp = 0;
my $target_compiler = 'metrowerks';
my %suppressed_warnings;
my $struct_max_gap = -1; #maximum gap between consecutive symbols before a struct will be split in two
my %metrowerks_near_tables;
#my %tasking_near_tables;
#my $global_address_offset_active = 0;
#my $global_address_offset        = 0;
my $cd_alias = 0;
my $cd_pointer = 0;
my $gen_ap_cdata = 0;
my $rel_offset = 0;

#main table column ids being used
my $machine_default_col = undef;
my $machine_data_col = undef;

my $exec_name = $0;              #name of this executable
$exec_name =~ s{^.*(\\|/)}{};

my $usage = "
Generates the C, H, and M files necessary for linking application code with
an SADB database.

usage: $exec_name [<flags>] <SADB file> <main table name>
  -a <name>,<address> set the struct/array <name>'s address here, ignore
     address in database, remove far qualifier (metrowerks only)
#  -e <offset> set the address of all structs/arrays relative to this offset,
#     remove far qualifier (metrowerks only)
#  -b <bytes> Break structures in two if the gap between consecutive symbols
#     exceeds <bytes>.
  -d <default column name> use this default column in the machine table.
     If not specified, the first default column is used.
#  -f <name>,<class> wrap the struct/array <name> in '#pragma class nc=<class>'
#     instead of using the _at() qualifier, declare it as _near (tasking only)
  -m <machine column name> use this machine table column.  If not specified,
     only the default column will be used.
  -n add a number suffix to variables that appear in a table more than once
  -o <output h file name> use this output file name (default cdata.h)
  -p <output c file name> use this output file name (default cdata.c)
  -q <output m file name> use this output file name (default cdata.m)
  -r <name> use this main table name in generated code (default cdata)
     Note: when using -b, <name> may be a comma-separated list.
  -t add a time stamp to the output file headers
  -A use a matlab alias for constant data main table variables that prepends 'CD_'
  -C skip build if database time stamp has not changed (generates *.make file)
  -I generate C code for the IAR compiler/M4 processor
  -G generate C code that will work with GCC, no addresses
  -P pointer access to constant data - custom storage class ConstantDataPointer
  -R use relative offset 
#  -T generate C code for the tasking compiler (default is for metrowerks)
  -W <warning num list> ignore these warning numbers (ex: -W 4,1,2)

  note: lists of arguments must be separated by commas, with no spaces.

* Sub-tables will be imported as arrays if their members are of uniform size,
  and as structures otherwise.
* The machine table will always be imported as a structure.
* Byte arrays will be inserted into any gaps found in structures.
* If a link table name is preceded by the machine's name, the machine's name
  will be omitted from the symbol name in the output files.

Warnings:
   1   could not open <file>.make
   4   <name> in <struct/array> overlaps <name> in <struct/array> at address
       <address>
  10   table <name> is being removed because it has no rows
  21   the elements of array <name> are misaligned (starts with element <num>)
  23   element <num> of array <name> has no value
  25   table <name> is missing default data at row <name> (address <address>)
  31   symbol <name> in struct <name> occurs more than once
  32   symbol <name> is being removed because it overlaps previous symbol
       <name> in struct <name>
  34   symbol <name> in struct <name> has no value
  36   symbol <name> in struct <name> (<num> bytes) occurs at an odd
       address
";

#check arguments
while(@ARGV && $ARGV[0] =~ m/^-([A-Za-z]+)$/){
  my $flags = $1;
  shift @ARGV; #remove flags token from args array
  foreach(split(//, $flags)){
    
    if($_ eq 'h'){
      print $usage;
      exit(0);
 #   }elsif($_ eq 'b'){
 #     $struct_max_gap = shift @ARGV;
    }elsif($_ eq 'o'){
      $output_file_h = shift @ARGV;
    }elsif($_ eq 'p'){
      $output_file_c = shift @ARGV;
    }elsif($_ eq 'q'){
      $output_file_m = shift @ARGV;
    }elsif($_ eq 's'){
      $output_file_a = shift @ARGV;
      $gen_ap_cdata = 1;
    }elsif($_ eq 'r'){
      push( @main_table_names, split( /,/, shift(@ARGV) ) );
    }elsif($_ eq 't'){
      $use_header_timestamp = 1;
    }elsif($_ eq 'd'){
      $machine_default_col_name = shift @ARGV;
    }elsif($_ eq 'm'){
      $machine_data_col_name = shift @ARGV;
    }elsif($_ eq 'R'){
      $rel_offset = shift @ARGV;
    }elsif($_ eq 'n'){
      $use_num_suffix = 1;
    }elsif($_ eq 'C'){
      $check_database_timestamp = 1;
    }elsif($_ eq 'A'){
      $cd_alias = 1;
    }elsif($_ eq 'a'){
      my @list = split( /,/, shift(@ARGV) );
      if(@list == 2){
        $metrowerks_near_tables{$list[0]} = $list[1];
      }else{
        print STDERR "\nError: wrong number of arguments to option -a\n";
        exit(1);
      }
 #   }elsif($_ eq 'e'){
 #     $global_address_offset_active = 1;
 #     $global_address_offset = shift @ARGV;
 #   }elsif($_ eq 'T'){
 #     $target_compiler = 'tasking';
    }elsif($_ eq 'I'){
      $target_compiler = 'iar';
    }elsif($_ eq 'G'){
      $target_compiler = 'gcc';
    }elsif($_ eq 'P'){
      $cd_pointer = 1;
#    }elsif($_ eq 'f'){
#      my @list = split( /,/, shift(@ARGV) );
#      if(@list == 2){
#        $tasking_near_tables{$list[0]} = $list[1];
#      }else{
#        print STDERR "\nError: wrong number of arguments to option -f\n";
#        exit(1);
#      }
    }elsif($_ eq 'W'){
      my @ignore_list = split( /,/, shift(@ARGV) );
      foreach(@ignore_list){
        $suppressed_warnings{$_}++;
      }
    }else{
      print STDERR "\nError: unknown flag '$_'\n";
      exit(1);
    }
  }
}

#set the main table name to its default value if it was not supplied by the user
if( @main_table_names <= 0){  @main_table_names = ($main_table_name_default) };

if(@ARGV < 2 ){ #no input file or key
  print STDERR "\nError: missing required arguments\n";
  exit(-1);
}

my ($database_file, $db_key) = @ARGV;

my @file_stats = stat($database_file);
my $last_modified = $file_stats[9];

#we'd better be able to read from the database file
( -r $database_file ) or die "\nError: couldn't read $database_file.\n";

#abort run if the database has not changed
if( $check_database_timestamp && defined($last_modified) ){
  if(-e "$database_file.make"){
    if( open( TSTAMP, "<$database_file.make" ) ){
      my $last_build_mtime = <TSTAMP>;
      if(
        defined ($last_build_mtime)
        && $last_build_mtime =~ m/^[0-9]+$/
        && $last_modified == $last_build_mtime
      ){
        #keep going if somebody has deleted the output files
        if( (-e $output_file_h) && (-e $output_file_c) && (-e $output_file_m) ){
          print "Skipping build: database file is unchanged.\n";
          exit(0);
        }
      }
    }else{
      #warning message will be printed below...
    }
    close(TSTAMP);
  }
}

#check the read/write permissions on all the output files before overwriting any of them
( -w $output_file_h || !-e $output_file_h ) or die "\nError: couldn't write to $output_file_h.\n";
( -w $output_file_c || !-e $output_file_c ) or die "\nError: couldn't write to $output_file_c.\n";
( -w $output_file_m || !-e $output_file_m ) or die "\nError: couldn't write to $output_file_m.\n";
( -w $output_file_a || !-e $output_file_a ) or die "\nError: couldn't write to $output_file_a.\n";

if($check_database_timestamp){
  #store datbase time stamp for this run
  if( open( TSTAMP, ">$database_file.make" ) ){
    print TSTAMP "$last_modified";
  }else{
    warning(1, "could not open $database_file.make: $!");  
  }
  close(TSTAMP);
}


#open database and output files
my $database = open_db($database_file);

open( OFH, ">$output_file_h" ) or die "\nError: couldn't open $output_file_h: $!\n";
open( OFM, ">$output_file_m" ) or die "\nError: couldn't open $output_file_m: $!\n";
open( OFC, ">$output_file_c" ) or die "\nError: couldn't open $output_file_c: $!\n";

if($gen_ap_cdata){
    open( OFA, ">$output_file_a" ) or die "\nError: couldn't open $output_file_a: $!\n";
}

#resolve the data and default columns
if( defined $machine_default_col_name ){
  $machine_default_col = get_break_id_by_name( $database, $machine_default_col_name )
}else{
  $machine_default_col = get_default_break( $database )
}
if( defined $machine_data_col_name ){
  $machine_data_col = get_break_id_by_name( $database, $machine_data_col_name )
}

#build a macro name for the c header file boilerplate
my $guard_macro = uc($output_file_h);
$guard_macro =~ s{^.*(\\|/)}{};
$guard_macro =~ s{[^A-Za-z0-9_]}{_};
$guard_macro = "_".$guard_macro."_";


my $timestamp = "";
if($use_header_timestamp){
  my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime(time);
  $year+=1900;
  $timestamp = "Built on: $year/$mon/$mday $hour:$min";
}

my $c_boilerplate = 
"/*****************************************************************************\\
This module defines the constant data structures available in the database.

This file is auto-generated by $exec_name.
$timestamp
Built from:
  $database_file
  key: $db_key
\\*****************************************************************************/";

my $m_boilerplate = 
"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%This module defines the constant data structures available in the database.
%
%This file is auto-generated by $exec_name.
%$timestamp
%Built from:
%  $database_file
%  key: $db_key
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";

my $a_boilerplate = 
"/*****************************************************************************\\
%This module maps the constant data structures available in the database.
%
%This file is auto-generated by $exec_name.
%$timestamp
%Built from:
%  $database_file
%  key: $db_key
\\*****************************************************************************/
#include \"stdint.h\"
#include \<stddef.h\>
#include \"ap_cdata.h\"
#include \"cdata.h\"
#include \"bsp_rom.h\"
#include \"bsp_ecuid.h\"

/// Number of 32bit words per section record
#define CD_SECT_RCRD_LEN            (2)
/// Index of RESERVED_0
#define CD_INDEX_RESERVED_0         (0)
///Index of NUMSECTIONS
#define CD_INDEX_NUMSECTIONS        (1)
/// Index of first Section ID
#define CD_INDEX_FIRST_ID           (2)
/// Index of First Section Offset
#define CD_INDEX_FIRST_OFFSET       (3)
/// Index of First Section Size
#define CD_INDEX_SECT_ID(s)         (CD_INDEX_FIRST_ID + ((s) * CD_SECT_RCRD_LEN))
/// Index of specific Section Offset
#define CD_INDEX_SECT_OFFSET(s)     (CD_INDEX_FIRST_OFFSET + ((s) * CD_SECT_RCRD_LEN))

#define CD_SID_CDATA                (0)
#define CD_SID(l)                   (offsetof(CONSTANT_DATA_t, l))

//******************************************************************************
// Static Function Prototypes
//******************************************************************************
static void const * getCDSection(uint32_t sectionID);


//******************************************************************************
// Static Variables
//******************************************************************************
static uintptr_t cdataAddress = 0;


//******************************************************************************
// Global Variables
//******************************************************************************";

my $a_footer1 = 
"\n//******************************************************************************
// External Function Definitions
//******************************************************************************

//******************************************************************************
void ap_cdata_init(void)
{
  cdataAddress = bsp_rom_getStartAddr(bsp_ecuid->ap_sw_const_smask);

  // CONSTANT_DATA is always section ID 0
  CONSTANT_DATA = (CONSTANT_DATA_t const *)getCDSection(CD_SID_CDATA);

  // The remaining table sections IDs are determined the location of their reference in the CONSTANT_DATA structure";

my $a_footer2 =
"}


//******************************************************************************
// Static Function Definitions
//******************************************************************************

//******************************************************************************
/**
 * Get a pointer to a section of cdata
 *
 * param sectionID ID of requested cdata section
 *
 * return void const* pointer to cdata section
 ******************************************************************************/
static void const * getCDSection(uint32_t sectionID)
{
  void const *sectionLoc = NULL;
  uint32_t const * map = (uint32_t *)cdataAddress;

  if (map && map[CD_INDEX_RESERVED_0] == 0)
  {
    uint32_t sectIndex;
    uint32_t numSections = map[CD_INDEX_NUMSECTIONS];

    // Try to find matching ID
    for (sectIndex = 0; sectIndex < numSections; sectIndex++)
    {
      if (map[CD_INDEX_SECT_ID(sectIndex)] == sectionID)
      {
        // The section is in cdata at the offset indicated in the cdataMap
        uintptr_t tempSectLoc = cdataAddress;
        tempSectLoc += map[CD_INDEX_SECT_OFFSET(sectIndex)];
        sectionLoc = (void const *)tempSectLoc;
        break;
      }
    }
  }

  return sectionLoc;
}";



print OFH 
"#ifndef $guard_macro
#define $guard_macro

$c_boilerplate

#include \"stdint.h\"
";

my $output_file_h_short_name = $output_file_h; #strip path from file name
$output_file_h_short_name =~ s{^.*(\\|/)}{};

print OFC 
"$c_boilerplate

#include \"$output_file_h_short_name\"
";

print OFM "$m_boilerplate\n";
if($gen_ap_cdata){
    print OFA "$a_boilerplate\n";
}
print_main_table($database);
print_link_tables($database);

if($gen_ap_cdata){
    print_map_tables($database);
}

print OFH "\n#endif //#ifndef $guard_macro\n";

if($gen_ap_cdata &&($target_compiler eq 'iar')){
    print OFA "$a_footer1\n";
    print_subtable_links($database);
    print OFA "$a_footer2\n";
}
if($target_compiler eq 'iar'){
        print OFC "\n#pragma location=\".checksum\"\n";
        print OFC "__root uint32_t const __checksum;";
    }




print STDOUT "Done.\n";

#################
## subroutines ##
#################

sub open_db{
#
# opens the database file
# params:
#    $filename - database file name
# returns:
#    the database connection
#
  my ($filename) = @_;
  (-r $filename) or die "\nError: couldn't read from $filename: $!\n";

  my $dbh = DBI->connect("dbi:SQLite:dbname=$filename")
    or die "Could not open database file $filename: " . DBI->errstr;
  return $dbh;
}


sub print_main_table{
#
# Generates the main (machine table) structure
#
  print STDOUT "Generating $db_key machine table...\n";
  
  my @maintable_data = get_maintable_data( $database, $db_key, $machine_default_col, $machine_data_col );
  my ($table_names, $addresses, $members, $data, $matlab ) = generate_typedef_struct(\@maintable_data, @main_table_names);
  
  my $table_name;
  while($table_name = pop @$table_names){
    print OFH "\ntypedef struct ${table_name}_s{\n";
    pretty_print(\*OFH, pop @$members );
    print OFH "}${table_name}_t;\n";

#    if($target_compiler eq 'tasking'){
#      if( exists $tasking_near_tables{$table_name} ){
#        print OFH "_near extern const ${table_name}_t $table_name;\n";
#        print OFC "\n#pragma class nc=" . $tasking_near_tables{$table_name} . "\n";
#        print OFC "_near const ${table_name}_t $table_name = {\n";
#        pretty_print(\*OFC, pop @$data);
#        print OFC "};\n";
#        print OFC "#pragma default_attributes\n";
#        pop(@$addresses); #discard unused address
#      }else{
#        print OFH "_far extern const ${table_name}_t $table_name;\n";
#        if($rel_offset){
#  my $offset_address = add_address_offset(pop(@$addresses), $rel_offset);
#print OFC "\n_fart const ${table_name}_t $table_name _at(".$offset_address.") = {\n";
#        }else{
#          print OFC "\n_farty const ${table_name}_t $table_name _at(". pop(@$addresses).") = {\n";
#        }
#        pretty_print(\*OFC, pop @$data);
#        print OFC "};\n";
#      }

###############    
#IAR - Main table
###############
    if($target_compiler eq 'iar'){
      if($cd_pointer){
        print OFH "\nextern ${table_name}_t const * $table_name;\n";

        if($rel_offset){
          my $offset_address = add_address_offset(pop(@$addresses), $rel_offset);        
          print OFC "\n__root ${table_name}_t const cd_$table_name \@". $offset_address ." = {\n";
        }else{
          print OFC "\n__root ${table_name}_t const cd_$table_name \@". pop(@$addresses) ." = {\n";
        }
        print OFA "${table_name}_t const * $table_name;\n";
      }else{        
        print OFH "\nextern const ${table_name}_t $table_name;\n";
        print OFC "\n${table_name}_t const $table_name \@". pop(@$addresses) ." = {\n";
      }
      
      pretty_print(\*OFC, pop @$data);
      print OFC "};\n"; 

###############    
#GCC - Main table
############### 
    }elsif($target_compiler eq 'gcc'){
      if($cd_pointer){
        print OFC "\n${table_name}_t const cd_$table_name = {\n";
      }else{        
        print OFC "\n${table_name}_t const $table_name = {\n";
      }
      pretty_print(\*OFC, pop @$data);
      print OFC "};\n";
      if($cd_pointer){
        print OFC "\n${table_name}_t const * $table_name = &cd_$table_name;\n";
      }
###############    
#HC12 - Main table
############### 
    }else{
      if( exists $metrowerks_near_tables{$table_name} ){
        if($cd_pointer){
          print OFH "\nextern ${table_name}_t const * $table_name;\n";
          print OFC "\n${table_name}_t const cd_$table_name \@". $metrowerks_near_tables{$table_name} ." = {\n";
        }else{        
          print OFH "\nextern const ${table_name}_t $table_name;\n";
          print OFC "\nconst ${table_name}_t $table_name \@". $metrowerks_near_tables{$table_name} ." = {\n";
        }
        pretty_print(\*OFC, pop @$data);
        print OFC "};\n";
        if($cd_pointer){
          print OFC "\n${table_name}_t const * $table_name = &cd_$table_name;\n";
        }
        pop(@$addresses); #discard unused address
#      }elsif($global_address_offset_active){
#        my $offset_address = remove_address_offset(pop(@$addresses), $global_address_offset);
#        print OFH "extern const ${table_name}_t $table_name;\n";
#        print OFC "\nconst ${table_name}_t $table_name \@". $offset_address ." = {\n";
#        pretty_print(\*OFC, pop @$data);
#        print OFC "};\n";
#      }else{
#        if($cd_pointer){
#          print OFH "\nextern ${table_name}_t const far* $table_name;\n";
#          print OFC "\nconst ${table_name}_t far cd_$table_name \@". pop(@$addresses) ." = {\n";
#        }else{        
#          print OFH "\nextern const ${table_name}_t far $table_name;\n";
#          print OFC "\nconst ${table_name}_t far $table_name \@". pop(@$addresses) ." = {\n";
#        }
#        
#        pretty_print(\*OFC, pop @$data);
#        print OFC "};\n";
#        }
#        
#        pretty_print(\*OFC, pop @$data);
#        print OFC "};\n";
      }
    }

    print OFM "\n";
    pretty_print(\*OFM, pop @$matlab);
  }

}#end main_table


sub print_link_tables{
#
# Generates the link table structures.
#
  #extract the relevant tables from the database
  my $exec_str;

  print STDOUT "Compiling a list of sub-tables for $db_key...\n";
  
  my @subtables = get_subtables($database, $db_key, $machine_default_col, $machine_data_col);

  my $num_of_subtables = @subtables;
  print STDOUT "Generating $num_of_subtables sub-tables...\n";
  
  foreach( my $i=0; $i< @subtables; $i++){
    my $subtable = $subtables[$i];
    my $column = $subtable->{'Column'};

    #print STDOUT "generating $db_key link table '$subtable'\n";

    #tables in the database are usually prefixed by the main table key (redundant for the project)
    $subtable->{'CName'} =~ s{^ $db_key _?}{}x;

    my @table_data = get_subtable_data($database, $subtable->{'CName'}, $subtable->{'ID'}, $subtable->{'Column'});

    #survey the element sizes in the table
    my %num_of_each_size;
    foreach(@table_data){ $num_of_each_size{ $_->{'Type'}->{'bits'} }++; }

    if( keys(%num_of_each_size) != 1 ){
      #the elements of this table are not of uniform size, so represent it as a struct
      my ($table_names, $addresses, $members, $data, $matlab ) = generate_typedef_struct(\@table_data, $subtable->{'CName'});

      my $table_name;
      while($table_name = pop @$table_names){
      
        print OFH "\ntypedef struct ${table_name}_s{\n";
        pretty_print(\*OFH, pop @$members );
        print OFH "}${table_name}_t;\n";

#        if($target_compiler eq 'tasking'){
#          if( exists $tasking_near_tables{$table_name} ){
#            print OFH "_near extern const ${table_name}_t $table_name;\n";
#            print OFC "\n#pragma class nc=" . $tasking_near_tables{$table_name} . "\n";
#            print OFC "_near const ${table_name}_t $table_name = { //column $column\n";
#            pretty_print(\*OFC, pop @$data);
#            print OFC "};\n";
#            print OFC "#pragma default_attributes\n";
#            pop(@$addresses); #discard unused address
#          }else{
#            print OFH "extern const ${table_name}_t $table_name;\n";
#            print OFC "\nconst ${table_name}_t $table_name _at(". pop(@$addresses).") = { //column $column\n";
#            pretty_print(\*OFC, pop @$data);
#            print OFC "};\n";
#          }

###############    
#IAR - Subtables
###############
        if($target_compiler eq 'iar'){
          if($cd_pointer){
            print OFH "extern ${table_name}_t const * $table_name;\n";
            print OFC "\n__root ${table_name}_t const cd_$table_name \@". pop(@$addresses) ." = { //column $column\n";
          }else{        
            print OFH "extern const ${table_name}_t $table_name;\n";
            print OFC "\n${table_name}_t const $table_name \@". pop(@$addresses) ." = { //column $column\n";
          }
          pretty_print(\*OFC, pop @$data);
          print OFC "};\n";

###############    
#GCC - Subtables
###############
        }elsif($target_compiler eq 'gcc'){
          if($cd_pointer){
            print OFC "\n${table_name}_t cd_$table_name = { //column $column\n";
          }else{        
            print OFC "\n${table_name}_t $table_name = { //column $column\n";
          }          
          pretty_print(\*OFC, pop @$data);
          print OFC "};\n";

###############    
#HC12 - Subtables
###############
        }else{
          if( exists $metrowerks_near_tables{$table_name} ){
            print OFH "extern const ${table_name}_t $table_name;\n";
            print OFC "\nconst ${table_name}_t $table_name \@". $metrowerks_near_tables{$table_name} ." = { //column $column\n";
            pretty_print(\*OFC, pop @$data);
            print OFC "};\n";
            pop(@$addresses); #discard unused address
#          }elsif($global_address_offset_active){
#            my $offset_address = remove_address_offset(pop(@$addresses), $global_address_offset);
#            print OFH "extern const ${table_name}_t $table_name;\n";
#            print OFC "\nconst ${table_name}_t $table_name \@". $offset_address ." = { //column $column\n";
#            pretty_print(\*OFC, pop @$data);
#            print OFC "};\n";
          }else{
            if($cd_pointer){
              print OFH "extern ${table_name}_t const far* $table_name;\n";
              print OFC "\n${table_name}_t const far cd_$table_name \@". pop(@$addresses) ." = { //column $column\n";
            }else{        
              print OFH "extern const ${table_name}_t far $table_name;\n";
              print OFC "\nconst ${table_name}_t far $table_name \@". pop(@$addresses) ." = { //column $column\n";
            }            
            
            pretty_print(\*OFC, pop @$data);
            print OFC "};\n";
          }
        }

        print OFM "\n";
        pretty_print(\*OFM, pop @$matlab);
      }
    }elsif( keys(%num_of_each_size) == 1){

      #the elements of this table are all the same size, so represent them as an array
      my $data_type = $table_data[0]->{'Type'};
      my $bytes = $data_type->{'bits'}/8;
      my $table_name = $subtable->{'CName'};

      my $first_address = $table_data[0]->{'MemLoc'};
      if($first_address =~ m/^0[xX]/){ $first_address = hex($first_address); }
      
      #check table memory locations (they should be contiguous)
      my $target_address = $first_address;
      my $table_alignment_warning_issued = 0;
      foreach(my $j=0; $j<@table_data; $j++){
        my $cur_address = $table_data[$j]->{'MemLoc'};

        if(($cur_address != $target_address) && !$table_alignment_warning_issued){
          warning(21, "the elements of array '$table_name' are misaligned (starts with element $j).");
          $table_alignment_warning_issued = 1;
        }
        $target_address += $bytes;
        
        #check data values too...
        my $data = $table_data[$j]->{'Data'};
        if( !defined $data || $data eq '' ){
          warning(23, "element $j of array '$table_name' has no value.");
        }
        
        check_external_object_overlap( "element $j", $table_name, $cur_address, $bytes );
      }

      #print data to c/h files
      my $tmp = $table_name; #guess where to insert underscores in mixed-case size def names
      $tmp =~ s{([A-Z])([A-Z][a-z])}{$1_$2}xg;
      $tmp =~ s{([a-z])([A-Z])}{$1_$2}xg;
      my $size_of = "SIZE_OF_".uc($tmp);
      
      my $addr_str = sprintf( "0x%x", $first_address );
        if($rel_offset){
          $addr_str = add_address_offset($addr_str, $rel_offset); 
        }
      print OFH "\n#define $size_of ".@table_data;

      my $comments = $subtable->{'Notes'};
      if( $data_type->{'fraction'} > 0 ){ #prepend table comments with data type
        $comments = $data_type->{'MATLAB'} .' '. $comments;
      }
      if($comments){
        $comments = ' //' . $comments;
      }else{
        $comments = '';
      }
      
#      if($target_compiler eq 'tasking'){
#        if( exists $tasking_near_tables{$table_name} ){
#          print OFH "\n_near extern const ".$data_type->{'C'}." ".$table_name."[$size_of];$comments\n";
#          print OFC "\n#pragma class nc=" . $tasking_near_tables{$table_name} . "\n";
#          print OFC "_near const ".$data_type->{'C'}." ".$table_name."[$size_of] _at($addr_str) = { //column $column\n";
#          print OFC "#pragma default_attributes\n";
#        }else{
#          print OFH "\nextern const ".$data_type->{'C'}." ".$table_name."[$size_of];$comments\n";
#          print OFC "\nconst ".$data_type->{'C'}." ".$table_name."[$size_of] _at($addr_str) = { //column $column\n";
#        }
      if($target_compiler eq 'iar'){
        if($cd_pointer){
          print OFH "\nextern ".$data_type->{'C'}." const * ".$table_name.";$comments\n";
          print OFC "\n__root ".$data_type->{'C'}." const cd_".$table_name."[] \@$addr_str = { //column $column\n";

      }else{        
          print OFH "\nextern ".$data_type->{'C'}." const ".$table_name."[];$comments\n";
          print OFC "\n".$data_type->{'C'}." const ".$table_name."[] \@$addr_str = { //column $column\n";
        }
        
      }elsif($target_compiler eq 'gcc'){
        if($cd_pointer){
          print OFC "\n".$data_type->{'C'}." const cd_".$table_name."[] = { //column $column\n";
        }else{        
          print OFC "\n".$data_type->{'C'}." const ".$table_name."[] = { //column $column\n";
        }      
      }else{
        if( exists $metrowerks_near_tables{$table_name} ){
          print OFH "\nextern const ".$data_type->{'C'}." ".$table_name."[$size_of];$comments\n";
          print OFC "\nconst ".$data_type->{'C'}." ".$table_name."[$size_of] \@". $metrowerks_near_tables{$table_name} ." = { //column $column\n";
#        }elsif($global_address_offset_active){
#          my $offset_address = remove_address_offset($addr_str, $global_address_offset);        
#          print OFH "\nextern const ".$data_type->{'C'}." ".$table_name."[$size_of];$comments\n";
#          print OFC "\nconst ".$data_type->{'C'}." ".$table_name."[$size_of] \@". $offset_address ." = { //$addr_str column $column\n";
        }else{
          if($cd_pointer){
            print OFH "\nextern ".$data_type->{'C'}." const * far ".$table_name.";$comments\n";
            print OFC "\n".$data_type->{'C'}." const far cd_".$table_name."[] \@$addr_str = { //column $column\n";
          }else{        
            print OFH "\nextern const ".$data_type->{'C'}." far ".$table_name."[$size_of];$comments\n";
            print OFC "\nconst ".$data_type->{'C'}." far ".$table_name."[$size_of] \@$addr_str = { //column $column\n";
          }          
        }
      }

      print OFM "\n$table_name = Bobcat.Parameter; CreateCDTable_basic( $table_name ,'', transpose(".$data_type->{'MATLAB_prefix'}." [...\n";

      my $c_line = "";
      my $m_line = "";
      foreach(@table_data){
        my $cdata = $_->{'Data'};
        my $mdata = sprintf( $data_type->{'MATLAB_format'}, $_->{'Data'} );  
        
        #limit line length to 200 characters
        if(length($c_line) + length("$cdata, ") < 200){
          if($data_type->{'sign'} ){
            $c_line .= "${cdata}, ";
          }else{
            $c_line .= "${cdata}U, ";
          }
        }else{
          print OFC "$c_line \n";
          if($data_type->{'sign'} ){
            $c_line = "${cdata}, ";
          }else{
            $c_line = "${cdata}U, ";
          }
        }

        if(length($m_line) + length("$mdata, ") < 200){
          $m_line .= "$mdata; ";
        }else{
          print OFM "$m_line...\n";
          $m_line = "$mdata; ";
        }
      }
      print OFC "$c_line\n";
      print OFC "};\n";
      if($cd_pointer && ($target_compiler ne 'iar')&& ($target_compiler ne 'gcc')){
        print OFC "\n".$data_type->{'C'}." const * far $table_name = cd_$table_name;\n";
      }
      if($cd_pointer &&($target_compiler eq 'gcc')){
        print OFC "\n".$data_type->{'C'}." const * $table_name = cd_$table_name;\n";
      }
      print OFM "$m_line...\n";
      print OFM "] ".$data_type->{'MATLAB_suffix'}." ));\n";
    }
    else
    {
      warning(10,"table " . $subtable->{'Name'} . " is being removed because it has no rows");
    }
  }
}


sub generate_typedef_struct{
#
# generates a typedefed struct based on the table data passed in
# params:
#    $table_entries      - hash structure returned by get_maintable_data / get_subtable_data
#    @param_struct_names - name(s) to be assigned to the structs generated
# returns:
#    \@table_names      - name of each struct
#    \@start_addresses  - absolute address of each struct
#    \@header_lists     - header file output for each struct
#    \@data_lists       - c file output for each struct
#    \@matlab_lists     - m-file output for each struct
# note: table order in the lists is reversed.
#
  my ($table_entries, @param_struct_names) = @_;

  my @symbol_list;
  my %previous_symbols;
  
  #make sure all the table names are valid C symbols
  for( my $i=0; $i<@param_struct_names; $i++ ){
    $param_struct_names[$i] = convert_to_C_symbol($param_struct_names[$i]);
  }
  
  my $struct_name = shift @param_struct_names;

  #build a list of all symbols and their values
  for(my $i=0; $i<@{$table_entries}; $i++){
    my $symbol = $table_entries->[$i]->{'CName'};
    my $data_type = $table_entries->[$i]->{'Type'};
    my $comments = $table_entries->[$i]->{'Notes'};
    if( $data_type->{'fraction'} > 0 ){ #prepend table comments with data type
      $comments = $data_type->{'MATLAB'} .' '. $comments;
    }
    my $mem_loc = $table_entries->[$i]->{'MemLoc'};
    my $data = $table_entries->[$i]->{'Data'};

    my $bytes = $data_type->{'bits'}/8;
    if($bytes > 1 && ($mem_loc % 2) ){
      warning(36, "symbol '$symbol' in struct '$struct_name' ($bytes bytes) occurs at an odd address.");
    }

    if( $data eq '' ){
      warning(34, "symbol '$symbol' in struct '$struct_name' has no value.");
    }

    if($previous_symbols{$symbol}++){
      if($use_num_suffix){
        #add an index to symbols already in the table, to make them unique
        $symbol .= $previous_symbols{$symbol}-1;
      }elsif($previous_symbols{$symbol} <= 2){
        warning(31, "symbol '$symbol' in struct '$struct_name' occurs more than once.");
      }
    }
  
    push @symbol_list, [$mem_loc, $bytes, $data_type, $symbol, $data, $comments];
  }
  
  #re-organize the table based on memory location
  @symbol_list = sort {$a->[0] <=> $b->[0] } @symbol_list;
  my $start_address = sprintf("0x%x", $symbol_list[0]->[0]);
  
  my $spacer_num = 0;
  my $base_struct_name = $struct_name;
  my $struct_name_num = 1;
  
  my @header_lists = ([]);
  my @data_lists = ([]);
  my @matlab_lists = ([]);
  my @table_names = ($struct_name);
  my @start_addresses = ($start_address);
  
  #build the structure(s)
  my $next_open_address = 0;
  my $previous_symbol = "";
  if(@symbol_list){ $next_open_address = $symbol_list[0]->[0]; }
  foreach my $table_entry( @symbol_list){
    my ($mem_loc, $bytes, $data_type, $symbol, $data, $comments) = @{$table_entry};
    if($mem_loc < $next_open_address){
      warning(32, "symbol '$symbol' is being removed because it overlaps previous symbol '$previous_symbol' in struct '$struct_name'.");
      #skip this entry to make the table line up
    }else{
      check_external_object_overlap( $symbol, $struct_name, $mem_loc, $bytes );

      #check for gaps in the table
      if($mem_loc > $next_open_address){
        my $gap_size = $mem_loc - $next_open_address;
        
        if( ($struct_max_gap >= 0) && $gap_size > $struct_max_gap ){
          #split the table if the gap is too large
          $spacer_num = 0;
          $next_open_address += $gap_size;

          unshift(@header_lists, []);
          unshift(@data_lists, []);
          unshift(@matlab_lists, []);
          if(!($struct_name = shift(@param_struct_names))){
            $struct_name = $base_struct_name . $struct_name_num++;
          }
          unshift(@table_names,$struct_name);
          unshift(@start_addresses,sprintf("0x%x", $next_open_address));
  
        }else{
          #insert a spacer variable if necessary
          my $spacer = "_spacer" . $spacer_num ."_[". ($gap_size) ."]";
          my $tmp_address = sprintf( "%x", $next_open_address);
          push @{$header_lists[0]}, [ "uint8_t", "$spacer;" ];
          push @{$data_lists[0]}, ["{0},", "//0x$tmp_address", "$spacer"];
          $spacer_num++;
          $next_open_address += $gap_size;
        }
      }
      if($comments){
        push @{$header_lists[0]}, [$data_type->{'C'}, "$symbol;", "//$comments"];
      }else{
        push @{$header_lists[0]}, [$data_type->{'C'}, "$symbol;"];
      }
      my $tmp_address = sprintf( "%x", $next_open_address);

      if($data_type->{'sign'} ){
        push @{$data_lists[0]}, ["$data,", "//0x$tmp_address", "$symbol"];
      }else{
        push @{$data_lists[0]}, ["${data}U,", "//0x$tmp_address", "$symbol"];
      }
      $next_open_address += $bytes;

      #cast to the matlab data type
      my $matlab_data = matlab_typecast($data, $data_type);
      if($cd_pointer){
        if ($cd_alias){
          push (@{$matlab_lists[0]}, [ "CD_" . $symbol, "= Bobcat.Parameter; CreateAliasCD(", "CD_" . $symbol, ",$matlab_data", ",'ConstantDataPointer'", ",'$struct_name'",",'$symbol');" ]);
        }else{
          push (@{$matlab_lists[0]}, [ $symbol, "= Bobcat.Parameter; CreateCD(", $symbol, ",$matlab_data", ",'ConstantDataPointer'", ",'$struct_name'", ");" ]);
        }
      }else{
        if ($cd_alias){
          push (@{$matlab_lists[0]}, [ "CD_" . $symbol, "= Bobcat.Parameter; CreateAliasCD(", "CD_" . $symbol, ",$matlab_data", ",'ConstantData'", ",'$struct_name'",",'$symbol');" ]);
        }else{
          push (@{$matlab_lists[0]}, [ $symbol, "= Bobcat.Parameter; CreateCD(", $symbol, ",$matlab_data", ",'ConstantData'", ",'$struct_name'", ");" ]);
        }
      }
    }
    $previous_symbol = $symbol;
  }
  
  return \@table_names, \@start_addresses, \@header_lists, \@data_lists, \@matlab_lists;
}


sub remove_address_offset{
#
# remove an address offset (values may be in hex)
# value returned is a hex string
#
  my ($addr,$offset) = @_;
  if($addr =~ m/^0[xX]/){ $addr = hex($addr); }
  if($offset =~ m/^0[xX]/){ $offset = hex($offset); }
  my $ret = $addr - $offset;
  if($ret < 0){ $ret = 0; }
  return sprintf("0x%x",$ret);
}

sub add_address_offset{
#
# add an address offset (values may be in hex)
# value returned is a hex string
#
  my ($addr,$offset) = @_;
  if($addr =~ m/^0[xX]/){ $addr = hex($addr); }
  if($offset =~ m/^0[xX]/){ $offset = hex($offset); }
  my $ret = $addr + $offset;
  if($ret < 0){ $ret = 0; }
  return sprintf("0x%x",$ret);
}

sub matlab_typecast{
#
#apply a matlab type cast to a literal value from the database
#
  my ($data, $data_type) = @_;
  return $data_type->{'MATLAB_prefix'} . sprintf( $data_type->{'MATLAB_format'}, $data) . $data_type->{'MATLAB_suffix'};
}


my $noname_counter = 0;
sub convert_to_C_symbol{
#
# converts a string into a format that will be accepted as a C symbol name
#
  my ($symbol) = @_;

  #strip leading/trailing white space
  $symbol =~ s/^\s+|\s+$//g;
  
  #convert non-word characters to underscores for C
  $symbol =~ s/[^A-Za-z_0-9]/_/g;

  #if the symbol starts with a number, add a leading _
  if($symbol =~ m/^[0-9]/){ $symbol = '_'.$symbol; }

  #remove duplicate and trailing underscores
  $symbol =~ s/__+/_/g;
  $symbol =~ s/_+$//g;

  if($symbol eq ''){ #handle empty symbol strings
    $symbol = '_noname'.($noname_counter++).'_';
  }
  
  return $symbol;
}


sub pretty_print{
#
#Prints a 2D array of strings aligned by column.
#Warning: assumes that all rows have the same number of elements
#example: 
# my @ex = (['a', 'bbb', 'cc'],['ddd','e','ffff']);
# pretty_print(\@ex);
# >> a   bbb cc
# >> ddd e   ffff
#
  my ($fh, $array_ref) = @_;
  my @col_lengths;
  
  for(my $i=0; $i < @{$array_ref}; $i++){
    for(my $j=0; $j<@{ $array_ref->[$i] }; $j++){
      my $len = length($array_ref->[$i][$j]);
      if(!defined $col_lengths[$j] || $col_lengths[$j] < $len){
        $col_lengths[$j] = $len;
      }
    }
  }

  for(my $i=0; $i < @{$array_ref}; $i++){
    for(my $j=0; $j<@{ $array_ref->[$i] }; $j++){
      my $pad_len = 1 + $col_lengths[$j] - length($array_ref->[$i][$j]);
      print $fh $array_ref->[$i][$j] . (' ' x $pad_len );
    }
    print $fh "\n";
  }
}

sub warning{
#
#prints a warning to sdterr (if the warning has not been suppressed)
#
  my ($num, $str) = @_;
  
  if(exists $suppressed_warnings{$num}){
    return;
  }else{
    print STDERR "Warning $num: " . $str . "\n"; 
  }
}

my %global_mem_table;
sub check_external_object_overlap{
#
#this sub looks for memory overlaps between symbols in different arrays/structures
#
  my ($name, $parent, $addr, $size) = @_;
  for(my $i=$addr; $i<$size+$addr; $i++){
    my @cur_obj = ($name, $parent);
    if(exists $global_mem_table{$i} ){
      my ($victim,$victim_parent) = @{$global_mem_table{$i}};
      my $addr_str = sprintf("0x%x", $i);
      warning(4,"'$name' in '$parent' overlaps '$victim' in '$victim_parent' at address $addr_str.");
      return
    }else{
      $global_mem_table{$i} = \@cur_obj;
    }
  }
}


######################
## database queries ##
######################

sub get_break_id_by_sn{
#
# Fetches the ID of the first SN break containing the provided serial number.
#
  my ($dbh, $sn) = @_;
  my $id_query = $dbh->prepare("
  select id from machinedataset where snstart <= ? AND snstop >= ? limit 1")
  or die "couldn't prepare statement: " . $dbh->errstr;

  $id_query->execute($sn,$sn) or die "query failed: " . $id_query->errstr;
  my $ret = undef;
  while( my ($id) = $id_query->fetchrow_array() ){
    $ret = $id;
  }
  if( !defined($ret) ){
    die "Unrecognized serial number $sn";
  }
  return $ret;
}


sub get_default_break{
#
# Fetches the ID of the first default SN break
#
  my ($dbh) = @_;
  my $id_query = $dbh->prepare("
  select id from machinedataset where isdefault=1 order by name limit 1 ")
  or die "couldn't prepare statement: " . $dbh->errstr;

  $id_query->execute() or die "query failed: " . $id_query->errstr;
  my $ret = undef;
  while( my ($id) = $id_query->fetchrow_array() ){
    $ret = $id;
  }
  if( !defined($ret) ){
    die "No default columns in machine table.";
  }
  return $ret;
}


sub get_break_id_by_name{
#
# Fetches the ID of the first SN break having the provided name.
#
  my ($dbh, $name) = @_;
  my $id_query = $dbh->prepare("
  select id from machinedataset where name = ? order by snstart limit 1")
  or die "couldn't prepare statement: " . $dbh->errstr;

  $id_query->execute($name) or die "query failed: " . $id_query->errstr;
  my $ret = undef;
  while( my ($id) = $id_query->fetchrow_array() ){
    $ret = $id;
  }
  if( !defined($ret) ){
    die "Unrecognized serial break name \"$name\"";
  }
  return $ret;
}


sub get_maintable_data{
#
# Fetches (and merges) main table data from the specified columns.
#
  my ($dbh, $table_name, $default_col_id, $data_col_id) = @_;
  my $col_data_query = $dbh->prepare("
    SELECT loc.Name, loc.Notes, loc.MemLoc, loc.WordLength, loc.FractionLength, loc.Signedness, data.Data, loc.Format
    FROM MachineDataSet break
    JOIN MachineData data ON break.ID = data.MachineDataSet_fk
    JOIN MachineLocation loc ON loc.ID = data.MachineLocation_fk
    WHERE break.ID = ?")
    or die "couldn't prepare statement: " . $dbh->errstr;

  #fetch the machine column rows that have data
  my %data_lookup;
  if( defined $data_col_id ){
    $col_data_query->execute($data_col_id) or die "query failed: " . $col_data_query->errstr;
    while( my $row = $col_data_query->fetchrow_hashref() ){
      my $entry = new_location( $row );
      $data_lookup{ $entry->{'MemLoc'} } = $entry;
    }
  }
  
  my $col_dflt_query = $dbh->prepare("
    SELECT loc.Name, loc.Notes, loc.MemLoc, loc.WordLength, loc.FractionLength, loc.Signedness, data.Data, loc.Format
    FROM MachineDataSet break
    JOIN MachineLocation loc ON loc.Machine_fk = break.Machine_fk
    OUTER LEFT JOIN MachineData data ON loc.ID = data.MachineLocation_fk AND break.ID = data.MachineDataSet_fk
    WHERE break.ID = ?
    ORDER BY loc.MemLoc")
    or die "couldn't prepare statement: " . $dbh->errstr;
  
  #read the whole default column, replacing its lines from data_lookup if they exist
  my @ret;
  $col_dflt_query->execute($default_col_id) or die "query failed: " . $col_dflt_query->errstr;
  while( my $row = $col_dflt_query->fetchrow_hashref() ){
  
    #check for missing default data
    if( !defined $row->{'Data'} ){
      my $addr_str = sprintf("0x%x", $row->{'MemLoc'});
      my $name_str = $row->{'Name'};
      if( !defined $name_str ){ $name_str = 'undefined' };
      warning(25,"table '$table_name' is missing default data at row '$name_str' (address $addr_str)");
      $row->{'Data'} = 0xffffffff;
    }
    my $entry = new_location( $row );
    my $dcol = $data_lookup{ $entry->{'MemLoc'} };
    if( defined($dcol) ){
      push( @ret, $dcol )
    }else{
      push( @ret, $entry );
    }
  }
  
  return @ret;
}


sub get_subtable_data{
#
# Fetches (and merges) subtable data from the specified column.
#
  my ($dbh, $table_name, $table_id, $data_col_ordering) = @_;
  my $col_data_query = $dbh->prepare("
    SELECT loc.Name, loc.Notes, loc.MemLoc, loc.WordLength, loc.FractionLength, loc.Signedness, data.Data, loc.Format
    FROM MachineSub sub
    JOIN MachineSubDataSet break ON break.MachineSub_fk = sub.ID
    JOIN MachineSubData data ON data.MachineSubDataSet_fk = break.ID
    JOIN MachineSubLocation loc ON loc.ID = data.MachineSubLocation_fk
    WHERE sub.ID = ? AND break.Ordering = ?")
    or die "couldn't prepare statement: " . $dbh->errstr;

  #fetch the machine column rows that have data
  my %data_lookup;
  if( defined $data_col_ordering ){
    $col_data_query->execute($table_id, $data_col_ordering) or die "query failed: " . $col_data_query->errstr;
    while( my $row = $col_data_query->fetchrow_hashref() ){
      my $entry = new_location( $row );
      $data_lookup{ $entry->{'MemLoc'} } = $entry;
    }
  }

  my $col_dflt_query = $dbh->prepare("
    SELECT loc.Name, loc.Notes, loc.MemLoc, loc.WordLength, loc.FractionLength, loc.Signedness, data.Data, loc.Format
    FROM MachineSub sub
    JOIN MachineSubDataSet break ON break.MachineSub_fk = sub.ID
    JOIN MachineSubLocation loc ON loc.ParentTable_fk = break.MachineSub_fk
    OUTER LEFT JOIN MachineSubData data ON loc.ID = data.MachineSubLocation_fk AND break.ID = data.MachineSubDataSet_fk
    WHERE sub.ID = ? AND break.Ordering = ?
    ORDER BY loc.MemLoc")
    or die "couldn't prepare statement: " . $dbh->errstr;
  
  #read the whole default column (which is always at index 0), repacing its lines from data_lookup if they exist
  my @ret;
  $col_dflt_query->execute($table_id, 0) or die "query failed: " . $col_dflt_query->errstr;
  while( my $row = $col_dflt_query->fetchrow_hashref() ){

    #check for missing default data
    if( !defined $row->{'Data'} ){
      my $addr_str = sprintf("0x%x", $row->{'MemLoc'});
      my $name_str = $row->{'Name'};
      if( !defined $name_str ){ $name_str = 'undefined' };
      warning(25,"table '$table_name' is missing default data at row '$name_str' (address $addr_str)");
      $row->{'Data'} = 0xffffffff;
    }
    my $entry = new_location( $row );
    my $dcol = $data_lookup{ $entry->{'MemLoc'} };
    if( defined($dcol) ){
      push( @ret, $dcol )
    }else{
      push( @ret, $entry );
    }
  }
  
  return @ret;
}


sub get_subtables{
#
# Fetches the ids, names, and column to load for all subtables
# attached to the specified machine main table.  Tables only loaded
# in options, or in subtables, are not included.
#
  my ($dbh, $name, $dflt_col, $data_col) = @_;

  #data for all subtables linked in the main table
  my $subtable_query = $dbh->prepare("
    SELECT sub.ID, sub.Name, dflt_data.Data, break_data.Data, sub.Notes
    FROM Machine machine
    JOIN MachineSub sub ON machine.ID = sub.Machine_fk
    JOIN MachineLocation loc on loc.MachineSub_fk = sub.ID
    LEFT OUTER JOIN MachineData dflt_data ON dflt_data.MachineLocation_fk = loc.ID AND dflt_data.MachineDataSet_fk = ?
    LEFT OUTER JOIN MachineData break_data ON break_data.MachineLocation_fk = loc.ID AND break_data.MachineDataSet_fk = ?
    WHERE machine.Name = ?")
    or die "couldn't prepare statement: " . $dbh->errstr;

  my @ret;
  $subtable_query->execute( $dflt_col,$data_col,$name) or die "query failed: " . $subtable_query->errstr;
  while( my( $sub_id, $sub_name, $dflt_data, $break_data, $sub_notes ) = $subtable_query->fetchrow_array() ){
    #figure out which column to load in the subtable
    my $column = undef;
    if( !defined $column ){ $column = $break_data; }
    if( !defined $column ){ $column = $dflt_data; }
    if( !defined $column ){ $column = 0; } #default
    
    if( !(defined $sub_name) ){
      $sub_name = '';
    }
    if( !defined $sub_notes ){
      $sub_notes = '';
    }
    
    my %item;
    $item{'Name'} = $sub_name;
    $item{'CName'} = convert_to_C_symbol($sub_name);
    $item{'ID'} = $sub_id;
    $item{'Notes'} = $sub_notes;
    $item{'Column'} = $column;
    push(@ret, \%item);
  }
  return @ret;
}

sub print_subtable_links{
#
# Fetches (and merges) subtable data from the specified column.
#
my ($dbh) = @_;
my $link_query = $dbh->prepare("
SELECT tbl.Name, tbl.MapID, sloc.Signedness, sloc.WordLength, sloc.FractionLength 
FROM MachineSub tbl
JOIN MachineSubLocation sloc ON sloc.id = (
  SELECT id FROM MachineSubLocation loc2
  WHERE tbl.id = loc2.ParentTable_fk
  LIMIT 1)")
  or die "couldn't prepare statement: " . $dbh->errstr;

my $test1 = $link_query->execute() or die "query failed: " . $link_query->errstr;

while( my( $var1, $var2, $var3, $var4, $var5 ) = $link_query->fetchrow_array()){
    if($var3){
        print OFA ("  ${var1} = (int${var4}_t const *)getCDSection(${var2});\n");
    }else{
        print OFA ("  ${var1} = (uint${var4}_t const *)getCDSection(${var2});\n");
    }
  }
}

sub print_map_tables{
#
# Fetches (and merges) subtable data from the specified column.
#
my ($dbh) = @_;
my $link_query = $dbh->prepare("
SELECT tbl.Name, sloc.Signedness, sloc.WordLength 
FROM MachineSub tbl
JOIN MachineSubLocation sloc ON sloc.id = (
  SELECT id FROM MachineSubLocation loc2
  WHERE tbl.id = loc2.ParentTable_fk
  LIMIT 1)")
  or die "couldn't prepare statement: " . $dbh->errstr;

my $test1 = $link_query->execute() or die "query failed: " . $link_query->errstr;

while( my( $var1, $var2, $var3 ) = $link_query->fetchrow_array()){
    if($var2){
        print OFA ("  int${var3}_t const *${var1};\n");
    }else{
        print OFA ("  uint${var3}_t const *${var1};\n");
    }
  }
  return;
}


sub new_location{
#
# Bundles the results of a database query into a data row hash.
#   Name   - location name
#   CName  - version of Name suitable for use as a variable in C
#   Notes  - location notes
#   MemLoc - location memory address
#   Type   - data type (see new_datatype)
#   Data   - data value
#
  my ($row) = @_;
  my $type = new_datatype($row->{'WordLength'}, $row->{'Signedness'} ,$row->{'FractionLength'}, $row->{'Format'});
  my $name = $row->{'Name'};
  if( !(defined $name) ){
    $name = '';
  }
  my $notes = $row->{'Notes'};
  if( !defined $notes ){
    $notes = '';
  }

  my %entry;
  $entry{'Name'} = $name;
  $entry{'CName'} = convert_to_C_symbol($name);
  $entry{'Notes'} = $notes;
  $entry{'MemLoc'} = $row->{'MemLoc'};
  $entry{'Type'} = $type;

  my $data = $row->{'Data'};
  if( $type->{'float'} ){
    #unpack the binary value into a float type
    if( $Config{ivsize} == 8 ){
      #64-bit perl
      my $packed_data = pack( 'q', $data );
      if( $row->{'WordLength'} == 32 ){
        $data = unpack( 'f', $packed_data );
      }else{
        $data = unpack( 'd', $packed_data );
      }
    }else{
      #32-bit perl
      my $packed_data = pack( 'i', $data );
      if( $row->{'WordLength'} == 32 ){
        $data = unpack( 'f', $packed_data );
      }else{
        $data = 0; #can't figure out how to get this to work in 32-bit perl -jjc
      }
    }
  }else{
    #mask off unused bytes so we match how SA handles database data
    my $negative = ($row->{'Data'} < 0) && $row->{'Signedness'};
    my $mask = ( 2 ** $row->{'WordLength'} - 1 );
    if( $negative ){
      $data = -(~($data | ~$mask)+1);
    }else{
      $data = $mask & $data;
    }
  }

  $entry{'Data'} = $data;

  return \%entry;
}


sub new_datatype{
#
# Creates a new data type hash.  The following fields will be included:
#   C - c types.h data type (e.g. uint8_t)
#   MATLAB - matlab data type (e.g. uint8, fixdt(1,16,5))
#   bits - total bits in data type (same as passed in)
#   sign - true if data type is signed (same as passed in)
#   fraction - bits in data type fraction (same as passed in )
#   MATLAB_prefix - first half of the matlab data import
#   MATLAB_suffix - second half of the matlab data import
#   MATLAB_format - sprintf formatting to be applied to the data value
#
  my ($bits,$sign,$fraction,$format) = @_;
  my %data_type;
  $data_type{'bits'} = $bits;
  $data_type{'sign'} = $sign;
  $data_type{'fraction'} = $fraction;
  $data_type{'float'} = $format == 1;

  if( $format == 1 ){
    if( $bits == 32 ){
      $data_type{'C'} =  "float";
      $data_type{'MATLAB'} = "single";
      $data_type{'MATLAB_prefix'} = "single(";
      $data_type{'MATLAB_suffix'} = ")";
      $data_type{'MATLAB_format'} = "%s";
    }else{
      $data_type{'C'} =  "double";
      $data_type{'MATLAB'} = "double";
      $data_type{'MATLAB_prefix'} = "double(";
      $data_type{'MATLAB_suffix'} = ")";
      $data_type{'MATLAB_format'} = "%s";
    }
  }else{
    my $signchar = (($sign>0)?'':'u');
    $data_type{'C'} =  "${signchar}int${bits}_t";

    if( $fraction != 0 ){
      $data_type{'MATLAB'} = "fixdt($sign,$bits,$fraction)";
      if($sign){
        $data_type{'MATLAB_prefix'} = "fi(0,$sign,$bits,$fraction,'int',";
        $data_type{'MATLAB_format'} = "%s";
      }else{
        $data_type{'MATLAB_prefix'} = "fi(0,$sign,$bits,$fraction,'hex',";
        $data_type{'MATLAB_format'} = "'%0". $bits/4 ."x'"; #uniform padded hexadecimal formatting required
      }
      $data_type{'MATLAB_suffix'} = ")";
    }else{
      $data_type{'MATLAB'} = "${signchar}int${bits}";
      $data_type{'MATLAB_prefix'} = "${signchar}int${bits}(";
      $data_type{'MATLAB_suffix'} = ')';
      $data_type{'MATLAB_format'} = '%s'; #note: don't use %d here or 4294967295 (0xffffffff) will be printed as -1 in 32-bit perl
    }
  }
  return \%data_type;
}
