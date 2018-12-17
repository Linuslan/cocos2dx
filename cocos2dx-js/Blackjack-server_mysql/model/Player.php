<?php
	class Player {
		private $id;
		private $openid;
		private $userName;
		private $score;
		private $loginTime;
		private $createTime;
		private $websocketId;
		public function getId() {
			return $id;
		}
		public function setId($id) {
			$this->id = $id;
		}
		public function getOpenid() {
			return $openid;
		}
		public function setOpenid($openid) {
			$this->openid = $openid;
		}
		public function getUserName() {
			return $userName;
		}
		public function setUserName($userName) {
			$this->userName = $userName;
		}
		public function getScore() {
			return $score;
		}
		public function setScore($score) {
			$this->score = $score;
		}
		public function getLoginTime() {
			return $loginTime;
		}
		public function setLoginTime() {
			$this->loginTime = $loginTime;
		}
		public function getCreateTime() {
			return $createTime;
		}
		public function setCreateTime($createTime) {
			$this->createTime = $createTime;
		}
		public function getWebsocketId() {
			return $websocketId;
		}
		public function setWebsocketId($websocketId) {
			$this->websocketId = $websocketId;
		}
	}
?>