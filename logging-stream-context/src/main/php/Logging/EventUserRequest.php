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
class Logging_EventUserRequest
{
	/**
	 * Environment variables
	 *
	 * @var string $environmentVars
	 */
	private $environmentVars;
	
	/**
	 * Getter for the $environmentVars property.
	 *
	 * @return string
	 */
	public function getEnvironmentVars ()
	{
		return $this->environmentVars;
	}
	
	/**
	 * Setter for the $environmentVars property
	 *
	 * @param string $environmentVars - Environment variables
	 */
	public function setEnvironmentVars ($environmentVars)
	{
		$this->environmentVars = $environmentVars;
	}
	
	/**
	 * Session data
	 *
	 * @var string $sessionData
	 */
	private $sessionData;
	
	/**
	 * Getter for the $sessionData property.
	 *
	 * @return string
	 */
	public function getSessionData ()
	{
		return $this->sessionData;
	}
	
	/**
	 * Setter for the $sessionData property
	 *
	 * @param string $sessionData - Session data
	 */
	public function setSessionData ($sessionData)
	{
		$this->sessionData = $sessionData;
	}
	
	/**
	 * SessionId
	 *
	 * @var string $sessionId
	 */
	private $sessionId;
	
	/**
	 * Getter for the $sessionId property.
	 *
	 * @return string
	 */
	public function getSessionId ()
	{
		return $this->sessionId;
	}
	
	/**
	 * Setter for the $sessionId property
	 *
	 * @param string $sessionId - SessionId
	 */
	public function setSessionId ($sessionId)
	{
		$this->sessionId = $sessionId;
	}
	
	/**
	 * Request data
	 *
	 * @var string $requestData
	 */
	private $requestData;
	
	/**
	 * Getter for the $requestData property.
	 *
	 * @return string
	 */
	public function getRequestData ()
	{
		return $this->requestData;
	}
	
	/**
	 * Setter for the $requestData property
	 *
	 * @param string $requestData - Request data
	 */
	public function setRequestData ($requestData)
	{
		$this->requestData = $requestData;
	}
	
	/**
	 * Request uri
	 *
	 * @var string $requestUri
	 */
	private $requestUri;
	
	/**
	 * Getter for the $requestUri property.
	 *
	 * @return string
	 */
	public function getRequestUri ()
	{
		return $this->requestUri;
	}
	
	/**
	 * Setter for the $requestUri property
	 *
	 * @param string $requestUri - Request uri
	 */
	public function setRequestUri ($requestUri)
	{
		$this->requestUri = $requestUri;
	}
	
	/**
	 * Returns the object as an XML value.
	 *
	 * @return string
	 */
	public function toXml ()
	{
		ob_start ();
		echo '<userRequest>';
		echo '<sessionId>', $this->getSessionId (), '</sessionId>';
		echo '<sessionData><![CDATA[', $this->getSessionData (), ']]></sessionData>';
		echo '<requestUri>', $this->getRequestUri (), '</requestUri>';
		echo '<requestData><![CDATA[', $this->getRequestData (), ']]></requestData>';
		echo '<environmentVars><![CDATA[', $this->getEnvironmentVars (), ']]></environmentVars>';
		echo '</userRequest>';
		return ob_get_clean ();
	}
	
	/**
	 * Return the object as a string
	 *
	 * @return string
	 */
	public function __toString ()
	{
		return $this->toXml ();
	}
}