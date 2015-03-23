-- MySQL dump 10.13  Distrib 5.5.41, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: dndd
-- ------------------------------------------------------
-- Server version	5.5.41-0+wheezy1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `일반게시판`
--
create database dndd;
use dndd;

DROP TABLE IF EXISTS `Sample`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Sample` (
  `num` int(11) NOT NULL,
  `page` int(11) DEFAULT NULL,
  `email` char(30) NOT NULL,
  `title` char(100) DEFAULT NULL,
  `contents` longtext,
  `date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `edit` mediumint(9) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`email`,`date`,`edit`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `일반게시판`
--

LOCK TABLES `Sample` WRITE;
/*!40000 ALTER TABLE `Sample` DISABLE KEYS */;
/*!40000 ALTER TABLE `Sample` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Follow`
--

DROP TABLE IF EXISTS `Follow`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Follow` (
  `email` varchar(30) CHARACTER SET utf8 NOT NULL,
  `follower` varchar(30) CHARACTER SET utf8 DEFAULT NULL,
  `secret` tinyint(1) DEFAULT NULL,
  `date` datetime DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Follow`
--

LOCK TABLES `Follow` WRITE;
/*!40000 ALTER TABLE `Follow` DISABLE KEYS */;
/*!40000 ALTER TABLE `Follow` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Users`
--

DROP TABLE IF EXISTS `Users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Users` (
  `email` char(30) NOT NULL,
  `password` char(45) DEFAULT NULL,
  `level` tinyint(4) DEFAULT NULL,
  `name` varchar(45) DEFAULT NULL,
  `tel` varchar(20) DEFAULT NULL,
  `date` datetime NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Users`
--

LOCK TABLES `Users` WRITE;
/*!40000 ALTER TABLE `Users` DISABLE KEYS */;
INSERT INTO `Users` VALUES ('anony@anony', password('anony'),0,'anonymous','000-000-0000','2015-03-02 01:19:15');
/*!40000 ALTER TABLE `Users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Vote`
--

DROP TABLE IF EXISTS `Vote`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Vote` (
  `field` varchar(30) CHARACTER SET utf8 DEFAULT NULL,
  `num` int(11) DEFAULT NULL,
  `email` varchar(30) CHARACTER SET utf8 DEFAULT NULL,
  `votedfor` tinyint(4) DEFAULT NULL,
  `secret` tinyint(1) DEFAULT NULL,
  `date` datetime DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Vote`
--

LOCK TABLES `Vote` WRITE;
/*!40000 ALTER TABLE `Vote` DISABLE KEYS */;
/*!40000 ALTER TABLE `Vote` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `VotingBoard`
--

DROP TABLE IF EXISTS `VotingBoard`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `VotingBoard` (
  `num` int(11) NOT NULL,
  `page` int(11) DEFAULT NULL,
  `email` char(30) NOT NULL,
  `title` char(100) DEFAULT NULL,
  `contents` longtext,
  `date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `edit` mediumint(9) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`email`,`date`,`edit`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `VotingBoard`
--

LOCK TABLES `VotingBoard` WRITE;
/*!40000 ALTER TABLE `VotingBoard` DISABLE KEYS */;
/*!40000 ALTER TABLE `VotingBoard` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;
DROP TABLE IF EXISTS `Field1`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Field1` (
  `num` int(11) NOT NULL,
  `page` int(11) DEFAULT NULL,
  `email` char(30) NOT NULL,
  `title` char(100) DEFAULT NULL,
  `contents` longtext,
  `date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `edit` mediumint(9) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`email`,`date`,`edit`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;
DROP TABLE IF EXISTS `Notice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Notice` (
  `num` int(11) NOT NULL,
  `page` int(11) DEFAULT NULL,
  `email` char(30) NOT NULL,
  `title` char(100) DEFAULT NULL,
  `contents` longtext,
  `date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  `edit` mediumint(9) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`email`,`date`,`edit`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;
grant select, insert on dndd.* to 'dndd'@'%' identified by 'dndddndd';
revoke insert on dndd.Notice from 'dndd'@'%';
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-03-05 20:12:07
