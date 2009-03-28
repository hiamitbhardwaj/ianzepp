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
class Logging_Event {
	/**
	 * @param string|null $message
	 * @return Logging_Exception
	 */
	public function newException($message) {
		require_once 'Logging/Exception.php';
		return new Logging_Exception($message);
	}
	
	/**
	 * @return Logging_EventException
	 */
	public function newEventException() {
		require_once 'Logging/EventException.php';
		return new Logging_EventException;
	}

	/**
	 * @return Logging_EventLocation
	 */
	public function newEventLocation() {
		require_once 'Logging/EventLocation.php';
		return new Logging_EventLocation;
	}

	/**
	 * @return Logging_EventUserRequest
	 */
	public function newEventUserRequest() {
		require_once 'Logging/EventUserRequest.php';
		return new Logging_EventUserRequest;
	}

	/**
	 * CorrelationId
	 *
	 * @var string $correlationId
	 */
	private $correlationId;

	/**
	 * Getter for the $correlationId property.
	 *
	 * @return string
	 */
	public function getCorrelationId() {
		return $this->correlationId;
	}

	/**
	 * Existence tester for the $correlationId property.
	 *
	 * @return boolean
	 */
	public function hasCorrelationId() {
		return empty($this->correlationId) === false;
	}

	/**
	 * Setter for the $correlationId property
	 *
	 * @param string $correlationId - CorrelationID
	 */
	public function setCorrelationId($correlationId) {
		$this->correlationId = $correlationId;
	}

	/**
	 * Exception information
	 *
	 * @var Logging_EventException $exception
	 */
	private $exception;

	/**
	 * Getter for the $exception property.
	 *
	 * @return Logging_EventException
	 */
	public function getException() {
		if ($this->exception == null) {
			$this->exception = $this->newEventException();
		}
		return $this->exception;
	}

	/**
	 * Existence tester for the $exception property.
	 *
	 * @return boolean
	 */
	public function hasException() {
		return empty($this->exception) === false;
	}

	/**
	 * Setter for the $exception property
	 *
	 * @param Logging_EventException $exception - Exception information
	 */
	public function setException($exception) {
		$this->exception = $exception;
	}

	/**
	 * Host name
	 *
	 * @var string $host
	 */
	private $host;

	/**
	 * Getter for the $host property.
	 *
	 * @return string
	 */
	public function getHost() {
		if (empty($this->level) && isset($SERVER['SERVER_NAME'])) {
			return $SERVER['SERVER_NAME'];
		} else if (empty($this->level)) {
			return 'unknown.local';
		} else {
			return $this->level;
		}
	}

	/**
	 * Setter for the $host property
	 *
	 * @param string $host - Host name
	 */
	public function setHost($host) {
		$this->host = $host;
	}

	/**
	 * Level
	 *
	 * @var string $level
	 */
	private $level;

	/**
	 * Getter for the $level property.
	 *
	 * @return string
	 */
	public function getLevel() {
		if (empty($this->level)) {
			throw $this->newException("Missing required value for the 'level' property");
		} else {
			return $this->level;
		}
	}

	/**
	 * Setter for the $level property
	 *
	 * @param string $level - Level
	 */
	public function setLevel($level) {
		$this->level = $level;
	}

	/**
	 * EventLocation information
	 *
	 * @var Logging_EventLocation $location
	 */
	private $location;

	/**
	 * Getter for the $location property.
	 *
	 * @return Logging_EventLocation
	 */
	public function getLocation() {
		if ($this->location == null) {
			$this->location = $this->newEventLocation();
		}
		return $this->location;
	}

	/**
	 * Existence tester for the $location property.
	 *
	 * @return boolean
	 */
	public function hasLocation() {
		return empty($this->location) === false;
	}

	/**
	 * Setter for the $location property
	 *
	 * @param Logging_EventLocation $location - EventLocation information
	 */
	public function setLocation(Logging_EventLocation $location) {
		$this->location = $location;
	}

	/**
	 * Logger name
	 *
	 * @var string $logger
	 */
	private $logger;

	/**
	 * Getter for the $logger property.
	 *
	 * @return string
	 */
	public function getLogger() {
		if (empty($this->logger)) {
			return '?';
		} else {
			return $this->logger;
		}
	}

	/**
	 * Setter for the $logger property
	 *
	 * @param string $logger - Logger name
	 */
	public function setLogger($logger) {
		$this->logger = $logger;
	}


	/**
	 * Message text
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
		if (empty($this->message)) {
			throw $this->newException("Missing required value for the 'message' property");
		} else {
			return $this->message;
		}
	}

	/**
	 * Setter for the $message property
	 *
	 * @param string $message - Message text
	 */
	public function setMessage($message) {
		$this->message = $message;
	}

	/**
	 * MessageId
	 *
	 * @var string $messageId
	 */
	private $messageId;

	/**
	 * Getter for the $messageId property.
	 *
	 * @return string
	 */
	public function getMessageId() {
		return $this->messageId;
	}

	/**
	 * Existence tester for the $messageId property.
	 *
	 * @return boolean
	 */
	public function hasMessageId() {
		return empty($this->messageId) === false;
	}

	/**
	 * Setter for the $messageId property
	 *
	 * @param string $messageId - MessageId
	 */
	public function setMessageId($messageId) {
		$this->messageId = $messageId;
	}

	/**
	 * Project name
	 *
	 * @var string $project
	 */
	private $project;

	/**
	 * Getter for the $project property.
	 *
	 * @return string
	 */
	public function getProject() {
		return $this->project;
	}

	/**
	 * Existence tester for the $project property.
	 *
	 * @return boolean
	 */
	public function hasProject() {
		return empty($this->project) === false;
	}

	/**
	 * Setter for the $project property
	 *
	 * @param string $project - Project name
	 */
	public function setProject($project) {
		$this->project = $project;
	}

	/**
	 * Service name
	 *
	 * @var string $service
	 */
	private $service;

	/**
	 * Getter for the $service property.
	 *
	 * @return string
	 */
	public function getService() {
		return $this->service;
	}

	/**
	 * Existence tester for the $service property.
	 *
	 * @return boolean
	 */
	public function hasService() {
		return empty($this->service) === false;
	}

	/**
	 * Setter for the $service property
	 *
	 * @param string $service - Service name
	 */
	public function setService($service) {
		$this->service = $service;
	}

	/**
	 * Thread name
	 *
	 * @var string $thread
	 */
	private $thread;

	/**
	 * Getter for the $thread property.
	 *
	 * @return string
	 */
	public function getThread() {
		return $this->thread;
	}

	/**
	 * Existence tester for the $thread property.
	 *
	 * @return boolean
	 */
	public function hasThread() {
		return empty($this->thread) === false;
	}

	/**
	 * Setter for the $thread property
	 *
	 * @param string $thread - Thread name
	 */
	public function setThread($thread) {
		$this->thread = $thread;
	}

	/**
	 * Timestamp
	 *
	 * @var string $timestamp
	 */
	private $timestamp;

	/**
	 * Getter for the $timestamp property.
	 *
	 * @return string
	 */
	public function getTimestamp() {
		if (empty($this->timestamp) && isset($SERVER['REQUEST_TIME'])) {
			return $SERVER['REQUEST_TIME'];
		} else if (empty($this->timestamp)) {
			return '?';
		} else {
			return $this->timestamp;
		}
	}

	/**
	 * Existence tester for the $timestamp property.
	 *
	 * @return boolean
	 */
	public function hasTimestamp() {
		return empty($this->timestamp) === false;
	}

	/**
	 * Setter for the $timestamp property
	 *
	 * @param string $timestamp - Time stamp
	 */
	public function setTimestamp($timestamp) {
		$this->timestamp = $timestamp;
	}

	/**
	 * User request information
	 *
	 * @var Logging_EventUserRequest $userRequest
	 */
	private $userRequest;

	/**
	 * Getter for the $userRequest property.
	 *
	 * @return Logging_EventUserRequest
	 */
	public function getUserRequest() {
		if ($this->userRequest == null) {
			$this->userRequest = $this->newEventUserRequest();
		}
		return $this->userRequest;
	}

	/**
	 * Existence tester for the $userRequest property.
	 *
	 * @return boolean
	 */
	public function hasUserRequest() {
		return empty($this->userRequest) === false;
	}

	/**
	 * Setter for the $userRequest property
	 *
	 * @param Logging_EventUserRequest $userRequest - User request information
	 */
	public function setUserRequest(Logging_EventUserRequest $userRequest) {
		$this->userRequest = $userRequest;
	}

	/**
	 * Returns the object as an XML value.
	 *
	 * @return string
	 */
	public function toXml() {
		ob_start();

		// Required properties (getX() will throw an exception if missing)
		echo '<host>', $this->getHost(), '</host>';
		echo '<logger>', $this->getLogger(), '</logger>';
		echo '<level>', $this->getLevel(), '</level>';
		echo '<message>', $this->getMessage(), '</message>';

		// Optional properties
		if ($this->hasTimestamp()) {
			echo '<timestamp>', $this->getTimestamp(), '</timestamp>';
		}
		if ($this->hasThread()) {
			echo '<thread>', $this->getThread(), '</thread>';
		}
		if ($this->hasProject()) {
			echo '<project>', $this->getProject(), '</project>';
		}
		if ($this->hasService()) {
			echo '<service>', $this->getService(), '</service>';
		}
		if ($this->hasCorrelationId()) {
			echo '<correlationId>', $this->getCorrelationId(), '</correlationId>';
		}
		if ($this->hasMessageId()) {
			echo '<messageId>', $this->getMessageId(), '</messageId>';
		}

		// Optional self-contained tags
		if ($this->hasLocation()) {
			echo $this->getLocation();
		}
		if ($this->hasException()) {
			echo $this->getException();
		}
		if ($this->hasUserRequest()) {
			echo $this->getUserRequest();
		}

		// Done.
		return '<eventRequest xmlns="http://ianzepp.com/logging">' . ob_get_clean() . '</eventRequest>';
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


