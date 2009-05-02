CREATE SCHEMA IF NOT EXISTS `h1n1`;

#
#
#
DROP TABLE IF EXISTS `h1n1`.`infections`;
CREATE TABLE `h1n1`.`infections` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `created_at` datetime NOT NULL,
  `updated_at` datetime default NULL,
  `deleted_at` datetime default NULL,
  `num_suspected` int(10) unsigned NOT NULL,
  `num_confirmed` int(10) unsigned NOT NULL,
  `num_fatal` int(10) unsigned NOT NULL,
  `geo_latitude` decimal(10,0) default NULL,
  `geo_longitude` decimal(10,0) default NULL,
  `loc_country` tinytext,
  `loc_province` tinytext,
  `description` text,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

