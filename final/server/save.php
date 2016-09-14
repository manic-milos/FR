<?php error_reporting(0);
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST, PUT, DELETE');

$method = $_SERVER['REQUEST_METHOD'];
// echo $method;

$input = json_decode(file_get_contents('php://input'),true);
// echo $input;

if($method=="POST"){
  $shortname='fr'.microtime(true).'_'.$input['name'];
  $name = mysql_real_escape_string('/opt/lampp/htdocs/fr/upload/'.$shortname);
  $data = mysql_real_escape_string($input['data']);

//   $name = '/tmp/'.microtime(true).'_'.$input['name'];
//   $data = $input['data'];

  $personname= $input['person'];
  $ifp = fopen($name, "wb");
  $datai = explode(',', $data);
  fwrite($ifp, base64_decode($datai[1]));
  fclose($ifp);
  //trazi da li postoji ta osoba upisana
  $namespath=mysql_real_escape_string('/opt/lampp/htdocs/fr/upload/names.csv');
  $namesfile = fopen($namespath, "r");
  $personNo=0;
  $found=false;
  while(($line = fgets($namesfile))!== false)
  {
    $personNo=$personNo+1;
    $cells=explode(';',$line);
    $currentName=trim($cells[1]);
    if($currentName==$personname)
    {
    //  echo $currentName;
      $personNo=$cells[0];
      $found=true;
      break;
    }
  }
  fclose($namesfile);
  //upisuje ako ne postoji, osoba dobija novu klasu
  if($found==false)
  {
    $namesfile = fopen($namespath, "a");
    fwrite($namesfile, $personNo.';'.$personname."\n");
    fclose($namesfile);
  }
  //upisuje u csv listu za trening
  $csvpath=mysql_real_escape_string('/opt/lampp/htdocs/fr/upload/train.csv');
  $csvfile=fopen($csvpath,"a");
  fwrite($csvfile,$name.';'.$personNo."\n");
  fclose($csvfile);
  $command="../../Server/Client F ".$shortname;
  $faceexec=exec($command,$returnvar);
//   echo $name;
  echo '{"meta": {"code": 200, "message": "Request successful"},"face":'.$faceexec.'}';
}

?>
