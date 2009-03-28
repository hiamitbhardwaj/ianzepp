<?php

/**
 *
 * @author Ian Zepp
 *
 */
class Appenda_Service_Echo_Endpoint implements Appenda_Endpoint {
	/**
	 *
	 * @param SimpleXMLElement $request
	 * @return SimpleXMLElement
	 */
	public function processMessage (SimpleXMLElement $xml) {
		$responseTag = str_replace ("Request", "Response", $xml->getName ());
		$responseXml = simplexml_load_string ("<{$responseTag} />");
		$responseXml ["xmlns"] = array_shift ($xml->getNamespaces (false));
		return $this->copy ($xml, $responseXml);
	}

	/**
	 * Recursive copy
	 *
	 * @param SimpleXMLElement $source
	 * @param SimpleXMLElement $target
	 * @return SimpleXMLElement
	 */
	public function copy (SimpleXMLElement $source, SimpleXMLElement $target) {
		foreach ($source->attributes () as $name => $data) {
			$target [$name] = (string) $data;
		}

		foreach ($source->children () as $childSource) {
			$childTarget = $target->addChild ($childSource->getName (), (string) $childSource);
			$this->copy ($childSource, $childTarget);
		}

		return $target;
	}
}