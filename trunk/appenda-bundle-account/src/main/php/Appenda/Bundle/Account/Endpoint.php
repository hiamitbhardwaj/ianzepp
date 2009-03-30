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

abstract class Appenda_Bundle_Account_Endpoint implements Appenda_Message_Endpoint
{
	private $accountTable;
	private $addressTable;
	private $contactTable;
	private $emailTable;
	private $phoneTable;
	
	private $defaultLimit = 100;
	
	/**
	 * @return Appenda_Bundle_Account_Table
	 */
	public function getAccountTable ()
	{
		return $this->accountTable;
	}
	
	/**
	 * @param Appenda_Bundle_Account_Table $accountTable
	 */
	public function setAccountTable ($accountTable)
	{
		$this->accountTable = $accountTable;
	}
	
	/**
	 * @return Appenda_Bundle_Account_Table
	 */
	public function getAddressTable ()
	{
		return $this->addressTable;
	}
	
	/**
	 * @param Appenda_Bundle_Account_Table $addressTable
	 */
	public function setAddressTable ($addressTable)
	{
		$this->addressTable = $addressTable;
	}
	
	/**
	 * @return Appenda_Bundle_Account_Table
	 */
	public function getContactTable ()
	{
		return $this->contactTable;
	}
	
	/**
	 * @param Appenda_Bundle_Account_Table $contactTable
	 */
	public function setContactTable ($contactTable)
	{
		$this->contactTable = $contactTable;
	}
	
	/**
	 * @return Appenda_Bundle_Account_Table
	 */
	public function getEmailTable ()
	{
		return $this->emailTable;
	}
	
	/**
	 * @param Appenda_Bundle_Account_Table $emailTable
	 */
	public function setEmailTable ($emailTable)
	{
		$this->emailTable = $emailTable;
	}
	
	/**
	 * @return Appenda_Bundle_Account_Table
	 */
	public function getPhoneTable ()
	{
		return $this->phoneTable;
	}
	
	/**
	 * @param Appenda_Bundle_Account_Table $phoneTable
	 */
	public function setPhoneTable ($phoneTable)
	{
		$this->phoneTable = $phoneTable;
	}
	
	/**
	 * @return integer
	 */
	public function getDefaultLimit ()
	{
		return $this->defaultLimit;
	}
	
	/**
	 * @param integer $defaultLimit
	 */
	public function setDefaultLimit ($defaultLimit)
	{
		$this->defaultLimit = $defaultLimit;
	}
	
	/**
	 * Enter description here...
	 *
	 * @param string $name
	 * @param string $xmlns
	 * @param string $text OPTIONAL
	 * @return SimpleXMLElement
	 */
	protected function getResponseXml ($name, $xmlns, $text = null)
	{
		if (empty ($text))
			return simplexml_load_string ("<$name xmlns='$xmlns' />");
		else
			return simplexml_load_string ("<$name xmlns='$xmlns'>$text</$name>");
	}
	
	/**
	 * Enter description here...
	 *
	 * @param SimpleXMLElement $xml
	 * @param Appenda_Bundle_Account_Model_Account $model
	 */
	protected function insertAccount (SimpleXMLElement $xml, Appenda_Bundle_Account_Model_Account $model)
	{
		$xml->{"id"} = $model->{"account_id"};
		$xml->{"name"} = $model->{"name"};
		$xml->{"type"} = $model->{"type"};
		
		foreach ($model->findContacts () as $contact)
			$rsp->addChild ("contact", $contact->{"id"});
		
		foreach ($model->findAddresses () as $address)
			$this->insertAddress ($rsp->addChild ("address"), $address);
		
		foreach ($model->findPhones () as $phone)
			$this->insertPhone ($rsp->addChild ("phone"), $phone);
	}
	
	/**
	 * Enter description here...
	 *
	 * @param SimpleXMLElement $xml
	 * @param Appenda_Bundle_Account_Model_Address $model
	 */
	protected function insertAddress (SimpleXMLElement $xml, Appenda_Bundle_Account_Model_Address $model)
	{
	}
	
	/**
	 * Enter description here...
	 *
	 * @param SimpleXMLElement $xml
	 * @param Appenda_Bundle_Account_Model_Contact $model
	 */
	protected function insertContact (SimpleXMLElement $xml, Appenda_Bundle_Account_Model_Contact $model)
	{
	}
	
	/**
	 * Enter description here...
	 *
	 * @param SimpleXMLElement $xml
	 * @param Appenda_Bundle_Account_Model_Phone $model
	 */
	protected function insertPhone (SimpleXMLElement $xml, Appenda_Bundle_Account_Model_Phone $model)
	{
	}
}