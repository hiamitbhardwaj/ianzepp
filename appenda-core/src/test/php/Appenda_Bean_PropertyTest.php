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

class Appenda_Bean_PropertyTest extends PHPUnit_Framework_TestCase {
	/**
	 * @expectedException Exception
	 */
	public function testConstructorWithoutArgs () {
		new Appenda_Bean_Property ();
	}

	/**
	 * @expectedException
	 */
	public function testConstructorWithNamedValue () {
		new Appenda_Bean_Property ("Name", "Value");
	}

	/**
	 * @expectedException
	 */
	public function testConstructorWithNamedIntegerValue () {
		new Appenda_Bean_Property ("Name", 21);
	}

	/**
	 * @expectedException Appenda_Exception
	 */
	public function testConstructorWithInvalidNameType () {
		new Appenda_Bean_Property (21, "Value");
	}

	/**
	 * @expectedException
	 */
	public function testConstructorCopy () {
		$instance0 = new Appenda_Bean_Property ("Name", 21);
		$instance1 = new Appenda_Bean_Property ($instance0);
		$this->assertEquals ($instance0, $instance1);
	}

	/**
	 * @expectedException
	 */
	public function testConstructorCopyNew () {
		$instance0 = new Appenda_Bean_Property ("Name", "21");
		$instance1 = new Appenda_Bean_Property ($instance0, 21);
		$this->assertNotEquals ($instance0, $instance1);
		$this->assertEquals (21, $instance1->getConvertedValue ());
	}

	/**
	 * @expectedException
	 */
	public function testGetName () {
		$instance0 = new Appenda_Bean_Property ("Name", "21");
		$this->assertEquals ("Name", $instance0->getName ());
	}

	/**
	 * @expectedException
	 */
	public function testGetValue () {
		$instance0 = new Appenda_Bean_Property ("Name", "21");
		$this->assertEquals ("21", $instance0->getValue ());
	}

	/**
	 * @expectedException
	 */
	public function testGetConvertedValueWhenNull () {
		$instance0 = new Appenda_Bean_Property ("Name", "21");
		$this->assertNull ($instance0->getConvertedValue ());
	}

	/**
	 * @expectedException
	 */
	public function testGetConvertedValueAfterSet () {
		$instance0 = new Appenda_Bean_Property ("Name", "21");
		$instance0->setConvertedValue (21);
		$this->assertEquals (21, $instance0->getConvertedValue ());
	}

	/**
	 * @expectedException
	 */
	public function testIsConverted () {
		$instance0 = new Appenda_Bean_Property ("Name", "21");
		$this->assertFalse ($instance0->isConverted ());

		$instance1 = new Appenda_Bean_Property ($instance0, 21);
		$this->assertTrue ($instance1->isConverted ());
	}

	/**
	 * @expectedException
	 */
	public function testIsConvertedAfterSet () {
		$instance0 = new Appenda_Bean_Property ("Name", "21");
		$this->assertFalse ($instance0->isConverted ());

		$instance0->setConvertedValue (21);
		$this->assertTrue ($instance0->isConverted ());
	}

}