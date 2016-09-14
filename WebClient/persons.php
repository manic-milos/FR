<?

	$fh = fopen("db/db.dat", 'r');
	$i=0;
	while($line = fgets($fh))
	{
		$info = explode(';', $line);
		//var_dump($info);
		$persons[trim($info[2])][] = $i++;
	}
	//var_dump($persons);
	fclose($fh);

	$id = $_GET['id'];

?>

<html>
	<head>
		<title>Face Recognition - Person <?php echo $id?></title>
	</head>
	<body>
	<h1>Original images</h1>
	<?
	for($i=0; $i<count($persons[$id]); $i++)
	{
		echo '<img src="db/orig/' . $persons[$id][$i] . '.png">';
	}
	?>
	<h1>Prepared images</h1>
	<?
	for($i=0; $i<count($persons[$id]); $i++)
	{
		echo '<img src="db/prepared/' . $persons[$id][$i] . '.png">';
	}
	?>
	</body>
</html>