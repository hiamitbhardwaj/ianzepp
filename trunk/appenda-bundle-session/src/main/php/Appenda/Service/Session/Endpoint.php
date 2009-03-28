<?php

/**
 *
 * @author Ian Zepp
 *
 */
abstract class Appenda_Service_Session_Endpoint implements Appenda_Endpoint {
	private $sessionTable;
	private $expirationTime;
	
	/**
	 * @return integer
	 */
	public function getExpirationTime () {
		return $this->expirationTime;
	}
	
	/**
	 * Enter description here...
	 *
	 * @return Zend_Db_Table_Abstract
	 */
	public function getSessionTable () {
		return $this->sessionTable;
	}
	
	/**
	 * @param string|int $expirationTime
	 */
	public function setExpirationTime ($expirationTime) {
		assert (is_integer ($expirationTime) || preg_match ("/^([0-9])+$/", $expirationTime));
		$this->expirationTime = intval ($expirationTime);
	}
	
	/**
	 * Enter description here...
	 *
	 * @param Zend_Db_Table_Abstract $sessionTable
	 */
	public function setSessionTable (Zend_Db_Table_Abstract $sessionTable) {
		$this->sessionTable = $sessionTable;
	}
	
}