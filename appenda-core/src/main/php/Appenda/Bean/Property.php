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

class Appenda_Bean_Property {
	/**
	 * Enter description here...
	 *
	 * @var string
	 */
	const TYPE_REFERENCE = "ref";
	
	/**
	 * Enter description here...
	 *
	 * @var string
	 */
	const TYPE_VALUE = "value";
	
	// Private properties
	private $convertedValue;
	private $name;
	private $source;
	private $type;
	private $value;
	
	/**
	 * Enter description here...
	 *
	 * @param Appenda_Bean_Property|string $arg0
	 * @param mixed $arg1
	 */
	public function __construct ($arg0, $arg1 = null) {
		if (is_string ($arg0) && !is_null ($arg1)) {
			return $this->__constructFromName ($arg0, $arg1);
		}
		
		if ($arg0 instanceof self && is_null ($arg1)) {
			return $this->__constructCopy ($arg0);
		}
		
		if ($arg0 instanceof self) {
			return $this->__constructCopyNew ($arg0, $arg1);
		}
		
		throw new Appenda_Bean_Exception ("Invalid constructor arguments");
	}
	
	/**
	 * Enter description here...
	 *
	 * @param string $name
	 * @param mixed $value
	 */
	private function __constructFromName ($name, $value) {
		assert (is_string ($name));
		assert (is_null ($value) == false);
		
		$this->name = $name;
		$this->value = $value;
	}
	
	/**
	 * Enter description here...
	 *
	 * @param Appenda_Bean_Property $copy
	 */
	private function __constructCopy (Appenda_Bean_Property $copy) {
		$this->convertedValue = $copy->convertedValue;
		$this->name = $copy->name;
		$this->source = $copy->source;
		$this->value = $copy->value;
	}
	
	/**
	 * Enter description here...
	 *
	 * @param Appenda_Bean_Property $copy
	 * @param mixed $convertedValue
	 */
	private function __constructCopyNew (Appenda_Bean_Property $copy, $convertedValue) {
		assert (is_null ($convertedValue) == false);
		
		$this->convertedValue = $convertedValue;
		$this->name = $copy->name;
		$this->source = $copy->source;
		$this->value = $copy->value;
	}
	
	/**
	 * @return mixed
	 */
	public function getConvertedValue () {
		return $this->convertedValue;
	}
	
	/**
	 * @return string
	 */
	public function getName () {
		return $this->name;
	}
	
	/**
	 * @return object
	 */
	public function getSource () {
		return $this->source;
	}
	
	/**
	 * @return string
	 */
	public function getType () {
		return $this->type;
	}
	
	/**
	 * @return mixed
	 */
	public function getValue () {
		return $this->value;
	}
	
	/**
	 * Enter description here...
	 *
	 * @return boolean
	 */
	public function isConverted () {
		return !is_null ($this->getConvertedValue ());
	}
	/**
	 * @param mixed $convertedValue
	 */
	public function setConvertedValue ($convertedValue) {
		$this->convertedValue = $convertedValue;
	}
	
	/**
	 * @param string $name
	 */
	public function setName ($name) {
		assert (is_string ($name));
		$this->name = $name;
	}
	
	/**
	 * @param object $source
	 */
	public function setSource ($source) {
		$this->source = $source;
	}
	
	/**
	 * @param string $type
	 */
	public function setType ($type) {
		assert (is_string ($type));
		$this->type = $type;
	}

}