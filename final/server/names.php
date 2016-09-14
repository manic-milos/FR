<?php

$namespath=mysql_real_escape_string('/opt/lampp/htdocs/fr/upload/names.csv');
  $namesfile = fopen($namespath, "r");

  while(($line = fgets($namesfile))!== false)
  {
    $cells=explode(';',$line);
    $currentName=trim($cells[1]);
    echo '<option value="'.$currentName.'"></option>';
  }
  fclose($namesfile);

?>