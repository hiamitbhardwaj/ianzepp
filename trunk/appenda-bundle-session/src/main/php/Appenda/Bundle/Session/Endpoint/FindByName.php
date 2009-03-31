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

class Appenda_Bundle_Session_Endpoint_FindByName extends Appenda_Bundle_Session_Endpoint
{
	public function processMessage (SimpleXMLElement $xml)
	{
		// Build the basic result xml
		$responseXml = simplexml_load_string ("<SessionList />");
		$responseXml ["xmlns"] = array_shift ($xml->getNamespaces (false));
		
		// Fetch first match
		$select = $this->getSessionTable ()->select ();
		$select->where ("name = ?", (string) $xml);
		$result = $this->getSessionTable ()->fetchRow ($select)->toArray ();
		
		// Is there a match?
		if (empty ($result))
		{
			return $responseXml;
		}
		
		// Is the session invalid (timed out)?
		if (intval ((string) $result ["expires_at"]) >= time ())
		{
			return $responseXml;
		}
		
		// Build and return the result
		$session = $responseXml->addChild ("session");
		$session->{"name"} = $result ["name"];
		$session->{"data"} = $result ["data"];
		$session->{"created"} = $result ["created_at"];
		$session->{"updated"} = $result ["updated_at"];
		$session->{"expires"} = $result ["expires_at"];
		
		// Done.
		return $responseXml;
	}
}