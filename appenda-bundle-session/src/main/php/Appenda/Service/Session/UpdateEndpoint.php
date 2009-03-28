<?php

/**
 *
 * @author Ian Zepp
 *
 */
class Appenda_Service_Session_UpdateEndpoint extends Appenda_Service_Session_Endpoint {
	/**
	 *
	 * @param SimpleXMLElement $request
	 * @return SimpleXMLElement
	 */
	public function processMessage (SimpleXMLElement $xml) {
		// Convert to an array
		$insert ["name"] = (string) $xml->{"name"};
		$insert ["data"] = (string) $xml->{"data"};
		$insert ["created_at"] = (string) time ();
		$insert ["updated_at"] = (string) time ();
		
		// Push it
		$table = $this->getSessionTable ();
		$where = $table->getAdapter ()->quoteInto ("name = ?", $insert ["name"]);
		$table->update ($insert, $where);
	}
}

