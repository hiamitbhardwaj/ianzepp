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

abstract class Appenda_Bundle_Account_Endpoint implements Appenda_Message_Endpoint
{
	private $accounts;
	private $addresses;
	private $contacts;
	private $phones;
	
	/**
	 * @return Appenda_Bundle_Account_Model
	 */
	public function getAccounts ()
	{
		return $this->accounts;
	}
	
	/**
	 * @return Appenda_Bundle_Account_Model
	 */
	public function getAddresses ()
	{
		return $this->addresses;
	}
	
	/**
	 * @return Appenda_Bundle_Account_Model
	 */
	public function getContacts ()
	{
		return $this->contacts;
	}
	
	/**
	 * @return Appenda_Bundle_Account_Model
	 */
	public function getPhones ()
	{
		return $this->phones;
	}
	
	/**
	 * @param Appenda_Bundle_Account_Model $accounts
	 */
	public function setAccounts (Appenda_Bundle_Account_Model $accounts)
	{
		$this->accounts = $accounts;
	}
	
	/**
	 * @param Appenda_Bundle_Account_Model $addresses
	 */
	public function setAddresses (Appenda_Bundle_Account_Model $addresses)
	{
		$this->addresses = $addresses;
	}
	
	/**
	 * @param Appenda_Bundle_Account_Model $contacts
	 */
	public function setContacts (Appenda_Bundle_Account_Model $contacts)
	{
		$this->contacts = $contacts;
	}
	
	/**
	 * @param Appenda_Bundle_Account_Model $phones
	 */
	public function setPhones (Appenda_Bundle_Account_Model $phones)
	{
		$this->phones = $phones;
	}
	
	/**
	 * Convert 
	 */
	public function convertAccountToXml (Appenda_Bundle_Account_Model_AccountRow $foo)
	{
	}
}