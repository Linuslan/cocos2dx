<?php
	class GameRoom {
		private $id;
		private $roomNo;
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
		public function getRoomNo() {
			return $roomId;
		}
		public function setRoomNo($roomNo) {
			$this->roomNo = $roomNo;
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