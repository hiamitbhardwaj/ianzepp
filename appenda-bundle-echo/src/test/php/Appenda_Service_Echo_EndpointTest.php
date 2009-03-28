<?php

require_once "PHPUnit/Framework.php";
require_once "Appenda/Loader.php";

/**
 *
 * @author Ian Zepp
 *
 */
class Appenda_Service_Echo_EndpointTest extends PHPUnit_Framework_TestCase {
	/**
	 * Enter description here...
	 *
	 * @return SimpleXMLElement
	 */
	private function newRequest () {
		$xml = simplexml_load_string ("<testRequest />");
		$xml->{"nested"} = __LINE__;
		$xml->{"nested"} ["attr0"] = __LINE__;
		$xml->{"nested"} ["attr1"] = __LINE__;
		$xml->{"nested"}->{"burrowed0"} = __LINE__;
		$xml->{"nested"}->{"burrowed1"} = __LINE__;
		$xml->{"nested"}->{"burrowed2"} = __LINE__;
		return $xml;
	}

	/**
	 * Enter description here...
	 *
	 * @return Appenda_Service_Echo_Endpoint
	 */
	private function newInstance () {
		return new Appenda_Service_Echo_Endpoint ();
	}

	/**
	 * Enter description here...
	 *
	 */
	public function testInstance () {
		$this->assertNotNull ($this->newInstance ());
	}

	/**
	 * Enter description here...
	 *
	 */
	public function testCopy () {
		$xml0 = $this->newRequest ();
		$xml1 = simplexml_load_string ("<testRequest />");
		$this->newInstance ()->copy ($xml0, $xml1);
		$this->assertEquals ($xml0->asXML (), $xml1->asXML ());
	}

	/**
	 * Enter description here...
	 *
	 */
	public function testProcessMessage () {
		$xml0 = $this->newRequest ();
		$xml1 = $this->newInstance ()->processMessage ($xml0);
		$this->assertEquals ("testRequest", $xml0->getName ());
		$this->assertEquals ("testResponse", $xml1->getName ());
		$this->assertEquals ($xml0->{"nested"}->asXML (), $xml1->{"nested"}->asXML ());
	}
}

