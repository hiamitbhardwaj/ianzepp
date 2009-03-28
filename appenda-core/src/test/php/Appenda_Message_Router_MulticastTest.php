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

class Appenda_Message_Router_Multicast_DelegateEndpoint implements Appenda_Message_Processor {
	public $receivedValue;
	
	public function processMessage (SimpleXMLElement $xml) {
		$this->receivedValue = (string) $xml ["value"];
		return $xml;
	}
}

class Appenda_Message_Router_Multicast_DelegateExceptionEndpoint implements Appenda_Message_Processor {
	public function processMessage (SimpleXMLElement $xml) {
		throw new Appenda_Exception ();
	}
}

class Appenda_Message_Router_Multicast_PrimaryDelegateEndpoint implements Appenda_Message_Processor {
	public function processMessage (SimpleXMLElement $xml) {
		$responseXml = simplexml_load_string ("<testResponse value='' />");
		$responseXml ["value"] = intval ($xml ["value"]) * 2;
		return $responseXml;
	}
}

class Appenda_Message_Router_Multicast_PrimaryDelegateExceptionEndpoint implements Appenda_Message_Processor {
	public function processMessage (SimpleXMLElement $xml) {
		throw new Appenda_Exception ();
	}
}

/**
 *
 * @author Ian Zepp
 *
 */
class Appenda_Message_Router_MulticastTest extends PHPUnit_Framework_TestCase {
	/**
	 * @expectedException 
	 */
	public function testDelegateEndpoint () {
		new Appenda_Message_Router_Multicast_DelegateEndpoint ();
	}
	
	/**
	 * @expectedException 
	 */
	public function testDelegateExceptionEndpoint () {
		new Appenda_Message_Router_Multicast_DelegateExceptionEndpoint ();
	}
	
	/**
	 * @expectedException Appenda_Exception
	 */
	public function testDelegateExceptionEndpointThrows () {
		$instance = new Appenda_Message_Router_Multicast_DelegateExceptionEndpoint ();
		$instance->processMessage (simplexml_load_string ("<testRequest />"));
	}
	
	/**
	 * @expectedException 
	 */
	public function testPrimaryDelegateEndpoint () {
		new Appenda_Message_Router_Multicast_PrimaryDelegateEndpoint ();
	}
	
	/**
	 * @expectedException 
	 */
	public function testPrimaryDelegateExceptionEndpoint () {
		new Appenda_Message_Router_Multicast_PrimaryDelegateExceptionEndpoint ();
	}
	
	/**
	 * @expectedException Appenda_Exception
	 */
	public function testPrimaryDelegateExceptionEndpointThrows () {
		$instance = new Appenda_Message_Router_Multicast_PrimaryDelegateExceptionEndpoint ();
		$instance->processMessage (simplexml_load_string ("<testRequest />"));
	}
	
	/**
	 * @expectedException
	 */
	public function testProcessMessage () {
		// Build the delegates
		$delegates ["Delegate01"] = new Appenda_Message_Router_Multicast_DelegateEndpoint ();
		$delegates ["Delegate02"] = new Appenda_Message_Router_Multicast_DelegateEndpoint ();
		$delegates ["Delegate03"] = new Appenda_Message_Router_Multicast_PrimaryDelegateEndpoint ();
		$delegates ["Delegate04"] = new Appenda_Message_Router_Multicast_DelegateEndpoint ();
		
		// Build the instance
		$instance = new Appenda_Message_Router_Multicast ();
		$instance->setDelegates ($delegates);
		$instance->setPrimaryDelegate ($delegates ["Delegate03"]);
		
		// Build the request xml
		$requestXml = simplexml_load_string ("<testRequest value='25' />");
		$responseXml = $instance->processMessage ($requestXml);
		
		// Test
		$this->assertNotNull ($responseXml);
		$this->assertEquals ("25", $delegates ["Delegate01"]->receivedValue);
		$this->assertEquals ("25", $delegates ["Delegate02"]->receivedValue);
		$this->assertEquals ("25", $delegates ["Delegate04"]->receivedValue);
		
		// Test the primary delegate response 
		$this->assertEquals ("testResponse", $responseXml->getName ());
		$this->assertEquals ("50", (string) $responseXml ["value"]);
	}
	
	/**
	 * @expectedException
	 */
	public function testProcessExceptionInDelegate () {
		// Build the delegates
		$delegates ["Delegate01"] = new Appenda_Message_Router_Multicast_DelegateEndpoint ();
		$delegates ["Delegate02"] = new Appenda_Message_Router_Multicast_DelegateEndpoint ();
		$delegates ["Delegate03"] = new Appenda_Message_Router_Multicast_DelegateExceptionEndpoint ();
		$delegates ["Delegate04"] = new Appenda_Message_Router_Multicast_DelegateEndpoint ();
		
		// Build the instance
		$instance = new Appenda_Message_Router_Multicast ();
		$instance->setDelegates ($delegates);
		$instance->processMessage (simplexml_load_string ("<testRequest />"));
	}
	
	/**
	 * @expectedException Appenda_Exception
	 */
	public function testProcessExceptionInPrimaryDelegate () {
		// Build the delegates
		$delegates ["Delegate01"] = new Appenda_Message_Router_Multicast_DelegateEndpoint ();
		$delegates ["Delegate02"] = new Appenda_Message_Router_Multicast_DelegateEndpoint ();
		$delegates ["Delegate03"] = new Appenda_Message_Router_Multicast_PrimaryDelegateExceptionEndpoint ();
		$delegates ["Delegate04"] = new Appenda_Message_Router_Multicast_DelegateEndpoint ();
		
		// Build the instance
		$instance = new Appenda_Message_Router_Multicast ();
		$instance->setDelegates ($delegates);
		$instance->setPrimaryDelegate ($delegates ["Delegate03"]);
		$instance->processMessage (simplexml_load_string ("<testRequest />"));
	}
}

