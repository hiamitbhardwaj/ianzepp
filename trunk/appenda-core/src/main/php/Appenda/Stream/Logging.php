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

class Appenda_Stream_Logging extends Appenda_Stream_Abstract
{
	public static $context = "php://stdout";
	private $level;
	private $path;
	
	/**
	 * TODO Put this to use.
	 *
	 * @var string
	 */
	const REGEX_EXCEPTION = "/^exception '(.+?)' with message '(.+)' in (.+?):(.+?)\nStack trace:\n(.+)$/";
	
	/**
	 * @see Appenda_Stream_Abstract::stream_open()
	 *
	 * @param string $path
	 * @param string $mode
	 * @param integer $options
	 * @param unknown_type $opened_path
	 * @return boolean
	 */
	public function stream_open ($path, $mode, $options, &$opened_path)
	{
		$this->setLevel (parse_url ($path, PHP_URL_HOST));
		$this->setPath (parse_url ($path, PHP_URL_PATH));
		return true;
	}
	
	/**
	 * @see Appenda_Stream_Abstract::stream_write()
	 *
	 * @param string $incomingData
	 * @return integer
	 */
	public function stream_write ($incomingData)
	{
		if ($this->getPath ())
		{
			$context = $this->getContext () . $this->getPath ();
		}
		else
		{
			$context = $this->getContext ();
		}
		
		// Build a message
		$xml = simplexml_load_string ("<insertEvent />");
		$xml->{"created_at"} = time ();
		$xml->{"level"} = $this->getLevel ();
		$xml->{"message"} = $incomingData;
		
		// Send the message
		file_put_contents ($context, $xml->asXML (), FILE_USE_INCLUDE_PATH | FILE_APPEND);
		return strlen ($incomingData);
	}
	
	/**
	 * @return string
	 */
	public static function getContext ()
	{
		return self::$context;
	}
	
	/**
	 * @return string
	 */
	public function getLevel ()
	{
		return $this->level;
	}
	
	/**
	 * @param string $context
	 */
	public static function setContext ($context)
	{
		self::$context = $context;
	}
	
	/**
	 * @param string $level
	 */
	public function setLevel ($level)
	{
		$this->level = strtoupper ($level);
	}
	
	/**
	 * @return string
	 */
	public function getPath ()
	{
		return $this->path;
	}
	
	/**
	 * @param string $path
	 */
	public function setPath ($path)
	{
		$this->path = $path;
	}

}