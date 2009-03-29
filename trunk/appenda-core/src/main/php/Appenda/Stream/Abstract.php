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

abstract class Appenda_Stream_Abstract
{
	/**
	 * Enter description here...
	 *
	 * @return boolean True always, unless an exception is thrown.
	 */
	public function setRegistered ($registered)
	{
		$className = get_class ($this);
		$protocol = strtolower (array_pop (explode ('_', $className)));
		
		if ($registered === 'true' || (is_bool ($registered) && $registered))
		{
			$success = stream_wrapper_register ($protocol, $className);
		}
		
		if ($registered === 'false' || (is_bool ($registered) && !$registered))
		{
			$success = stream_wrapper_unregister ($protocol, $className);
		}
		
		if (!$success)
		{
			$map ["message"] = "Registration / Unregistration error";
			$map ["registered"] = $registered;
			$map ["protocol"] = $protocol;
			$map ["className"] = $className;
			throw new Appenda_Exception ($map);
		}
		else
		{
			return true;
		}
	}
	
	/**
	 * This method does nothing.
	 *
	 * @return void
	 */
	public function stream_close ()
	{
	}
	
	/**
	 * This method does nothing.
	 *
	 * @return boolean True always.
	 */
	public function stream_flush ()
	{
		return true;
	}
	
	/**
	 * This method does nothing.
	 *
	 * @return boolean True always.
	 */
	public function stream_eof ()
	{
		return true;
	}
	
	/**
	 * This method is called immediately after your stream object is created. path specifies the URL that was
	 * passed to fopen() and that this object is expected to retrieve. You can use parse_url()  to break it apart.
	 *
	 * - mode is the mode used to open the file, as detailed for fopen(). You are responsible for checking that
	 * mode is valid for the path requested.
	 * - options holds additional flags set by the streams API. It can hold one or more of the following values OR'd
	 * together.
	 *
	 * Flag                   Description
	 * STREAM_USE_PATH        If path is relative, search for the resource using the include_path.
	 * STREAM_REPORT_ERRORS   If this flag is set, you are responsible for raising errors using trigger_error()
	 *                        during opening of the stream. If this flag is not set, you should not raise any errors.
	 *
	 * If the path is opened successfully, and STREAM_USE_PATH is set in options, you should set opened_path to the
	 * full path of the file/resource that was actually opened. If the requested resource was opened successfully,
	 * you should return TRUE, otherwise you should return FALSE
	 *
	 * @param string $path
	 * @param string $mode
	 * @param integer $options
	 * @param string &$opened_path
	 * @return boolean
	 */
	public function stream_open ($path, $mode, $options, &$opened_path)
	{
		return true;
	}
	
	/**
	 * This method does nothing.
	 *
	 * @param integer $count
	 * @return string|boolean
	 */
	public function stream_read ($count)
	{
		return false;
	}
	
	/**
	 * This method does nothing.
	 *
	 * @param integer $offset
	 * @param integer $whence
	 * @return boolean False always.
	 */
	public function stream_seek ($offset, $whence)
	{
		return false;
	}
	
	/**
	 * This method does nothing, but should.
	 *
	 * @return array
	 */
	public function stream_stat ()
	{
		// TODO add correct array structure
		return array ();
	}
	
	/**
	 * This method does nothing.
	 *
	 * @return integer 0 always.
	 */
	public function stream_tell ()
	{
		return 0;
	}
	
	/**
	 * Enter description here...
	 *
	 * @param string $data
	 * @return integer Number of bytes written.
	 */
	abstract public function stream_write ($incomingData);
	
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $path
	 * @param unknown_type $flags
	 * @return unknown
	 */
	public function url_stat ($path, $flags)
	{
		// TODO add correct array structure
		return array ();
	}
	
	/**
	 * Enter description here...
	 *
	 * @return boolean
	 */
	public function dir_closedir ()
	{
		return false;
	}
	
	/**
	 * Enter description here...
	 *
	 * @param unknown_type $path
	 * @param unknown_type $options
	 * @return unknown
	 */
	public function dir_opendir ($path, $options)
	{
		return false;
	}
	
	/**
	 * Enter description here...
	 *
	 * @return unknown
	 */
	public function dir_readdir ()
	{
		return false;
	}
	
	/**
	 * Enter description here...
	 *
	 * @return unknown
	 */
	public function dir_rewinddir ()
	{
		return false;
	}
}

