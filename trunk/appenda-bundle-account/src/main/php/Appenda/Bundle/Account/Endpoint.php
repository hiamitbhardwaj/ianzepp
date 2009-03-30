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

}