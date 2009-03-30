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

-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.0.67-0ubuntu6


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema appenda
--

CREATE DATABASE IF NOT EXISTS `appenda_bundle_account`;
USE `appenda_bundle_account`;

--
-- Definition of table `accounts`
--

DROP TABLE IF EXISTS `accounts`;
CREATE TABLE  `accounts` (
  `account_id` char(36) NOT NULL,
  `created_at` int(10) unsigned NOT NULL,
  `updated_at` int(10) unsigned default NULL,
  `deleted_at` int(10) unsigned default NULL,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY  (`account_id`)
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

--
-- Dumping data for table `accounts`
--

/*!40000 ALTER TABLE `accounts` DISABLE KEYS */;
LOCK TABLES `accounts` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `accounts` ENABLE KEYS */;


--
-- Definition of table `accounts_addresses`
--

DROP TABLE IF EXISTS `accounts_addresses`;
CREATE TABLE  `accounts_addresses` (
  `account_address_id` int(10) unsigned NOT NULL auto_increment,
  `account_id` char(36) NOT NULL,
  `address_id` char(36) NOT NULL,
  `created_at` int(10) unsigned NOT NULL,
  `deleted_at` int(10) unsigned default NULL,
  PRIMARY KEY  (`account_address_id`),
  KEY `FK_ACC_ADD_JOIN_ACC` (`account_id`),
  KEY `FK_ACC_ADD_JOIN_ADD` (`address_id`),
  CONSTRAINT `FK_ACC_ADD_JOIN_ACC` FOREIGN KEY (`account_id`) REFERENCES `accounts` (`account_id`) ON DELETE CASCADE,
  CONSTRAINT `FK_ACC_ADD_JOIN_ADD` FOREIGN KEY (`address_id`) REFERENCES `addresses` (`address_id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

--
-- Dumping data for table `accounts_addresses`
--

/*!40000 ALTER TABLE `accounts_addresses` DISABLE KEYS */;
LOCK TABLES `accounts_addresses` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `accounts_addresses` ENABLE KEYS */;


--
-- Definition of table `accounts_contacts`
--

DROP TABLE IF EXISTS `accounts_contacts`;
CREATE TABLE  `accounts_contacts` (
  `account_contact_id` int(10) unsigned NOT NULL auto_increment,
  `account_id` char(36) NOT NULL,
  `contact_id` char(36) NOT NULL,
  `created_at` int(10) unsigned NOT NULL,
  `deleted_at` int(10) unsigned default NULL,
  PRIMARY KEY  (`account_contact_id`),
  KEY `FK_ACC_CON_JOIN_ACC` (`account_id`),
  KEY `FK_ACC_CON_JOIN_CON` (`contact_id`),
  CONSTRAINT `FK_ACC_CON_JOIN_ACC` FOREIGN KEY (`account_id`) REFERENCES `accounts` (`account_id`) ON DELETE CASCADE,
  CONSTRAINT `FK_ACC_CON_JOIN_CON` FOREIGN KEY (`contact_id`) REFERENCES `contacts` (`contact_id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

--
-- Dumping data for table `accounts_contacts`
--

/*!40000 ALTER TABLE `accounts_contacts` DISABLE KEYS */;
LOCK TABLES `accounts_contacts` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `accounts_contacts` ENABLE KEYS */;


--
-- Definition of table `accounts_phones`
--

DROP TABLE IF EXISTS `accounts_phones`;
CREATE TABLE  `accounts_phones` (
  `account_phone_id` int(10) unsigned NOT NULL auto_increment,
  `account_id` char(36) NOT NULL,
  `phone_id` char(36) NOT NULL,
  `created_at` int(10) unsigned NOT NULL,
  `deleted_at` int(10) unsigned default NULL,
  PRIMARY KEY  (`account_phone_id`),
  KEY `FK_ACC_PHO_JOIN_ACC` (`account_id`),
  KEY `FK_ACC_PHO_JOIN_PHO` (`phone_id`),
  CONSTRAINT `FK_ACC_PHO_JOIN_ACC` FOREIGN KEY (`account_id`) REFERENCES `accounts` (`account_id`) ON DELETE CASCADE,
  CONSTRAINT `FK_ACC_PHO_JOIN_PHO` FOREIGN KEY (`phone_id`) REFERENCES `phones` (`phone_id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

--
-- Dumping data for table `accounts_phones`
--

/*!40000 ALTER TABLE `accounts_phones` DISABLE KEYS */;
LOCK TABLES `accounts_phones` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `accounts_phones` ENABLE KEYS */;


--
-- Definition of table `addresses`
--

DROP TABLE IF EXISTS `addresses`;
CREATE TABLE  `addresses` (
  `address_id` char(36) NOT NULL,
  `created_at` int(10) unsigned NOT NULL,
  `updated_at` int(10) unsigned default NULL,
  `deleted_at` int(10) unsigned default NULL,
  `company` varchar(255) default NULL,
  `attention` varchar(255) default NULL,
  `country_code` varchar(10) NOT NULL,
  `province` varchar(255) default NULL,
  `city` varchar(255) NOT NULL,
  `postal_code` varchar(10) default NULL,
  `street` varchar(255) NOT NULL,
  PRIMARY KEY  (`address_id`)
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

--
-- Dumping data for table `addresses`
--

/*!40000 ALTER TABLE `addresses` DISABLE KEYS */;
LOCK TABLES `addresses` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `addresses` ENABLE KEYS */;


--
-- Definition of table `contacts`
--

DROP TABLE IF EXISTS `contacts`;
CREATE TABLE  `contacts` (
  `contact_id` char(36) NOT NULL,
  `created_at` int(10) unsigned NOT NULL,
  `updated_at` int(10) unsigned default NULL,
  `deleted_at` int(10) unsigned default NULL,
  `first_name` varchar(255) NOT NULL,
  `middle_name` varchar(255) default NULL,
  `last_name` varchar(255) NOT NULL,
  `salutation` varchar(20) default NULL,
  `suffix` varchar(20) default NULL,
  PRIMARY KEY  (`contact_id`)
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

--
-- Dumping data for table `contacts`
--

/*!40000 ALTER TABLE `contacts` DISABLE KEYS */;
LOCK TABLES `contacts` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `contacts` ENABLE KEYS */;


--
-- Definition of table `contacts_addresses`
--

DROP TABLE IF EXISTS `contacts_addresses`;
CREATE TABLE  `contacts_addresses` (
  `contact_address_id` int(10) unsigned NOT NULL auto_increment,
  `contact_id` char(36) NOT NULL,
  `address_id` char(36) NOT NULL,
  `created_at` int(10) unsigned NOT NULL,
  `deleted_at` int(10) unsigned default NULL,
  PRIMARY KEY  (`contact_address_id`),
  KEY `FK_CON_ADD_JOIN_CON` (`contact_id`),
  KEY `FK_CON_ADD_JOIN_ADD` (`address_id`),
  CONSTRAINT `FK_CON_ADD_JOIN_ADD` FOREIGN KEY (`address_id`) REFERENCES `addresses` (`address_id`) ON DELETE CASCADE,
  CONSTRAINT `FK_CON_ADD_JOIN_CON` FOREIGN KEY (`contact_id`) REFERENCES `contacts` (`contact_id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

--
-- Dumping data for table `contacts_addresses`
--

/*!40000 ALTER TABLE `contacts_addresses` DISABLE KEYS */;
LOCK TABLES `contacts_addresses` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `contacts_addresses` ENABLE KEYS */;


--
-- Definition of table `contacts_phones`
--

DROP TABLE IF EXISTS `contacts_phones`;
CREATE TABLE  `contacts_phones` (
  `contact_phone_id` int(10) unsigned NOT NULL auto_increment,
  `contact_id` char(36) NOT NULL,
  `phone_id` char(36) NOT NULL,
  `created_at` int(10) unsigned NOT NULL,
  `deleted_at` int(10) unsigned default NULL,
  PRIMARY KEY  (`contact_phone_id`),
  KEY `FK_CON_PHO_JOIN_CON` (`contact_id`),
  KEY `FK_CON_PHO_JOIN_PHO` (`phone_id`),
  CONSTRAINT `FK_CON_PHO_JOIN_CON` FOREIGN KEY (`contact_id`) REFERENCES `contacts` (`contact_id`) ON DELETE CASCADE,
  CONSTRAINT `FK_CON_PHO_JOIN_PHO` FOREIGN KEY (`phone_id`) REFERENCES `phones` (`phone_id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

--
-- Dumping data for table `contacts_phones`
--

/*!40000 ALTER TABLE `contacts_phones` DISABLE KEYS */;
LOCK TABLES `contacts_phones` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `contacts_phones` ENABLE KEYS */;


--
-- Definition of table `phones`
--

DROP TABLE IF EXISTS `phones`;
CREATE TABLE  `phones` (
  `phone_id` char(36) NOT NULL,
  `created_at` int(10) unsigned NOT NULL,
  `updated_at` int(10) unsigned default NULL,
  `deleted_at` int(10) unsigned default NULL,
  `country_code` int(11) default NULL,
  `number` int(11) NOT NULL,
  `extention` int(11) default NULL,
  PRIMARY KEY  (`phone_id`)
) ENGINE=InnoDB DEFAULT CHARSET=ascii;

--
-- Dumping data for table `phones`
--

/*!40000 ALTER TABLE `phones` DISABLE KEYS */;
LOCK TABLES `phones` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `phones` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
