/*
Navicat MySQL Data Transfer

Source Server         : qewrq
Source Server Version : 50709
Source Host           : 10.63.220.3:3306
Source Database       : config

Target Server Type    : MYSQL
Target Server Version : 50709
File Encoding         : 65001

Date: 2016-12-05 10:36:37
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for client
-- ----------------------------
DROP TABLE IF EXISTS `client`;
CREATE TABLE `client` (
  `ip_address` varchar(20) NOT NULL,
  `project` varchar(20) NOT NULL,
  `id_phone` varchar(8) NOT NULL,
  `status_phone` varchar(4) NOT NULL,
  `phone_ison` varchar(4) NOT NULL,
  PRIMARY KEY (`ip_address`,`project`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of client
-- ----------------------------
INSERT INTO `client` VALUES ('10.63.220.3', 'P809T70', '12345678', 'NULL', 'ON');
INSERT INTO `client` VALUES ('10.63.220.2', 'P809V50', '12345678', 'NULL', 'ON');
INSERT INTO `client` VALUES ('10.63.220.2', 'P809T70', '12345678', 'NULL', 'ON');
INSERT INTO `client` VALUES ('10.63.220.4', 'P809T70', '12345678', 'NULL', 'ON');
INSERT INTO `client` VALUES ('10.63.220.1', 'P809V50', '12345678', 'NULL', 'ON');
INSERT INTO `client` VALUES ('10.63.220.4', 'P809V50', '12345678', 'NULL', 'ON');
INSERT INTO `client` VALUES ('10.63.220.3', 'P809V50', '12345678', 'NULL', 'ON');
INSERT INTO `client` VALUES ('10.63.220.1', 'P809T70', '12345678', 'NULL', 'ON');

-- ----------------------------
-- Table structure for config
-- ----------------------------
DROP TABLE IF EXISTS `config`;
CREATE TABLE `config` (
  `ip_address` varchar(20) NOT NULL,
  `project` varchar(20) NOT NULL,
  `lcoal_version_path` varchar(100) NOT NULL,
  `ftp_ip_address` varchar(20) NOT NULL,
  `ftp_user` varchar(20) NOT NULL,
  `ftp_password` varchar(50) NOT NULL,
  `local_upload_path` varchar(50) NOT NULL,
  `ftp_config_path` varchar(50) NOT NULL,
  `config_pre_name` varchar(50) NOT NULL,
  `project_name_config` varchar(50) NOT NULL,
  `server_ip_address` varchar(50) NOT NULL,
  `local_ip_address` varchar(50) NOT NULL,
  PRIMARY KEY (`project`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of config
-- ----------------------------
INSERT INTO `config` VALUES ('10.63.220.2', 'hello', 'E:\\version\\P809T70\\P809T70.zip', '10.63.237.2', 'mengwei', 'MENGwei2275', '..\\Config_upload\\', 'out/CI_version/config_files', 'P809T70*', 'P809T70', '10.60.200.165', '10.63.220.2');
INSERT INTO `config` VALUES ('10.63.220.2', 'P809V50', 'E:\\version\\P809T70\\P809T70.zip', '10.63.237.2', '10192582', 'MENGwei2275', '..\\Config_upload\\', 'out/CI_version/config_files', 'M_P809V50*', 'P809V50', '10.60.200.165', '10.63.220.2');

-- ----------------------------
-- Table structure for friends
-- ----------------------------
DROP TABLE IF EXISTS `friends`;
CREATE TABLE `friends` (
  `user1` varchar(100) NOT NULL,
  `user2` varchar(100) NOT NULL,
  PRIMARY KEY (`user1`,`user2`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of friends
-- ----------------------------

-- ----------------------------
-- Table structure for message
-- ----------------------------
DROP TABLE IF EXISTS `message`;
CREATE TABLE `message` (
  `user1` varchar(100) NOT NULL,
  `user2` varchar(100) NOT NULL,
  `msg` varchar(100) NOT NULL,
  `sendkey` varchar(100) NOT NULL,
  PRIMARY KEY (`user1`,`user2`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of message
-- ----------------------------

-- ----------------------------
-- Table structure for server
-- ----------------------------
DROP TABLE IF EXISTS `server`;
CREATE TABLE `server` (
  `ip_address` varchar(20) NOT NULL,
  `project` varchar(20) NOT NULL,
  `id_phone` varchar(8) NOT NULL,
  `status_phone` varchar(4) NOT NULL,
  `status_pc` varchar(4) NOT NULL,
  `path_version` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`ip_address`,`project`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of server
-- ----------------------------
INSERT INTO `server` VALUES ('10.63.220.2', 'P809V50', '12345678', 'BUSY', 'BUSY', 'out/CI_version/M_P809V50/M_P809V50_ENG_VERSION_modem_244-VERSION_boot_987.zip');
INSERT INTO `server` VALUES ('10.63.220.1', 'P809V50', '12345678', 'NULL', 'NULL', 'out/CI_version/M_P809V50/M_P809V50_ENG_VERSION_modem_244-VERSION_boot_987.zip');
INSERT INTO `server` VALUES ('10.63.220.4', 'P809V50', '12345678', 'NULL', 'BUSY', 'out/CI_version/M_P809V50/M_P809V50_ENG_VERSION_modem_244-VERSION_boot_987.zip');
INSERT INTO `server` VALUES ('10.63.220.3', 'P809V50', '12345678', 'NULL', 'BUSY', 'out/CI_version/M_P809V50/M_P809V50_ENG_VERSION_modem_244-VERSION_boot_987.zip');
INSERT INTO `server` VALUES ('10.63.220.3', 'P809T70', '12345678', 'NULL', 'NULL', 'out/CI_version/P809T70/P809T70_ENG_VERSION_modem_99-VERSION_boot_280.zip');
INSERT INTO `server` VALUES ('10.63.220.2', 'P809T70', '12345678', 'NULL', 'BUSY', 'out/CI_version/P809T70/P809T70_ENG_VERSION_modem_99-VERSION_boot_280.zip');
INSERT INTO `server` VALUES ('10.63.220.4', 'P809T70', '12345678', 'NULL', 'BUSY', 'out/CI_version/P809T70/P809T70_ENG_VERSION_modem_99-VERSION_boot_280.zip');
INSERT INTO `server` VALUES ('10.63.220.1', 'P809T70', '12345678', 'NULL', 'BUSY', 'out/CI_version/P809T70/P809T70_ENG_VERSION_modem_99-VERSION_boot_280.zip');

-- ----------------------------
-- Table structure for tutorials_tb2
-- ----------------------------
DROP TABLE IF EXISTS `tutorials_tb2`;
CREATE TABLE `tutorials_tb2` (
  `tutorial_id` int(11) NOT NULL AUTO_INCREMENT,
  `tutorial_title` varchar(100) NOT NULL,
  `tutorial_author` varchar(40) NOT NULL,
  `submission_date` date DEFAULT NULL,
  PRIMARY KEY (`tutorial_id`,`tutorial_title`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of tutorials_tb2
-- ----------------------------

-- ----------------------------
-- Table structure for tutorials_tbl
-- ----------------------------
DROP TABLE IF EXISTS `tutorials_tbl`;
CREATE TABLE `tutorials_tbl` (
  `tutorial_id` int(11) NOT NULL AUTO_INCREMENT,
  `tutorial_title` varchar(100) NOT NULL,
  `tutorial_author` varchar(40) NOT NULL,
  `submission_date` date DEFAULT NULL,
  PRIMARY KEY (`tutorial_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of tutorials_tbl
-- ----------------------------

-- ----------------------------
-- Table structure for version
-- ----------------------------
DROP TABLE IF EXISTS `version`;
CREATE TABLE `version` (
  `client_version` double(11,2) NOT NULL,
  `server_version` double(11,2) NOT NULL,
  `server_path` varchar(100) NOT NULL,
  `client_path` varchar(100) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of version
-- ----------------------------
INSERT INTO `version` VALUES ('2.10', '2.01', '\\\\10.63.220.2\\every_build\\SOURCE\\server_update', '\\\\10.63.220.2\\every_build\\SOURCE\\client_update');

-- ----------------------------
-- View structure for client_view
-- ----------------------------
DROP VIEW IF EXISTS `client_view`;
CREATE ALGORITHM=UNDEFINED DEFINER=``@`` SQL SECURITY DEFINER  VIEW `client_view` AS SELECT
	*
FROM
	client ;

-- ----------------------------
-- View structure for server_view
-- ----------------------------
DROP VIEW IF EXISTS `server_view`;
CREATE ALGORITHM=UNDEFINED DEFINER=``@`` SQL SECURITY DEFINER  VIEW `server_view` AS SELECT
*
FROM
`server` ;

-- ----------------------------
-- Procedure structure for hello
-- ----------------------------
DROP PROCEDURE IF EXISTS `hello`;
DELIMITER ;;
CREATE DEFINER=``@`` PROCEDURE `hello`()
BEGIN
DECLARE exista INT;
(select count(*) into exista from (select project  from client_view WHERE ip_address ='10.63.220.2') as VIEW WHERE project = 'P809T70');

if exista = 0 then 
insert into client values ('10.63.220.2','P809T70',12365498,1) ;
end if;
END
;;
DELIMITER ;
