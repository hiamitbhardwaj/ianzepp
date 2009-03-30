<?php

/**
 *
 * @author Ian Zepp
 *
 */
class Appenda_Service_Session_FindByNameEndpoint extends Appenda_Service_Session_Endpoint {
	/**
	 *
	 * @param SimpleXMLElement $request
	 * @return SimpleXMLElement
	 */
	public function processMessage (SimpleXMLElement $xml) {
		// Build the basic result xml
		$responseXml = simplexml_load_string ("<findByNameResponse />");
		$responseXml ["xmlns"] = array_shift ($xml->getNamespaces (false));
		
		// Fetch first match
		$select = $this->getSessionTable ()->select ();
		$select->where ("name = ?", (string) $xml);
		$result = $this->getSessionTable ()->fetchRow ($select)->toArray ();
		
		// Is there a match?
		if (empty ($result)) {
			return $responseXml;
		}
		
		// Is the session invalid (timed out)?
		if (intval ((string) $responseXml->{"expires_at"}) >= time ()) {
			return $responseXml;
		}
		
		// Build and return the result
		$responseXml->{"name"} = $result ["name"];
		$responseXml->{"data"} = $result ["data"];
		$responseXml->{"created_at"} = $result ["created_at"];
		$responseXml->{"updated_at"} = $result ["updated_at"];
		$responseXml->{"expires_at"} = $result ["expires_at"];
		return $responseXml;
	}
}