<?php
	$conn;
	function getConn() {
		//$GLOBALS["conn"] = mysql_connect("cdb-jtnu9xs0.cd.tencentcdb.com:10028","root","lanbin123456");
		$GLOBALS["conn"] = mysqli_connect("cdb-jtnu9xs0.cd.tencentcdb.com:10028", "root", "lanbin123456", "calculate24");
		if (!$GLOBALS["conn"]) {
			die('Could not connect: ' . mysqli_connect_error());
		}
		//mysql_select_db("calculate24");
		//mysql_query("set names 'utf8'");
		$GLOBALS["conn"]->query("SET NAMES 'utf8'");
		return $GLOBALS["conn"];
	}

	function closeDB() {
		//mysql_close($GLOBALS["conn"]);
		mysqli_close($GLOBALS["conn"]);
	}

	function db_execute($sql) {
		echo "execute sql is ".$sql."\n";
		$id = null;
		$conn = $GLOBALS["conn"];
		if(!$conn) {
			echo "database connection aborted\n";
			$conn = getConn();
			$GLOBALS["conn"] = $conn;
		} else if(!mysqli_ping($conn)) {
			echo "database connection has gone away\n";
			$conn = getConn();
			$GLOBALS["conn"] = $conn;
		}
		if(mysqli_query($conn,$sql)) {
			echo "insert success.\n";
			$id = mysqli_insert_id($conn);
			echo "new id is:".$id."\n";
		} else {
			echo "insert failure.(".mysqli_errno($conn).")".mysqli_error($conn)."\n";
			echo "reconnect database.\n";
			$conn = getConn();
			$GLOBALS["conn"] = $conn;
			mysqli_query($conn, $sql);
			$id = mysqli_insert_id($conn);
			echo "insert success, new id is ".$id."\n";
		}
		return $id;
	}
?>