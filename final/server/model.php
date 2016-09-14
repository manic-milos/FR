<?php 
	$csvpath=mysql_real_escape_string('/opt/lampp/htdocs/fr/upload/train.csv');
	$csv = array_map('str_getcsv', file($csvpath)); 



	if(isset($_GET['action']))
	{
		if($_GET['action'] == 'delete' && isset($_GET['id']) && !is_nan(intval($_GET['id'])))
		{
			$id = intval($_GET['id']);
			$i = 0;
			$izlaz = "";
			foreach ($csv as $value) {
				echo $id." - ".$i;
				if($i != $id)
					$izlaz = $izlaz.$value[0]."\n";
				$i++;
			}

			file_put_contents($csvpath, $izlaz); 
			//Treniranje ne treba
			
		}
		else if($_GET['action'] == 'train' && isset($_FILES['image']) && isset($_POST['name']))
		{
			$url = $_FILES["image"]["tmp_name"];
			$name = $_POST['name'];
			$imgname = $_FILES["image"]["name"];

			$path = "img/persons/"; // OVDE STAVI PUTANJU KOJA TI ODGOVARA I NE ZABORAVI / NA KRAJU

			if(move_uploaded_file($url, $path.$imgname))
			{
				$izlaz = $path.$imgname.";".$name."\n";
				file_put_contents($csvpath, $izlaz, FILE_APPEND); // PROMENI PUTANJU DO CSV FAJLA

				//Treniranje
				$command="../../Server/Client T train.csv";
				$returns=exec($command,$returnvar);
			}

		}

		header("Location: model.php");
	}

?>


<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Face recognition</title>
	<link rel="stylesheet" href="style.css">
</head>
<body>
	<div class="wrap">
		<div class="pattern">
			<div class="app">
				<header>
					<h1 class="title">Face recognition</h1>

				</header>
				<p class="look">Model Training</p>

				<canvas id="screenshot"></canvas>

				
				<?php $i = 0; foreach ($csv as $value) {  ?>
					<div class="person">
						<div class="image" style="background-image: url(<?php echo explode(';',$value[0])[0]; ?>)">	</div>
						<div class="name"> <p><?php echo explode(';',$value[0])[1]; ?></p></div>
						<div class="delete"><a href="model.php?action=delete&id=<?php echo $i; ?>"><img src="img/delete.png" alt=""></a></div>
					</div>

				<?php $i++; } ?>

				<form action="./model.php?action=train" method="post" enctype="multipart/form-data" charset="utf-8">
						<p class="caption">Add new image to model</p>
						<label for="name">Person's name: </label>
						<input type="text" name="name">
						<br>	
						<br>	
						<label for="image">Person's image: </label>
						<input type="file" name="image">
						<input type="submit" class="scan" value="Add new image">
				</form>

			</div>
		</div>
	</div>

	<script>

	

	</script>

</body>
</html>
