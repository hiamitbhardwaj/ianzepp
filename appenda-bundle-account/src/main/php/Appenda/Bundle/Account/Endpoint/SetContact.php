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
 * @package Appenda.Bundle.Account
 */

class Appenda_Bundle_Account_Endpoint_SetContact extends Appenda_Bundle_Account_Endpoint {
	/**
	 * Enter description here...
	 *
	 * @param SimpleXMLElement $xml
	 * @return SimpleXMLElement
	 */
	public function processMessage (SimpleXMLElement $xml) {
		// Build the status response in advance
		$responseXml = simplexml_load_string ("<{$xml->getName ()} />");
		$responseXml->addAttribute ("xmlns", array_shift ($xml->getNamespaces ()));
		$responseXml->{"model"} = "Contact";
		$responseXml->{"modelId"} = null;
		$responseXml->{"success"} = true;
		
		try {
			// Try to add the contact
			$row = $this->getContacts ()->createRow ();
			$row->{"firstName"} = $xml->{"firstName"};
			$row->{"middleName"} = $xml->{"middleName"};
			$row->{"lastName"} = $xml->{"lastName"};
			$row->save ();
			
			// If successful, add the id
			$responseXml->{"modelId"} = $row->{"contact_id"};
		} catch (Exception $exception) {
			$responseXml->{"success"} = false;
			$responseXml->{"exceptionType"} = get_class ($exception);
			$responseXml->{"exceptionMessage"} = $exception->getMessage ();
		}
		
		return $responseXml;
	}
}
	
	