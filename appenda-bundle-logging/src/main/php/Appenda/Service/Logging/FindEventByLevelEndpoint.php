<?php

/**
 *
 * @author Ian Zepp
 *
 */
class Appenda_Service_Session_FindEventByLevelEndpoint extends Appenda_Service_Logging_Endpoint {
	/**
	 *
	 * @param SimpleXMLElement $request
	 * @return SimpleXMLElement
	 */
	public function processMessage (SimpleXMLElement $xml) {
		// Build the basic result xml
		$responseXml = simplexml_load_string ("<findEventByLevelResponse />");
		$responseXml ["xmlns"] = array_shift ($xml->getNamespaces (false));
		
		// Fetch first match
		$select = $this->getEventTable ()->select ();
		$select->where ("level = ?", (string) $xml);
		$result = $this->getEventTable ()->fetchRow ($select)->toArray ();
		
		// Is there a match?
		if (!empty ($result)) {
			$responseXml->{"level"} = $result ["level"];
			$responseXml->{"message"} = $result ["message"];
		}
		
		return $responseXml;
	}
}