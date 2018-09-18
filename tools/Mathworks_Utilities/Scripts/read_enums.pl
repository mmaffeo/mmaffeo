#!/usr/bin/perl
use strict;

my %symbol_table; #used to store symbol/value pairs and to detect multiple declarations
my $output_file = 'enums.m'; #output matlab file
my $global_data_type = undef; #global data type hint

my $exec_name = $0;
$exec_name =~ s{^.*(\\|/)}{};

my $usage = "
Generates an m-file from a c header file that contains all the 'enum'
symbols therein.  Processing of a file's contents stops if
'MATLAB_STOP_READING' is encountered.

WARNING: this script is not a compiler!  It does not follow #include
directives.  Complicated definitions may confuse it.

usage: $exec_name [-o <output file name>] <input header files...>
  -o <output file name> use this output file name (default enums.m)
  -t <type> cast all matlab variables to <type>.  <type> may be of the form
     'uint16', 'fixdt_0_16_8', or variations thereof.

An 'enum' keyword followed by  //fixdt_0_16_8 or //int8, etc have its elements
cast to that data type.  This overrides the -t option.  Examples:
  enum //int32
  { /*all of these values will be cast to int32*/ };
  typedef enum foobar //uint8
  { /*all of these values will be cast to uint8*/ }foobar_t;
";

#check arguments
while($ARGV[0] =~ m/^-([A-Za-z]+)$/){
  my $flags = $1;
  shift @ARGV; #remove flags token from args array
  foreach(split(//, $flags)){
    if($_ eq 'h'){
      print $usage;
      exit(0);
    }elsif($_ eq 'o'){
      $output_file  = shift @ARGV;
    }elsif($_ eq 't'){
      $global_data_type  = process_hint( shift @ARGV, '-t');
    }else{
      print STDERR "unknown flag '$_'\n";
      exit(-1);
    }
  }
}

if(@ARGV <= 0 ){ #no input files
  print STDERR "missing file arguments\n";
  exit(1);
}

#test all input files before clobbering the output file
foreach my $input_file (@ARGV){
  -r $input_file or die "Error: coudn't read from file $input_file.\n";
}

#open output file
open( OFH, ">$output_file" ) or die "couldn't open $output_file: $!\n";

#process each input file
foreach my $input_file (@ARGV){

  my $short_name = $input_file; #strip path from file name
  $short_name =~ s{^.*(\\|/)}{};
  
  #slurp in file for comment processing
  my $file_contents;
  {
    open( CD_H_FILE, "<$input_file") or die "Error: couldn't open $input_file: $!\n";
    local( $/ );
    $file_contents = <CD_H_FILE>;
    close CD_H_FILE;
  }

  #remove sections we're not supposed to process
  $file_contents =~ s/MATLAB_STOP_READING.*\z//s;
  
  #strip commented code
  #$file_contents =~ s{//.*?(\r?\n)}{$1}gxs; #// comments

  #strip commented code
  $file_contents =~  s{ #// comments
    //
    (?! \s* fixdt[_0-9]+ | \s* u?int[0-9]+ ) #leave comment alone if it looks like //fixdt_0_16_8 or uint16, etc
    .*?
    (\r?\n)
  }{$1}gxs;
  $file_contents =~ s{/\*.*?\*/}{}gs;    #/**/ comments

  #concatenate continued lines into one line
  $file_contents =~ s{\\\n}{}gs;

  print OFH "\n\%input file: $input_file\n";
  
  #find enums
  while( $file_contents =~ m<
    enum                                       #enum declaration w/o typedef
    (?: \s+ ([A-Za-z_][A-Za-z_0-9]*) )? \s*    #enum name (if defined)
    (?: //\h*([^\r\n]*) \r?\n)?                # data type hint (optional)
    \{ ([^\}]*) \} \s* ;                       #body
    |
    typedef \s* enum                           #enum declaration w/ typedef
    (?: \s+ [A-Za-z_][A-Za-z_0-9]* )? \s*      #enum name (if defined)
    (?: //\h*([^\r\n]*) \r?\n)?                # data type hint (optional)
    \{ ([^\}]*) \} \s*                         #body
    ([A-Za-z_][A-Za-z_0-9]*) \s*;              #typedef name
  >xgs ){
    my ($enum_body, $header, $hint);
    my @print_list;

    my ($enum_name, $hint1, $body1, $hint2, $body2, $typedef_name) = ($1, $2, $3, $4, $5, $6);
    if(defined $typedef_name){ $header = "$typedef_name (typedef enum)";    $enum_body = $body2; $hint=$hint2}
    elsif(defined $enum_name){ $header = "$enum_name (enum)";               $enum_body = $body1; $hint=$hint1}
    else                     { $header = "anonymous enum";                  $enum_body = $body1; $hint=$hint1}

    print OFH "%$header:\n";

    #try to establish a data type for these enumerated values
    my $data_type;
    if( defined($hint) ){
      $data_type = process_hint($hint, $typedef_name);
    }
    if( !defined($data_type) ){
      $data_type = $global_data_type;
    }
    
    #parse out members & values
    my @members;
    my $value = -1;
    $enum_body =~ s{//.*?(\r?\n)}{$1}gxs; #// comments
    while($enum_body =~ m<
      \G\s*
      ([A-Za-z_][A-Za-z_0-9]*) \s*   #enum symbol
      (?: =\s* ([A-Za-z_0-9]+) )?    #value (optional)
      \s*,?
    >gxs){
      my $symbol = $1;
      if(defined $2){
        $value = $2;
        if($value =~ m/^0[xX]/){ #convert hex values
          $value = hex($value);
        } 
      }else{
        $value++;
      }
  
      #duplicate symbol check
      if(exists($symbol_table{$symbol})){
        print STDERR "Warning: duplicate symbol '$symbol' found in '$header'. (file: '$input_file')\n";
      }

      #set the symbol in the table
      $symbol_table{$symbol} = $value;

      my $tmp_value = $value;

      if(defined $data_type){
        $tmp_value = $data_type->{MATLAB_prefix} . sprintf( $data_type->{MATLAB_format}, $tmp_value) . $data_type->{MATLAB_suffix};
      }
      push(@print_list, [ $symbol, "= Bobcat.Parameter; CreateDefine(", $symbol, ",$tmp_value", ",'Define'", ",'$short_name'", ');' ] );
    }

    #dump symbols to matlab m-file
    pretty_print(\@print_list);
  }
}

close OFH;

### subs ########################################

sub pretty_print{
#Prints a 2D array of strings aligned by column.
#Warning: assumes that all rows are the same width.
#example: 
# my @ex = (['a', 'bbb', 'cc'],['ddd','e','ffff']);
# pretty_print(\@ex);
# >> a   bbb cc
# >> ddd e   ffff
  my ($array_ref) = @_;
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
      print OFH $array_ref->[$i][$j] . (' ' x $pad_len );
    }
    print OFH "\n";
  }
}


sub process_hint{
# process a data type hint
# returns: a data type (if one was could be read), otherwise undefined

  my ($hint, $symbol) = @_;
  my %data_type;
  $hint =~ s/^\s+|\s+$//;
  
  if(!defined $hint){
    return;
  }
  
  #look for fixdt_#_#_# in the description
  if($hint =~ m{ ( fixdt (\S+) ) }x){
    my ( $hint, $hint_args ) = ($1, $2);
    if($hint_args =~ m{ ^_ ([01]) _ ([0-9]+) _ (-?[0-9]+) $}x ){
      my ($sign, $bits, $fraction) = ($1,$2,$3);
      $data_type{'C'} = (($sign)?'':'u') . 'int' . $bits . '_t';
      $data_type{'bits'} = $bits;
      $data_type{'sign'} = $sign;
      $data_type{'fraction'} = $fraction;
      $data_type{'MATLAB_prefix'} = "fi(0,$sign,$bits,$fraction,'hex',";
      $data_type{'MATLAB_suffix'} = ")";
      $data_type{'MATLAB_format'} = "'%0". $bits/4 ."x'"; #uniform padded hexadecimal formatting required
    }
  }

  #look for uint8_t etc, in the description
  if($hint =~ m{ ( (u)?int(8|16|32|64) ) (?: _[tT] )? (?: $ | \s+ ) }x){
    $data_type{'C'} = $1.'_t';
    $data_type{'bits'} = $3;
    $data_type{'sign'} = !defined $2;
    $data_type{'fraction'} = 0;
    $data_type{'MATLAB_prefix'} = "$1(";
    $data_type{'MATLAB_suffix'} = ')';
    $data_type{'MATLAB_format'} = '%d';
  }

  if(!%data_type){
    print STDERR "Warning: Could not find a valid data type matching hint '$hint' for '$symbol'.\n";
    return undef;
  }else{
    return \%data_type;  
  }
}
