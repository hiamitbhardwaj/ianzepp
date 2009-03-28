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

class Appenda_Stream_Stomp extends Appenda_Stream_Abstract {
	public $context; // why does this have to be public?
	private $connection;
	private $data;
	private $tell = 0;
	
	/**
	 * @see Appenda_Stream_Abstract::stream_open()
	 *
	 * @param string $path
	 * @param string $mode
	 * @param integer $options
	 * @param unknown_type $opened_path
	 * @return boolean
	 */
	public function stream_open ($path, $mode, $options, &$opened_path) {
		$this->setContext ($path);
		return true;
	}
	
	/**
	 * @see Appenda_Stream_Abstract::stream_write()
	 *
	 * @param string $incomingData
	 * @return integer
	 */
	public function stream_write ($incomingData) {
		$connection = $this->getConnection ();
		
		if (!$connection) {
			$map ["message"] = "Connection object has not been properly injected";
			$map ["incomingData"] = $incomingData;
			$map ["this"] = $this;
			throw new Appenda_Exception ($map);
		}
		
		try {
			$connection->sendMessage ($this->getChannel (), $incomingData);
		} catch (Exception $e) {
			$map ["message"] = "Caught exception while sending outbound message";
			$map ["exception"] = $e;
			$map ["incomingData"] = $incomingData;
			$map ["this"] = $this;
			throw new Appenda_Exception ($map);
		}
		
		return strlen ($incomingData);
	}
	
	/**
	 * @see Appenda_Stream_Abstract::stream_read()
	 *
	 * @param integer $count
	 * @return string|boolean
	 */
	public function stream_read ($count) {
		$connection = $this->getConnection ();
		
		if (!$connection) {
			$map ["message"] = "Connection object has not been properly injected";
			$map ["incomingData"] = $incomingData;
			$map ["this"] = $this;
			throw new Appenda_Exception ($map);
		}
		
		// If the data is null, then we haven't read in a frame yet
		if (is_null ($this->data)) {
			// Subscribe to the channel of interest
			try {
				$frame = $connection->newSubscriptionFrame ($this->getChannel ());
				$connection->sendFrame ($frame);
			} catch (Exception $e) {
				$map ["message"] = "Caught exception while trying to subscribe to channel";
				$map ["exception"] = $e;
				$map ["frame"] = $frame;
				$map ["this"] = $this;
				throw new Appenda_Exception ($map);
			}
			
			// Try to read a message from that channel
			try {
				$this->data = $connection->readFrame ()->getBody ();
			} catch (Exception $e) {
				// Save the data as an empty string for future reads
				$this->data = '';
				
				// Throw an exception
				$map ["message"] = "Caught exception while reading inbound message";
				$map ["exception"] = $e;
				$map ["readSize"] = $count;
				$map ["this"] = $this;
				throw new Appenda_Exception ($map);
			}
		}
		
		// If the data is empty, there is nothing to return
		if (empty ($this->data)) {
			return '';
		}
		
		// Pull out the requested number of bytes
		$data = substr ($this->data, 0, $count);
		$this->data = substr ($this->data, $count);
		$this->tell = $this->tell + strlen ($data);
		return $data;
	}
	
	/**
	 * @see Appenda_Stream_Abstract::stream_eof()
	 *
	 * @return boolean
	 */
	public function stream_eof () {
		return is_null ($this->data) || empty ($this->data);
	}
	
	/**
	 * @see Appenda_Stream_Abstract::stream_tell()
	 *
	 * @return integer
	 */
	public function stream_tell () {
		return $this->tell;
	}
	
	/**
	 * Enter description here...
	 *
	 * @return string
	 */
	public function getChannel () {
		return parse_url ($this->getContext (), PHP_URL_PATH);
	}
	
	/**
	 * @return Appenda_Stomp_Connection
	 */
	public function getConnection () {
		if (!$this->connection) {
			$this->connection = new Appenda_Stomp_Connection ();
			$this->connection->setBrokerUri ($this->getContext ());
			$this->connection->setConnectionTimeout(10);			
			$this->connection->connect ();
		}
		
		return $this->connection;
	}
	
	/**
	 * @param Appenda_Stomp_Connection $connection
	 */
	public function setConnection (Appenda_Stomp_Connection $connection) {
		$this->connection = $connection;
	}
	
	/**
	 * @return string
	 */
	public function getContext () {
		return $this->context;
	}
	
	/**
	 * @param string $context
	 */
	public function setContext ($context) {
		assert (is_string ($context));
		$this->context = $context;
	}

}

