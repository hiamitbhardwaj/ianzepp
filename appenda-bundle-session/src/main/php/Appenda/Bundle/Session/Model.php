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
 * 
 * @method string getId ()
 * @method void setId (string)
 * @method integer getExpiration ()
 * @method void setExpiration (integer)
 */
class Appenda_Bundle_Session_Model extends Appenda_Property_Set implements Appenda_Model
{
	protected function __construct ()
	{
		$this->register ("Id", "String");
		$this->register ("Expiration", "Integer");
		$this->registerTemplate (__CLASS__);
	}
	
	/**
	 * Returns a new model object, initialized with the table row data (if available).
	 *
	 * @param Zend_Db_Table_Row $row
	 * @return Appenda_Bundle_Session_Model
	 */
	public function newInstance (Zend_Db_Table_Row $row = null)
	{
		$self = parent::newInstance (__CLASS__);
		$self->setId ($row ["id"]);
		$self->setExpiration ($row ["expiration"]);
		return $self;
	}
}