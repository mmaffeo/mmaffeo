#!/usr/bin/perl -w
use strict;

my $db_prog = "database_reader.exe";
my $output_file_h = 'cdata.h';
my $output_file_c = 'cdata.c';
my $output_file_m = 'cdata.m';
my $default_col = 0;
my $machine_col = 0;
my $use_num_suffix = 0;
my $main_table_name_default = 'cdata';
my @main_table_names;
my $check_bdb_timestamp = 0;
my $use_header_timestamp = 0;
my $target_compiler = 'metrowerks';
my %suppressed_warnings;
my $struct_max_gap = -1; #maximum gap between consecutive symbols before a struct will be split in two
my %metrowerks_near_tables;
my %tasking_near_tables;
my $global_address_offset_active = 0;
my $global_address_offset        = 0;
my $cd_alias = 0;

my $exec_name = $0;
$exec_name =~ s{^.*(\\|/)}{};

my $usage = "
Generates the C, H, and M files necessary for linking application code with
a BDB database.

usage: $exec_name [<flags>] <BDB file> <database key>
  -a <name>,<address> set the struct/array <name>'s address here, ignore
     address in database, remove far qualifier (metrowerks only)
  -e <offset> set the address of all structs/arrays relative to this offset,
     remove far qualifier (metrowerks only)
  -b <bytes> Break structures in two if the gap between consecutive symbols
     exceeds <bytes>.
  -d <default column index> use this default table (default 0)
  -f <name>,<class> wrap the struct/array <name> in '#pragma class nc=<class>'
     instead of using the _at() qualifier, declare it as _near (tasking only)
  -m <machine column index> use this machine table (default 0)  
  -n add a number suffix to variables that appear in a table more than once
  -o <output h file name> use this output file name (default cdata.h)
  -p <output c file name> use this output file name (default cdata.c)
  -q <output m file name> use this output file name (default cdata.m)
  -r <name> use this main table name in generated code (default cdata)
     Note: when using -b, <name> may be a comma-separated list.
  -s <path> specify the path to database_reader.exe (default is .)
  -t add a time stamp to the output file headers
  -A uses an alias for constant data variable names with CD_ removed
  -C skip build if database time stamp has not changed (generates *.make file)
  -T generate C code for the tasking compiler (default is for metrowerks)
  -W <warning num list> ignore these warning numbers (ex: -W 4,1,2)

  note: lists of arguments must be separated by commas, with no spaces.
   
* Database items with //fixdt_0_16_8 or //int8, etc in their descriptions will
  be interpreted as their respective data types when possible.
* Descriptions may also use % instead of // (matlab style comments).  Anything
  after a // or % will not be included in names of the c/m file symbols.
* Sub-tables will be imported as arrays if their members are of uniform size,
  and as structures otherwise.
* The machine table will always be imported as a structure.
* Byte arrays will be inserted into any gaps found in structures.
* If a link table name is preceded by the database key, the key will be omitted
  from the symbol name in the output files.

Warnings:
   1   could not open <file>.make
   2   invalid size <num> for <array/symbol>, defaulting to uint16_t
   3   ignoring hint <hint> for symbol <name> (invalid arguments to fixdt)
   4   <name> in <struct/array> overlaps <name> in <struct/array> at address
       <address>
  20   type specified for array <name> conflicts with its size in the database
  21   the elements of array <name> are misaligned (starts with element <num>)
  22   element <num> of array <name> is being removed because it has an invalid
       address <address>
  23   element <num> of array <name> has no value
  24   element <num> of table <name> has a non-numeric value
  30   type specified for symbol <name> in struct <name> conflicts with its
       size in the database
  31   symbol <name> in struct <name> occurs more than once
  32   symbol <name> is being removed because it overlaps previous symbol
       <name> in struct <name>
  33   symbol <name> in struct <name> is being removed because it has an
       invalid address <address>
  34   symbol <name> in struct <name> has no value
  35   symbol <name> in struct <name> has a non-numeric value
  36   symbol <name> in struct <name> (<num> bytes) occurs at an odd address
";

#check arguments
while(@ARGV && $ARGV[0] =~ m/^-([A-Za-z]+)$/){
  my $flags = $1;
  shift @ARGV; #remove flags token from args array
  foreach(split(//, $flags)){
    
    if($_ eq 'h'){
      print $usage;
      exit(0);
    }elsif($_ eq 'b'){
      $struct_max_gap = shift @ARGV;
    }elsif($_ eq 'o'){
      $output_file_h = shift @ARGV;
    }elsif($_ eq 'p'){
      $output_file_c = shift @ARGV;
    }elsif($_ eq 'q'){
      $output_file_m = shift @ARGV;
    }elsif($_ eq 'r'){
      push( @main_table_names, split( /,/, shift(@ARGV) ) );
    }elsif($_ eq 's'){
      $db_prog = (shift @ARGV) . "\\" . $db_prog;
    }elsif($_ eq 't'){
      $use_header_timestamp = 1;
    }elsif($_ eq 'd'){
      $default_col = shift @ARGV;
    }elsif($_ eq 'm'){
      $machine_col = shift @ARGV;
    }elsif($_ eq 'n'){
      $use_num_suffix = 1;
    }elsif($_ eq 'C'){
      $check_bdb_timestamp = 1;
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
    }elsif($_ eq 'e'){
      $global_address_offset_active = 1;
      $global_address_offset = shift @ARGV;
    }elsif($_ eq 'T'){
      $target_compiler = 'tasking';
    }elsif($_ eq 'f'){
      my @list = split( /,/, shift(@ARGV) );
      if(@list == 2){
        $tasking_near_tables{$list[0]} = $list[1];
      }else{
        print STDERR "\nError: wrong number of arguments to option -f\n";
        exit(1);
      }
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

my ($bdb_file, $db_key) = @ARGV;

#report a verbose error if the database reader can't be found
if(!-e $db_prog){
  print STDERR "\nERROR: The database reader program can not be found at '$db_prog'.  Please specify its location with -s or move it to your working directory.\n";
  exit(-1);
}

(-r $bdb_file) or die "\nError: couldn't read from $bdb_file: $!\n";

my @file_stats = stat($bdb_file);
my $last_modified = $file_stats[9];

#abort run if the database has not changed
if($check_bdb_timestamp){
  if(-e "$bdb_file.make"){
    if( open( TSTAMP, "<$bdb_file.make" ) ){
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

if($check_bdb_timestamp){
  #store datbase time stamp for this run
  if( open( TSTAMP, ">$bdb_file.make" ) ){
    print TSTAMP "$last_modified";
  }else{
    warning(1, "could not open $bdb_file.make: $!");  
  }
  close(TSTAMP);
}

open( OFH, ">$output_file_h" ) or die "\nError: couldn't open $output_file_h: $!\n";
open( OFC, ">$output_file_c" ) or die "\nError: couldn't open $output_file_c: $!\n";
open( OFM, ">$output_file_m" ) or die "\nError: couldn't open $output_file_m: $!\n";

#build a macro name for the c header file boilerplate
my $gaurd_macro = uc($output_file_h);
$gaurd_macro =~ s{^.*(\\|/)}{};
$gaurd_macro =~ s{[^A-Za-z0-9_]}{_};
$gaurd_macro = "_".$gaurd_macro."_";


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
  $bdb_file
  key: $db_key
\\*****************************************************************************/";

my $m_boilerplate = 
"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%This module defines the constant data structures available in the database.
%
%This file is auto-generated by $exec_name.
%$timestamp
%Built from:
%  $bdb_file
%  key: $db_key
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";

print OFH 
"#ifndef $gaurd_macro
#define $gaurd_macro

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

print_main_table();
print_link_tables();

print OFH "\n#endif //#ifndef $gaurd_macro\n";

print STDOUT "Done.\n";

#################
## subroutines ##
#################

sub print_main_table{
#
# Generates the main (machine table) structure
#
  print STDOUT "Generating $db_key machine table...\n";
  
  #extract the relevent tables from the database
  my @descriptions = run($db_prog, '-Mdr', $db_key, $bdb_file);
  my @sizes        = run($db_prog, '-Mbr', $db_key, $bdb_file);
  my @locs         = run($db_prog, '-Mmr', $db_key, $bdb_file);
  my @values       = run($db_prog, '-MFr', $db_key, $default_col, $machine_col, $bdb_file);
  
  my ($table_names, $addresses, $members, $data, $matlab ) = generate_typedef_struct(\@descriptions, \@sizes, \@locs, \@values, @main_table_names);
  
  my $table_name;
  while($table_name = pop @$table_names){
    print OFH "\ntypedef struct ${table_name}_s{\n";
    pretty_print(\*OFH, pop @$members );
    print OFH "}${table_name}_t;\n";

    if($target_compiler eq 'tasking'){
      if( exists $tasking_near_tables{$table_name} ){
        print OFH "_near extern const ${table_name}_t $table_name;\n";
        print OFC "\n#pragma class nc=" . $tasking_near_tables{$table_name} . "\n";
        print OFC "_near const ${table_name}_t $table_name = {\n";
        pretty_print(\*OFC, pop @$data);
        print OFC "};\n";
        print OFC "#pragma default_attributes\n";
        pop(@$addresses); #discard unused address
      }else{
        print OFH "_far extern const ${table_name}_t $table_name;\n";
        print OFC "\n_far const ${table_name}_t $table_name _at(". pop(@$addresses).") = {\n";
        pretty_print(\*OFC, pop @$data);
        print OFC "};\n";
      }
    }else{
      if( exists $metrowerks_near_tables{$table_name} ){
        print OFH "extern const ${table_name}_t $table_name;\n";
        print OFC "\nconst ${table_name}_t $table_name \@". $metrowerks_near_tables{$table_name} ." = {\n";
        pretty_print(\*OFC, pop @$data);
        print OFC "};\n";
        pop(@$addresses); #discard unused address
      }elsif($global_address_offset_active){
        my $offset_address = remove_address_offset(pop(@$addresses), $global_address_offset);
        print OFH "extern const ${table_name}_t $table_name;\n";
        print OFC "\nconst ${table_name}_t $table_name \@". $offset_address ." = {\n";
        pretty_print(\*OFC, pop @$data);
        print OFC "};\n";
      }else{
        print OFH "extern const ${table_name}_t far $table_name;\n";
        print OFC "\nconst ${table_name}_t far $table_name \@". pop(@$addresses) ." = {\n";
        pretty_print(\*OFC, pop @$data);
        print OFC "};\n";
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
  #extract the relevent tables from the database
  my $exec_str;

  print STDOUT "Compiling a list of sub-tables for $db_key...\n";
  
  my @subtables        = run($db_prog, '-MXlr', $db_key, $bdb_file);
  my @subtable_columns = run($db_prog, '-MXFr', $db_key, $default_col, $machine_col, $bdb_file);  

  my $num_of_subtables = @subtables;
  print STDOUT "Generating $num_of_subtables sub-tables...\n";
  
  foreach( my $i=0; $i< @subtables; $i++){
    my $subtable = $subtables[$i];
    my $column = $subtable_columns[$i];

    #print STDOUT "generating $db_key link table '$subtable'\n";

    #extract subtable data from the database
    my @descriptions;
    my @sizes;
    my @locs;
    my @values;

    my @querry = run($db_prog, '-LbmdN', $subtable, $column, $bdb_file);
    foreach(@querry){
      my ($loc, $size, $desc, $val) = split(/,/);
      push(@descriptions, $desc);
      push(@sizes, $size);
      push(@locs, $loc);
      push(@values, $val);
    }

    #read database table description
    my ($table_name, $comments, $data_type) = process_description($subtable);
    #tables in the database are usually prefixed by the main table key (redundant for the project)
    $table_name =~ s{^ $db_key _?}{}x;
    
    #survey the element sizes in the table
    my %num_of_each_size;
    foreach(@sizes){ $num_of_each_size{$_}++; }

    if( keys(%num_of_each_size) != 1 ){
      #the elements of this table are not of uniform size, so represent it as an enumeration
      my ($table_names, $addresses, $members, $data, $matlab ) = generate_typedef_struct(\@descriptions, \@sizes, \@locs, \@values, $table_name);

      my $table_name;
      while($table_name = pop @$table_names){
      
        print OFH "\ntypedef struct ${table_name}_s{\n";
        pretty_print(\*OFH, pop @$members );
        print OFH "}${table_name}_t;\n";

        if($target_compiler eq 'tasking'){
          if( exists $tasking_near_tables{$table_name} ){
            print OFH "_near extern const ${table_name}_t $table_name;\n";
            print OFC "\n#pragma class nc=" . $tasking_near_tables{$table_name} . "\n";
            print OFC "_near const ${table_name}_t $table_name = { //column $column\n";
            pretty_print(\*OFC, pop @$data);
            print OFC "};\n";
            print OFC "#pragma default_attributes\n";
            pop(@$addresses); #discard unused address
          }else{
            print OFH "extern const ${table_name}_t $table_name;\n";
            print OFC "\nconst ${table_name}_t $table_name _at(". pop(@$addresses).") = { //column $column\n";
            pretty_print(\*OFC, pop @$data);
            print OFC "};\n";
          }
        }else{
          if( exists $metrowerks_near_tables{$table_name} ){
            print OFH "extern const ${table_name}_t $table_name;\n";
            print OFC "\nconst ${table_name}_t $table_name \@". $metrowerks_near_tables{$table_name} ." = { //column $column\n";
            pretty_print(\*OFC, pop @$data);
            print OFC "};\n";
            pop(@$addresses); #discard unused address
          }elsif($global_address_offset_active){
            my $offset_address = remove_address_offset(pop(@$addresses), $global_address_offset);
            print OFH "extern const ${table_name}_t $table_name;\n";
            print OFC "\nconst ${table_name}_t $table_name \@". $offset_address ." = { //column $column\n";
            pretty_print(\*OFC, pop @$data);
            print OFC "};\n";
          }else{
            print OFH "extern const ${table_name}_t far $table_name;\n";
            print OFC "\nconst ${table_name}_t far $table_name \@". pop(@$addresses) ." = { //column $column\n";
            pretty_print(\*OFC, pop @$data);
            print OFC "};\n";
          }
        }

        print OFM "\n";
        pretty_print(\*OFM, pop @$matlab);
      }
    }else{
      #the elements of this table are all the same size, so represent them as an array
      my @tmp = keys(%num_of_each_size);
      my $size = $tmp[0];
      
      if(!%{$data_type}){
        $data_type = guess_data_type("array '$subtable'", $size);
      }else{
        if($data_type->{'bits'} != $size*8){
          warning(20, "type specified for array '$table_name' conflicts with its size in the database.");
        }
      }

      my $first_address = $locs[0];
      if($first_address =~ m/^0[xX]/){ $first_address = hex($first_address); }
      
      #check table memory locations (they should be contiguous)
      my $target_address = $first_address;
      my $table_alignment_warning_issued = 0;
      foreach(my $j=0; $j<@locs; $j++){
        my $cur_address = $locs[$j];
        if($cur_address =~ m/^0[xX]/){ $cur_address = hex($cur_address); }
        
        if($cur_address !~ m/^[0-9]+$/){
          warning(22, "element $j of array '$table_name' is being removed because it has an invalid address '$cur_address'.");
          next;
        }
        
        if(($cur_address != $target_address) && !$table_alignment_warning_issued){
          warning(21, "the elements of array '$table_name' are misaligned (starts with element $j).");
          $table_alignment_warning_issued = 1;
        }
        $target_address += $size;
        
        #check data values too...
        my $data = $values[$j];
        if( $data eq '' ){
          warning(23, "element $j of array '$table_name' has no value.");
        }elsif( $data !~ m{ ^\s* -? \s* (0[xX])? [0-9A-Fa-f]+ \s*$ }x ){
          warning(24, "element $j of array '$table_name' has a non-numeric value.");
        }
        
        check_external_object_overlap( "element $j", $table_name, $cur_address, $size );
      }

      #print data to c/h files
      my $tmp = $table_name; #guess where to insert underscores in mixed-case names
      $tmp =~ s{([A-Z])([A-Z][a-z])}{$1_$2}xg;
      $tmp =~ s{([a-z])([A-Z])}{$1_$2}xg;
      my $size_of = "SIZE_OF_".uc($tmp);
      
      my $addr_str = sprintf( "0x%x", $first_address );
      print OFH "\n#define $size_of ".@sizes;

      if($comments){
        $comments = ' //' . $comments;
      }
      
      if($target_compiler eq 'tasking'){
        if( exists $tasking_near_tables{$table_name} ){
          print OFH "\n_near extern const ".$data_type->{'C'}." ".$table_name."[$size_of];$comments\n";
          print OFC "\n#pragma class nc=" . $tasking_near_tables{$table_name} . "\n";
          print OFC "_near const ".$data_type->{'C'}." ".$table_name."[$size_of] _at($addr_str) = { //column $column\n";
          print OFC "#pragma default_attributes\n";
        }else{
          print OFH "\nextern const ".$data_type->{'C'}." ".$table_name."[$size_of];$comments\n";
          print OFC "\nconst ".$data_type->{'C'}." ".$table_name."[$size_of] _at($addr_str) = { //column $column\n";
        }
      }else{
        if( exists $metrowerks_near_tables{$table_name} ){
          print OFH "\nextern const ".$data_type->{'C'}." ".$table_name."[$size_of];$comments\n";
          print OFC "\nconst ".$data_type->{'C'}." ".$table_name."[$size_of] \@". $metrowerks_near_tables{$table_name} ." = { //column $column\n";
        }elsif($global_address_offset_active){
          my $offset_address = remove_address_offset($addr_str, $global_address_offset);        
          print OFH "\nextern const ".$data_type->{'C'}." ".$table_name."[$size_of];$comments\n";
          print OFC "\nconst ".$data_type->{'C'}." ".$table_name."[$size_of] \@". $offset_address ." = { //$addr_str column $column\n";
        }else{
          print OFH "\nextern const ".$data_type->{'C'}." far ".$table_name."[$size_of];$comments\n";
          print OFC "\nconst ".$data_type->{'C'}." far ".$table_name."[$size_of] \@$addr_str = { //column $column\n";
        }
      }

      print OFM "\n$table_name = Bobcat.Parameter; CreateCDTable_basic( $table_name ,'', ".$data_type->{'MATLAB_prefix'}." [...\n";

      my $c_line = "";
      my $m_line = "";
      foreach(@values){
        my $data = $_;
        #limit line length to 200 characters
        if(length($c_line) + length("$data, ") < 200){
          $c_line .= "$data, ";
        }else{
          print OFC "$c_line\n";
          $c_line = "$data, ";
        }
        $data =~ s{(0[xX][0-9A-Fa-f]+)}{hex($1)}ge; #convert hex numbers (matlab doesn't understand these)
        if(length($m_line) + length("$data, ") < 200){
          $m_line .= "$data, ";
        }else{
          print OFM "$m_line...\n";
          $m_line = "$data, ";
        }
      }
      print OFC "$c_line\n";
      print OFC "};\n";

      print OFM "$m_line...\n";
      print OFM "] ".$data_type->{'MATLAB_suffix'}." );\n";
    }
  }
}


sub generate_typedef_struct{
#
# generates a typedefed struct based on the table data passed in
# params:
#    $descriptions       - ref to a list of the database descriptions for this table
#    $sizes              - ref to a list of the database sizes for this table
#    $locs               - ref to a list of the database addresses for this table
#    $values             - ref to a list of the database values for this table
#    @param_struct_names - name(s) to be assigned to the structs generated
# returns:
#    \@table_names      - name of each struct
#    \@start_addresses  - absolute address of each struct
#    \@header_lists     - header file output for each struct
#    \@data_lists       - c file output for each struct
#    \@matlab_lists     - m-file output for each struct
# note: table order in the lists is reversed.
#
  my ($descriptions, $sizes, $locs, $values, @param_struct_names) = @_;

  my @symbol_list;
  my %previous_symbols;
  my $struct_name = shift @param_struct_names;

  #build a list of all symbols and their values
  for(my $i=0; $i<@{$descriptions}; $i++){
    my $symbol = $descriptions->[$i];
    my $data_type;
    my $comments;
    my $size = $sizes->[$i];
    my $mem_loc = $locs->[$i];
    my $data = $values->[$i];

    #convert memory location from hex, if necessary
    if($mem_loc =~ m/^0[xX]/){ $mem_loc = hex($mem_loc); }

    ($symbol, $comments, $data_type) = process_description($symbol);

    if($mem_loc !~ m/^[0-9]+$/){
      warning(33, "symbol '$symbol' in struct '$struct_name' is being removed because it has an invalid address '$mem_loc'.");
      next;
    }

    if($size > 1 && ($mem_loc % 2) ){
      warning(36, "symbol '$symbol' in struct '$struct_name' ($size bytes) occurs at an odd address.");
    }

    if(!%{$data_type}){
      $data_type = guess_data_type("symbol '$symbol' in struct '$struct_name'", $size);
    }else{
      if($data_type->{'bits'} != $size*8){
        warning(30, "type specified for symbol '$symbol' in struct '$struct_name' conflicts with its size in the database.");
      }
    }

    if( $data eq '' ){
      warning(34, "symbol '$symbol' in struct '$struct_name' has no value.");
    }elsif( $data !~ m{ ^\s* -? \s* (0[xX])? [0-9A-Fa-f]+ \s*$ }x ){
      warning(35, "symbol '$symbol' in struct '$struct_name' has a non-numeric value.");
    }

    if($previous_symbols{$symbol}++){
      if($use_num_suffix){
        #add an index to symbols already in the table, to make them unique
        $symbol .= $previous_symbols{$symbol}-1;
      }elsif($previous_symbols{$symbol} <= 2){
        warning(31, "symbol '$symbol' in struct '$struct_name' occurs more than once.");
      }
    }
  
    push @symbol_list, [$mem_loc, $size, $data_type, $symbol, $data, $comments];
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
    my $temp_symbol = "";
  if(@symbol_list){ $next_open_address = $symbol_list[0]->[0]; }
  foreach my $table_entry( @symbol_list){
    my ($mem_loc, $size, $data_type, $symbol, $data, $comments) = @{$table_entry};
    if($mem_loc < $next_open_address){
      warning(32, "symbol '$symbol' is being removed because it overlaps previous symbol '$previous_symbol' in struct '$struct_name'.");
      #skip this entry to make the table line up
    }else{
      check_external_object_overlap( $symbol, $struct_name, $mem_loc, $size );

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
      push @{$data_lists[0]}, ["$data,", "//0x$tmp_address", "$symbol"];
      $next_open_address += $size;

      #cast to the matlab data type
      my $matlab_data = matlab_typecast($data, $data_type);
      if ($cd_alias){
                push (@{$matlab_lists[0]}, [ "CD_" . $symbol, "= Bobcat.Parameter; CreateAliasCD(", "CD_" . $symbol, ",$matlab_data", ",'ConstantData'", ",'$struct_name'",",'$symbol');" ]);
            }else{
                push (@{$matlab_lists[0]}, [ $symbol, "= Bobcat.Parameter; CreateCD(", $symbol, ",$matlab_data", ",'ConstantData'", ",'$struct_name'", ");" ]);
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


sub guess_data_type{
#
#default data types used when nothing is known other than object size
#
  my %data_type;

  my ($symbol, $size) = @_;
  if($size == 8){
    $data_type{'C'}             = 'uint64_t';
    $data_type{'bits'}          = 64;
    $data_type{'sign'}          = 0;
    $data_type{'fraction'}      = 0;
    $data_type{'MATLAB_prefix'} = 'uint64(';
    $data_type{'MATLAB_suffix'} = ')';
  }elsif($size == 4){
    $data_type{'C'}             = 'uint32_t';
    $data_type{'bits'}          = 32;
    $data_type{'sign'}          = 0;
    $data_type{'fraction'}      = 0;
    $data_type{'MATLAB_prefix'} = 'uint32(';
    $data_type{'MATLAB_suffix'} = ')';
  }elsif($size == 2){
    $data_type{'C'}             = 'uint16_t';
    $data_type{'bits'}          = 16;
    $data_type{'sign'}          = 0;
    $data_type{'fraction'}      = 0;
    $data_type{'MATLAB_prefix'} = 'uint16(';
    $data_type{'MATLAB_suffix'} = ')';
  }elsif($size == 1){
    $data_type{'C'}             = 'uint8_t';
    $data_type{'bits'}          = 8;
    $data_type{'sign'}          = 0;
    $data_type{'fraction'}      = 0;
    $data_type{'MATLAB_prefix'} = 'uint8(';
    $data_type{'MATLAB_suffix'} = ')';
  }else{ #default for invalid size
    warning(2, "invalid size '$size' for '$symbol', defaulting to uint16_t.");
    $data_type{'C'}             = 'uint16_t';
    $data_type{'bits'}          = 16;
    $data_type{'sign'}          = 0;
    $data_type{'fraction'}      = 0;
    $data_type{'MATLAB_prefix'} = 'uint16(';
    $data_type{'MATLAB_suffix'} = ')';
  }
  return \%data_type;
}


sub process_description{
#
# processes a database entry description string
# returns:
# 1) a symbol string based on the description suitable for use as a C variable
# 2) a comment string, if // was encountered or a fixdt was found
# 3) a data type, if one was indicated in the description, otherwise undefined
#
  my ($symbol) = @_;
  my $data_type;
  my $comments = "";
  my %data_type;
  
  #look for fixdt_#_#_# in the description
  if($symbol =~ m{ ( fixdt (\S+) ) }x){
    my ( $hint, $hint_args ) = ($1, $2);
    if($hint_args =~ m{ ^_ ([01]) _ ([0-9]+) _ ([0-9]+) $}x ){
      my ($sign, $bits, $fraction) = ($1,$2,$3);
      $data_type{'C'} = (($sign)?'':'u') . 'int' . $bits . '_t';
      $data_type{'bits'} = $bits;
      $data_type{'sign'} = $sign;
      $data_type{'fraction'} = $fraction;
      $data_type{'MATLAB_prefix'} = 'fi(';
      $data_type{'MATLAB_suffix'} = "/2^$fraction,$sign,$bits,$fraction)";
    }else{
      warning(3, "ignoring hint '$hint' for symbol '$symbol' (invalid arguments to fixdt).");
    }
  }

  #look for uint8_t etc, in the description
  if($symbol =~ m{ ( (u)?int(8|16|32|64) ) (?: _[tT] )? (?: $ | \s+ ) }x){
    $data_type{'C'} = $1.'_t';
    $data_type{'bits'} = $3;
    $data_type{'sign'} = !defined $2;
    $data_type{'fraction'} = 0;
    $data_type{'MATLAB_prefix'} = "$1(";
    $data_type{'MATLAB_suffix'} = ')';
  }
  
  #strip everything after a // or % and add it to the comments string
  if($symbol =~ s{ (?://|%) (.*) $}{}x){ $comments .= $1; }
  
  $symbol = convert_to_C_symbol($symbol);
  
  return ($symbol, $comments, \%data_type, );
}


sub matlab_typecast{
#
#apply a matlab type cast to a literal value from the database
#
  my ($data, $data_type) = @_;
  $data =~ s{(0[xX][0-9A-Fa-f]+)}{hex($1)}ge; #convert hex numbers (matlab doesn't understand these)
  return $data_type->{'MATLAB_prefix'} . $data . $data_type->{'MATLAB_suffix'};
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
#Warning: assumes that all rows are the same width.
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


sub run{
#
#Runs a shell command and returns its standard output.
#Exits if the command fails.
#
  my ($cmd, @args) = @_;
  my @values;  
  
  #loathe perl 5.0
  eval q{
    open(CMD, '-|', $cmd, @args) or die "your perl version is... lacking";
  }; if($@){
    foreach(@args){ 
      if(m/[ \t]/){
        #quote arguemnts with embedded white space
        $cmd .= ' "' . $_ . '"';
      }else{
        $cmd .= " $_";
      }
    }
    @values = `$cmd`;
    if( $? ){
      #non-zero return code from the program, exiting.
      print "\nError: failed to run $cmd.\n";
      exit(-1);
    }
  }else{
    @values = <CMD>;
    close(CMD);
    if( $? ){
      #non-zero return code from the program, exiting.
      print "\nError: failed to run $cmd.\n";
      exit(-1);
    }
  }

  foreach(@values){ s/\r?\n$//; }
  return @values;
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


