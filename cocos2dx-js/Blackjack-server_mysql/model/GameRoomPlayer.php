<?php
	class GameRoomPlayer {
		private $id;
		private $roomId
		private $playerId;
		private $status;
		private $score;
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
			return $this->roomId = $roomId;
		}
		public function getPlayerId() {
			return $playerId;
		}
		public function setPlayerId($playerId) {
			$this->playerId = $playerId;
		}
		public function getStatus() {
			return $status;
		}
		public function setStatus($status) {
			$this->status = $status;
		}
		public function getScore() {
			return $score;
		}
		public function setScore($score) {
			$this->score = $score;
		}
	}
?>