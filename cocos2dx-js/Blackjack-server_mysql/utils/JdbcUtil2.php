<?php
	$cur_dir=dirname(__FILE__);
	chdir($cur_dir);
	include_once "../Workerman/MySQL/Connection.php";
	use Workerman\MySQL;
	$conn;
	function getConn() {
		echo "get connection from JdbcUtil2.getConn().\n";
		$GLOBALS["conn"] = new \Workerman\MySQL\Connection('cdb-jtnu9xs0.cd.tencentcdb.com', '10028', 'root', 'lanbin123456', 'calculate24');
		if (!$GLOBALS["conn"]) {
			die('Could not connect: ' . mysql_error());
		}
		$conn = $GLOBALS["conn"];
		$conn->query("set names 'utf8'");
		return $GLOBALS["conn"];
	}

	function closeDB() {
		mysql_close($GLOBALS["conn"]);
	}

	function db_execute($sql) {
		echo "execute JdbcUtil2.db_execute().\n";
		echo "execute $sql.\n";
		return $GLOBALS["conn"]->query($sql);
	}
?>