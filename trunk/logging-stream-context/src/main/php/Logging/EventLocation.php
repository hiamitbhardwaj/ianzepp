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
class Logging_EventLocation {
    /**
     * @param string|null $message
     * @return Logging_Exception
     */
    public function newException($message) {
        require_once 'Logging/Exception.php';
        return new Logging_Exception($message);
    }
    
	/**
	 * Class name
	 *
	 * @var string $className
	 */
	private $className;

	/**
	 * Getter for the $className property.
	 *
	 * @return string
	 */
	public function getClassName() {
		return $this->className;
	}

	/**
	 * Existence tester for the $className property.
	 *
	 * @return boolean
	 */
	public function hasClassName() {
		return empty($this->className) === false;
	}

	/**
	 * Setter for the $className property
	 *
	 * @param string $className - Class name
	 */
	public function setClassName($className) {
		$this->className = $className;
	}

	/**
	 * File name
	 *
	 * @var string $fileName
	 */
	private $fileName;

	/**
	 * Getter for the $fileName property.
	 *
	 * @return string
	 */
	public function getFileName() {
		return $this->fileName;
	}

    /**
     * Existence tester for the $fileName property.
     *
     * @return boolean
     */
    public function hasFileName() {
        if (empty($this->fileName)) {
            throw $this->newException("Missing required value for the 'fileName' property");
        } else {
            return true;
        }
    }

	/**
	 * Setter for the $fileName property
	 *
	 * @param string $fileName - File name
	 */
	public function setFileName($fileName) {
		$this->fileName = $fileName;
	}

	/**
	 * Line number
	 *
	 * @var string $lineNumber
	 */
	private $lineNumber;

	/**
	 * Getter for the $lineNumber property.
	 *
	 * @return string
	 */
	public function getLineNumber() {
		return $this->lineNumber;
	}

	/**
	 * Existence tester for the $lineNumber property.
	 *
	 * @return boolean
	 */
	public function hasLineNumber() {
		if (empty($this->lineNumber)) {
			throw $this->newException("Missing required value for the 'lineNumber' property");
		} else {
			return true;
		}
	}

	/**
	 * Setter for the $lineNumber property
	 *
	 * @param string $lineNumber - Line number
	 */
	public function setLineNumber($lineNumber) {
		$this->lineNumber = $lineNumber;
	}

	/**
	 * Method name
	 *
	 * @var string $methodName
	 */
	private $methodName;

	/**
	 * Getter for the $methodName property.
	 *
	 * @return string
	 */
	public function getMethodName() {
		return $this->methodName;
	}

	/**
	 * Existence tester for the $methodName property.
	 *
	 * @return boolean
	 */
	public function hasMethodName() {
		return empty($this->methodName) === false;
	}

	/**
	 * Setter for the $methodName property
	 *
	 * @param string $methodName - Method name
	 */
	public function setMethodName($methodName) {
		$this->methodName = $methodName;
	}

	/**
	 * Returns the object as an XML value.
	 *
	 * @return string
	 */
	public function toXml($wrapped = true) {
		ob_start();

		// Add parts
		if ($this->hasFileName()) {
			echo '<fileName>', $this->getFileName(), '</fileName>';
		}
		if ($this->hasClassName()) {
			echo '<className>', $this->getClassName(), '</className>';
		}
		if ($this->hasMethodName()) {
			echo '<methodName>', $this->getMethodName(), '</methodName>';
		}
		if ($this->hasLineNumber()) {
			echo '<lineNumber>', $this->getLineNumber(), '</lineNumber>';
		}

		// Wrap?
		if ($wrapped) {
			return '<location>' . ob_get_clean() . '</location>';
		} else {
			return ob_get_clean();
		}
	}

	/**
	 * Return the object as a string
	 *
	 * @return string
	 */
	public function __toString() {
		return $this->toXml();
	}
}