 
<?php
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST, PUT, DELETE');

$method = $_SERVER['REQUEST_METHOD'];
// echo $method;

$input = json_decode(file_get_contents('php://input'),true);
// echo $input;

if($method=="POST"){
$microtime=microtime(true);
  $name = mysql_real_escape_string('/opt/lampp/htdocs/fr/upload/'.$microtime.'_'.$input['name']);
  $data = mysql_real_escape_string($input['data']);

  $shortname=mysql_real_escape_string($microtime.'_'.$input['name']);
//   $name = '/tmp/'.microtime(true).'_'.$input['name'];
//   $data = $input['data'];

  
  $ifp = fopen($name, "wb");
  $datai = explode(',', $data);
  fwrite($ifp, base64_decode($datai[1]));
  fclose($ifp);
  
  //pamcenje
  $chmoded = chmod($name,0777); 
  if (!$chmoded){echo "Could not change the file permissions";}
  
  //izvrsavanje komande za prepoznavanje
  $command="../../Server/Client R ".$shortname." ";
  $returns=exec($command,$returnvar);

  
  //dekodiranje jsona vracenog iz exec
  $jsondata=json_decode($returns,true);
  if($jsondata['success']==1)
  {
    $predictedClass=$jsondata['predicted'];
    
    //nalazenje imena coveka iz fajla na osnovu klase
    $namespath=mysql_real_escape_string('/opt/lampp/htdocs/fr/upload/names.csv');
    $namesfile = fopen($namespath, "r");
    $found=false;
	$jsondata2 = array();
    while(($line = fgets($namesfile))!== false)
    {
      $cells=explode(';',$line);
      $currentName=trim($cells[1]);
      if($cells[0]==$predictedClass)
      {
// 	echo $cells[1];
	$personName=trim($cells[1]);
	$jsondata2['predicted']=$personName;
	$found=true;
	break;
      }
    }
    fclose($namesfile);
    
    //vraca se prva slika koja je upisana u model za tu osobu
    $csvpath=mysql_real_escape_string('/opt/lampp/htdocs/fr/upload/train.csv');
    $csvfile=fopen($csvpath,"r");
    while(($line = fgets($csvfile))!== false)
    {
      $cells=explode(';',$line);
      $classno=trim($cells[1]);
      if($classno==$predictedClass)
      {
	$imagepath=trim($cells[0]);
	$imagedata = file_get_contents($imagepath);
	$base64 = base64_encode($imagedata);
	$base64src = 'data: '.mime_content_type($imagepath).';base64,'.$base64;
	$jsondata2['data']=$base64src;
	break;
      }
    }

	exec("rm ../../upload/".$shortname);
	
    echo '{"name":"'.$personName.'","confidence":'.$jsondata['confidence'].', "data":"'.$base64src.'"}';
	
  }
  else
  {
		exec("rm ../../upload/".$shortname);

    //nije prepoznao lice
    echo '{"meta":{"code":"404"}}';
  }
//   echo $jsondata;
//   echo $returnvar;
//   echo $name;
//   echo '{"meta": {"code": 200, "message": "Request successful"}, "data": "'.$data.'"}';
}

?>
