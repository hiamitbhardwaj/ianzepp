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

class Appenda_Bundle_Account_TableRow_Contact extends Appenda_Bundle_Account_TableRow
{
	/**
	 * Enter description here...
	 *
	 * @return Zend_Db_Table_Rowset_Abstract
	 */
	public function findAccounts ()
	{
		return $this->findManyToManyRowset ("Appenda_Bundle_Account_Table_Contact", "Appenda_Bundle_Account_Table_Account");
	}
	
	/**
	 * Enter description here...
	 *
	 * @return Zend_Db_Table_Rowset_Abstract
	 */
	public function findAddresses ()
	{
		return $this->findManyToManyRowset ("Appenda_Bundle_Account_Table_Contact", "Appenda_Bundle_Account_Table_Address");
	}
	
	/**
	 * Enter description here...
	 *
	 * @return Zend_Db_Table_Rowset_Abstract
	 */
	public function findPhones ()
	{
		return $this->findManyToManyRowset ("Appenda_Bundle_Account_Table_Contact", "Appenda_Bundle_Account_Table_Phone");
	}
	
	/**
	 * Enter description here...
	 *
	 * @param SimpleXMLElement $rootXml
	 * @return SimpleXMLElement
	 */
	public function toXml (SimpleXMLElement $xml, $recursive = false)
	{
		$xml->{"id"} = $this->{"contact_id"};
		$xml->{"firstName"} = $this->{"first_name"};
		$xml->{"middleName"} = $this->{"middle_name"};
		$xml->{"lastName"} = $this->{"last_name"};
		$xml->{"salutation"} = $this->{"salutation"};
		$xml->{"suffix"} = $this->{"suffix"};
		
		foreach ($this->findAddresses () as $address )
		{
			$address->toXml ($xml->{"addresses"}->addChild ("address"));
		}
		
		foreach ($this->findPhones () as $phone )
		{
			$phone->toXml ($xml->{"phones"}->addChild ("phone"));
		}
		
		// Only add accounts if recurse is true.
		if (!$recurse)
		{
			return $xml;
		}
		
		foreach ($this->findAccounts () as $account )
		{
			$account->toXml ($xml->{"accounts"}->addChild ("account"));
		}
		
		return $xml;
	}
}