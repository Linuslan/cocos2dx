<?php
	class GameRoom {
		private $id;
		private $roomId;
		private $roomName;
		private $status;
		private $password;
		private $createTime;
		public function getId() {
			return $id;
		}
		public function setId($id) {
			$this->id = $id;
		}
		public function getRoomId() {
			return $roomId;
		}
		public function setRoomId($roomId) {
			$this->roomId = $roomId;
		}
		public function getRoomName() {
			return $roomName;
		}
		public function setRoomName($roomName) {
			$this->roomName = $roomName;
		}
		public function getStatus() {
			return $status;
		}
		public function setStatus($status) {
			$this->status = $status;
		}
		public function getPassword() {
			return $password;
		}
		public function setPassword($password) {
			$this->password = $password;
		}
		public function getCreateTime() {
			return $createTime;
		}
		public function setCreateTime($createTime) {
			$this->createTime = $createTime;
		}

	}
?>