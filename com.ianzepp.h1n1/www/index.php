<?php
/**
 * My new Zend Framework project
 * 
 * @author  
 * @version 
 */

set_include_path (get_include_path () . PATH_SEPARATOR . '.');
set_include_path (get_include_path () . PATH_SEPARATOR . '../library');
set_include_path (get_include_path () . PATH_SEPARATOR . '../application/models/');

require_once 'Zend/Loader.php';
Zend_Loader::registerAutoload();

// Setup default DB connection
$config['host'] = 'localhost';
$config['username'] = 'root';
$config['password'] = '';
$config['dbname'] = 'h1n1';

$defaultDB = Zend_Db::factory ('Pdo_Mysql', $config);
Zend_Db_Table_Abstract::setDefaultAdapter ($defaultDB);

// Setup controller
$controller = Zend_Controller_Front::getInstance ();
$controller->setControllerDirectory ('../application/controllers');
$controller->throwExceptions (false); // should be turned on in development time 
$controller->dispatch ();
