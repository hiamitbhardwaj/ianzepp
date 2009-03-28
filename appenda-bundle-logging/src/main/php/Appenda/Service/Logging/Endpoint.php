<?php

/**
 *
 * @author Ian Zepp
 *
 */
abstract class Appenda_Service_Logging_Endpoint extends Appenda_Endpoint
{
	/**
	 * @var Zend_Db_Table_Abstract
	 */
	private $eventTable;

	/**
	 * Enter description here...
	 *
	 * @return Zend_Db_Table_Abstract
	 */
	public function getEventTable()
	{
		return $this->eventTable;
	}

	/**
	 * Enter description here...
	 *
	 * @param Zend_Db_Table_Abstract $sessionTable
	 */
	public function setEventTable(Zend_Db_Table_Abstract $tableTable)
	{
		$this->eventTable = $eventTable;
	}
}