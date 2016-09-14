<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST, PUT, DELETE');
  
  $command="../../Server/Client T train.csv";
  exec($command,$returnvar);
  echo '{"meta":{"status":"200","response":"ok"}}';

?>
