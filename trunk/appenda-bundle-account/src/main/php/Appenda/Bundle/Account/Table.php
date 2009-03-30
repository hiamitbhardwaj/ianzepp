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

require_once "Zend/Db/Table.php";

class Appenda_Bundle_Account_Table extends Zend_Db_Table
{
	const Account = "Appenda_Bundle_Account_Table_Account";
	const AccountAddress = "Appenda_Bundle_Account_Table_AccountAddress";
	const AccountContact = "Appenda_Bundle_Account_Table_AccountContact";
	const AccountPhone = "Appenda_Bundle_Account_Table_AccountPhone";
	const Address = "Appenda_Bundle_Account_Table_Address";
	const Contact = "Appenda_Bundle_Account_Table_Contact";
	const ContactAddress = "Appenda_Bundle_Account_Table_ContactAddress";
	const ContactPhone = "Appenda_Bundle_Account_Table_ContactPhone";
	const Phone = "Appenda_Bundle_Account_Table_Phone";
}

