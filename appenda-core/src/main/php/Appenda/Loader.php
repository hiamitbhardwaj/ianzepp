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

require_once "Zend/Loader.php";

class Appenda_Loader extends Zend_Loader
{
	/**
	 *
	 * @return string
	 */
	public function __toString ()
	{
		return get_class ($this);
	}
	
	/**
	 *
	 * @param string $class
	 * @param string|array(string) $dirs
	 * @return void
	 */
	public static function loadClass ($class, $dirs = null)
	{
		parent::loadClass ($class, $dirs);
	}
	
	/**
	 *
	 * @param string $class
	 * @return object Instance of $class
	 */
	public static function autoload ($class)
	{
		try
		{
			self::loadClass ($class);
			return $class;
		}
		catch (Exception $e)
		{
			$map ["message"] = "Caught exception during autoload attempt";
			$map ["exception"] = $e;
			$map ["className"] = $class;
			file_put_contents ("php://stderr", print_r ($map, true));
		}
		
		return false;
	}
	
	/**
	 *
	 * @param bool $load
	 * @return void
	 */
	public static function registerAutoload ($load = true)
	{
		parent::registerAutoload ('Appenda_Loader', $load);
	}
}

/**
 * Register the autoloader
 */

Appenda_Loader::registerAutoload ();
