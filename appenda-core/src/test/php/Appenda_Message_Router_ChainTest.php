<?php

/**
 * The MIT License
 * 
 * Copyright (c) 2009 Ian Zepp
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * @author Ian Zepp
 * @package 
 */

require_once "PHPUnit/Framework.php";
require_once "Appenda/Loader.php";

class Appenda_Message_Router_Chain_Exception extends Exception {}

class Appenda_Message_Router_Chain_ExceptionEndpoint implements Appenda_Message_Processor  {
	public function processMessage (SimpleXMLElement $xml) {
		throw new Appenda_Message_Router_Chain_Exception ();
	}
}

class Appenda_Message_Router_Chain_IncrementingEndpoint implements Appenda_Message_Processor {
	public function processMessage (SimpleXMLElement $xml) {
		$xml ["value"] = intval ($xml ["value"]) + 5;
		return $xml;
	}
}

class Appenda_Message_Router_ChainTest extends PHPUnit_Framework_TestCase {
	/**
	 * @expectedException
	 */
	public function testProcessMessage () {
		// Build the delegates
		$delegates ["Incrementing01"] = new Appenda_Message_Router_Chain_IncrementingEndpoint ();
		$delegates ["Incrementing02"] = new Appenda_Message_Router_Chain_IncrementingEndpoint ();
		$delegates ["Incrementing03"] = new Appenda_Message_Router_Chain_IncrementingEndpoint ();

		// Build the instance
		$instance = new Appenda_Message_Router_Chain ();
		$instance->setDelegates ($delegates);

		// Build the request xml
		$requestXml = simplexml_load_string ("<testRequest value='25' />");
		$responseXml = $instance->processMessage ($requestXml);

		// Test
		$this->assertNotNull ($responseXml);
		$this->assertEquals ("40", (string) $responseXml ["value"]);
	}

	/**
	 * @expectedException Appenda_Exception
	 */
	public function testProcessMessageWithException () {
		// Build the delegates
		$delegates ["Incrementing01"] = new Appenda_Message_Router_Chain_IncrementingEndpoint ();
		$delegates ["Exception01"] = new Appenda_Message_Router_Chain_ExceptionEndpoint ();
		$delegates ["Incrementing02"] = new Appenda_Message_Router_Chain_IncrementingEndpoint ();

		// Build the instance
		$instance = new Appenda_Message_Router_Chain ();
		$instance->setDelegates ($delegates);

		// This should throw an exception
		$instance->processMessage (simplexml_load_string ("<testRequest />"));
	}
}

