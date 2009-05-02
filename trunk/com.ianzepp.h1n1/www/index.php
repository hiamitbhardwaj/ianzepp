<?php
/**
 * My new Zend Framework project
 * 
 * @author  
 * @version 
 */

set_include_path(get_include_path() . PATH_SEPARATOR . '.');
set_include_path(get_include_path() . PATH_SEPARATOR . '../library');
set_include_path(get_include_path() . PATH_SEPARATOR . '../application/models/');

require_once 'Zend/Controller/Front.php';
require_once 'Zend/Layout.php';

// Setup controller
$controller = Zend_Controller_Front::getInstance();
$controller->setControllerDirectory('../application/controllers');
$controller->throwExceptions(false); // should be turned on in development time 
$controller->dispatch();
