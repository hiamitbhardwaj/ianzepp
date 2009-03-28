<?php

/**
 *
 * @author Ian Zepp
 *
 */
class Appenda_Service_Session_InsertEndpoint extends Appenda_Service_Session_Endpoint {
	/**
	 * Enter description here...
	 *
	 * @param SimpleXMLElement $xml
	 * @return SimpleXMLElement
	 */
	public function processMessage (SimpleXMLElement $xml) {
		$this->getSessionTable ()->insert ($xml->asXML());
	}
}

