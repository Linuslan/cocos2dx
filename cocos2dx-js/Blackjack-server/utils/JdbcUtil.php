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
?>