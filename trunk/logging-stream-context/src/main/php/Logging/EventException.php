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
class Logging_EventException {
	/**
	 * Detail information
	 *
	 * @var string $detail
	 */
	private $detail;

	/**
	 * Getter for the $detail property.
	 *
	 * @return string
	 */
	public function getDetail() {
		return $this->detail;
	}

	/**
	 * Setter for the $detail property
	 *
	 * @param string $detail - Detail information
	 */
	public function setDetail($detail) {
		$this->detail = $detail;
	}

	/**
	 * Exception name
	 *
	 * @var string $exceptionName
	 */
	private $exceptionName;

	/**
	 * Getter for the $exceptionName property.
	 *
	 * @return string
	 */
	public function getExceptionName() {
		return $this->exceptionName;
	}

	/**
	 * Setter for the $exceptionName property
	 *
	 * @param string $exceptionName - Exception name
	 */
	public function setExceptionName($exceptionName) {
		$this->exceptionName = $exceptionName;
	}

	/**
	 * Message data
	 *
	 * @var string $message
	 */
	private $message;

	/**
	 * Getter for the $message property.
	 *
	 * @return string
	 */
	public function getMessage() {
		return $this->message;
	}

	/**
	 * Setter for the $message property
	 *
	 * @param string $message - Message data
	 */
	public function setMessage($message) {
		$this->message = $message;
	}

	/**
	 * Returns the object as an XML value.
	 *
	 * @return string
	 */
	public function toXml() {
		ob_start();
		echo '<exception>';
		echo '<exceptionName>', $this->getExceptionName(), '</exceptionName>';
		echo '<message>', $this->getMessage(), '</message>';
		echo '<detail>', $this->getDetail(), '</detail>';
		echo '</exception>';
		return ob_get_clean();
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