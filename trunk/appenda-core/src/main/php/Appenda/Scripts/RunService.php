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

/** Basic framework */
require_once "Appenda/Core.php";
require_once "Appenda/Scripts/ProcessArguments.php";

/** Validate the script arguments */
global $_ARGUMENTS;

if (!$_ARGUMENTS ["beanConfig"])
{
	exit ("Missing required argument: --beanConfig");
}

if (!$_ARGUMENTS ["bean"])
{
	exit ("Missing required argument: --bean");
}

/** Load the beans */
$beanContainer = new Appenda_Bundle_BeanContainer ();
$beanContainer->processConfig ($_ARGUMENTS ["beanConfig"]);

/** Do we override logging with another context? */
if ($_ARGUMENTS ["loggingContext"])
{
	$staticLogging = new Appenda_Stream_Logging ();
	$staticLogging->setContent ($_ARGUMENTS ["loggingContexT"]);
}

/** Start the message processing */
$bean = $beanContainer->findBean ($_ARGUMENTS ["bean"]);
$bean->getBeanInstance ()->processMessages ();

// Done!

