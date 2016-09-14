<html>
<head>
	<title>Face Recognition</title>
</head>
<body>
	<form action="" method="post" enctype="multipart/form-data">
		<table>
			<tr>
				<td>
					Akcija:
				</td>
				<td>
					<select name="action">
						<option value="A">Dodavanje fotografije u model</option>
						<option value="R">Prepoznavanje fotografije</option>
						<option value="T">Treniranje modela</option>
						<option value="M">Prepoznavanje seta fotografija</option>
					</select>
				</td>
			</tr>
			<tr>
				<td>
					Fajl:
				</td>
				<td>
					<input type="file" name="file" />
				</td>
			</tr>
			<tr>
				<td>
					Port:
				</td>
				<td>
					<input name="port" />
				</td>
			</tr>
			<tr>
				<td>
					&nbsp;
				</td>
				<td>
					<input type="submit" name="submit" value="Obradi!" />
				</td>
			</tr>
		</table>
	</form>
	<br />
	<br />

	<?php

		error_reporting(E_ALL);

		if(!empty($_POST))
		{			

			set_time_limit(0);
			ob_implicit_flush();

			$service_port = $_POST['port'];

			//$service_port = 30000;

			$address = 'localhost';

			$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
			if ($socket === false) {
			    echo "socket_create() failed: reason: " . 
			         socket_strerror(socket_last_error()) . "\n";
			}

			echo "Attempting to connect to '$address' on port '$service_port'...";
			$result = socket_connect($socket, $address, $service_port);
			if ($result === false) {
			    echo "socket_connect() failed.\nReason: ($result) " . 
			          socket_strerror(socket_last_error($socket)) . "\n";
			}

			$action = $_POST['action'];
			$personID = $_POST['personID'];

			if ($_FILES["file"]["error"] > 0)
		    {
		    	echo "Return Code: " . $_FILES["file"]["error"] . "<br>";
		    }
		  	else
		    {
			    echo "Upload: " . $_FILES["file"]["name"] . "<br>";
			    echo "Type: " . $_FILES["file"]["type"] . "<br>";
			    echo "Size: " . ($_FILES["file"]["size"] / 1024) . " kB<br>";
			    echo "Temp file: " . $_FILES["file"]["tmp_name"] . "<br>";

			    $desiredFilename = $_FILES["file"]["name"];

			    $destination = "upload/" . $desiredFilename;

			    $fileName = $_FILES["file"]["name"];

			    $i = 0;

			    while (file_exists($destination))
			    {
			    	$i++;
			    	$fileName = $desiredFilename . "_" . $i;
			    	$destination = "upload/" . $fileName;
			    }

		    	move_uploaded_file($_FILES["file"]["tmp_name"],	$destination);
		    	echo "Stored in: " . $destination;
			    
		    }

		    if($action == 'A')
		    	$msg = $action . $fileName . ';' . $personID;
		    else
		    	$msg = $action.$fileName;

			$out = '';

			echo "Sending HTTP HEAD request...";
			socket_write($socket, $msg, strlen($msg));
			echo "OK.\n";

			echo "Reading response:\n\n";
			$response = socket_read($socket, 1000, PHP_NORMAL_READ);
			echo $response;

			socket_close($socket);
		}
	?>

</body>
</html>