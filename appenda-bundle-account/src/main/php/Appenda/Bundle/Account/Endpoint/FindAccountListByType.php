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
 * @package Appenda_Bundle_Account
 */

class Appenda_Bundle_Account_Endpoint_FindAccountById extends Appenda_Bundle_Account_Endpoint
{
	/**
	 * @param SimpleXMLElement $xml
	 * @return SimpleXMLElement
	 */
	public function processMessage (SimpleXMLElement $xml)
	{
		// Build the basic response
		$response = $this->getResponseXml ("AccountList", $xml ["xmlns"]);
		
		// Build the search
		$offset = (int) $xml->{"offset"};
		$limit = (int) $xml->{"limit"};
		
		if ($limit == 0)
			$limit = $this->getDefaultLimit ();
		
		$select = $this->getAccountTable ()->select ();
		$select->where ("type = ?", (string) $xml);
		$select->limit ($limit, $offset);
		
		// Results found?
		$modelList = $this->getAccountTable ()->fetch ($select);
		
		foreach ($modelList as $model)
		{
			$this->insertAccount ($response->addChild ("account"), $model);
		}
		
		// Add metadata
		$response ["count"] = count ($modelList);
		$response ["limit"] = $limit;
		$response ["offset"] = $offset;
		
		// Done.
		return $response;
	}
}