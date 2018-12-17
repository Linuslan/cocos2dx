<?php
	$conn;
	function getConn() {
		$GLOBALS["conn"] = mysql_connect("cdb-jtnu9xs0.cd.tencentcdb.com:10028","root","lanbin123456");
		if (!$GLOBALS["conn"]) {
			die('Could not connect: ' . mysql_error());
		}
		mysql_select_db("calculate24");
		mysql_query("set names 'utf8'");
		return $GLOBALS["conn"];
	}

	function closeDB() {
		mysql_close($GLOBALS["conn"]);
	}

	function db_execute($sql) {
		echo "execute sql is ".$sql."\n";
		$id = null;
		if(!$GLOBALS["conn"]) {
			echo "database connection aborted\n";
			getConn();
		} else if(!mysql_ping($GLOBALS["conn"])) {
			echo "database connection has gone away\n";
			getConn();
		}
		if(mysql_query($sql, $GLOBALS["conn"])) {
			echo "insert success.\n";
			$id = mysql_insert_id();
			echo "new id is:".$id."\n";
		} else {
			echo "insert failure.(".mysql_errno().")".mysql_error()."\n";
			echo "reconnect database.\n";
			getConn();
			mysql_query($sql, $GLOBALS["conn"]);
			$id = mysql_insert_id();
			echo "insert success, new id is ".$id."\n";
		}
		return $id;
	}
?>