<?php

/**
 *
 * @author Ian Zepp
 *
 */
class Appenda_Service_Session_InsertEventEndpoint extends Appenda_Service_Logging_Endpoint {
	/**
	 *
	 * @param SimpleXMLElement $request
	 * @return SimpleXMLElement
	 */
	public function processMessage (SimpleXMLElement $xml) {
		// Convert to an array
		$insert ["level"] = (string) $xml->{"level"};
		$insert ["message"] = (string) $xml->{"message"};
		
		// Insert into the DB
		$this->getEventTable ()->insert ($insert);
	}
}