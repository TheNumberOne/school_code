-- MySQL dump 10.16  Distrib 10.1.29-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: 74.220.207.161    Database: sethtimm_4407
-- ------------------------------------------------------
-- Server version	5.6.41-84.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `balloon`
--

DROP TABLE IF EXISTS `balloon`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `balloon` (
  `id` int(9) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `color` varchar(32) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `balloon`
--

LOCK TABLES `balloon` WRITE;
/*!40000 ALTER TABLE `balloon` DISABLE KEYS */;
INSERT INTO `balloon` VALUES (000000001,'Red'),(000000002,'Blue'),(000000003,'Green'),(000000004,'Black'),(000000005,'Grey'),(000000006,'Pink');
/*!40000 ALTER TABLE `balloon` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `credit_card`
--

DROP TABLE IF EXISTS `credit_card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `credit_card` (
  `number` varchar(16) NOT NULL,
  `type` varchar(32) NOT NULL,
  `exp_month` int(2) unsigned zerofill NOT NULL,
  `exp_year` int(4) unsigned zerofill NOT NULL,
  PRIMARY KEY (`number`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `credit_card`
--

LOCK TABLES `credit_card` WRITE;
/*!40000 ALTER TABLE `credit_card` DISABLE KEYS */;
INSERT INTO `credit_card` VALUES ('1234123412341234','Visa',01,2020),('2345234523452345','Mastercard',02,2020),('3456345634563456','Discover',03,2020),('4567456745674567','Visa',04,2020),('5678567856785678','American Express',05,2020);
/*!40000 ALTER TABLE `credit_card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `customer` (
  `id` int(9) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL,
  `address` varchar(64) NOT NULL,
  `city` varchar(64) NOT NULL,
  `state` varchar(64) NOT NULL,
  `zip` varchar(10) NOT NULL,
  `phone` varchar(16) NOT NULL,
  `email` varchar(256) NOT NULL,
  `credit_balance` decimal(9,2) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (000000001,'Seth','921 South 8th Avenue','Pocatello','Idaho','83201','5555555555','timmseth@isu.edu',0.00),(000000002,'Rosetta','921 South 8th Avenue','Pocatello','Idaho','83201','5555555555','robepea2@isu.edu',0.00),(000000003,'Dylan','921 South 8th Avenue','Pocatello','Idaho','83201','5555555555','lashdyla@isu.edu',0.00),(000000004,'Vincent','921 South 8th Avenue','Pocatello','Idaho','83201','5555555555','timmseth@isu.edu',0.00),(000000005,'Adam','921 South 8th Avenue','Pocatello','Idaho','83201','5555555555','timmseth@isu.edu',0.00);
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `employee`
--

DROP TABLE IF EXISTS `employee`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `employee` (
  `id` int(9) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `ssn` int(9) unsigned zerofill NOT NULL,
  `name` varchar(64) NOT NULL,
  `address` varchar(64) NOT NULL,
  `city` varchar(64) NOT NULL,
  `state` varchar(64) NOT NULL,
  `zip` varchar(10) NOT NULL,
  `home_phone` varchar(16) DEFAULT NULL,
  `cell_phone` varchar(16) DEFAULT NULL,
  `email` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `employee`
--

LOCK TABLES `employee` WRITE;
/*!40000 ALTER TABLE `employee` DISABLE KEYS */;
INSERT INTO `employee` VALUES (000000001,111111111,'A John Doe','921 South 8th Avenue','Pocatello','Idaho','83201','5555555555','5555555555','timmseth@isu.edu'),(000000002,222222222,'B John Doe','921 South 8th Avenue','Pocatello','Idaho','83201','5555555555','5555555555','timmseth@isu.edu'),(000000003,333333333,'C John Doe','921 South 8th Avenue','Pocatello','Idaho','83201','5555555555','5555555555','timmseth@isu.edu'),(000000004,444444444,'D John Doe','921 South 8th Avenue','Pocatello','Idaho','83201','5555555555','5555555555','timmseth@isu.edu'),(000000005,555555555,'E John Doe','921 South 8th Avenue','Pocatello','Idaho','83201','5555555555','5555555555','timmseth@isu.edu');
/*!40000 ALTER TABLE `employee` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `holds_account`
--

DROP TABLE IF EXISTS `holds_account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `holds_account` (
  `fk_customer_id` int(9) unsigned zerofill NOT NULL,
  `fk_credit_card_number` varchar(16) NOT NULL,
  PRIMARY KEY (`fk_customer_id`,`fk_credit_card_number`),
  KEY `fk_customer_ndx` (`fk_customer_id`),
  KEY `fk_cc_ndx` (`fk_credit_card_number`),
  CONSTRAINT `fk_cc_hold_constraint` FOREIGN KEY (`fk_credit_card_number`) REFERENCES `credit_card` (`number`) ON UPDATE CASCADE,
  CONSTRAINT `fk_cust_hold_constraint` FOREIGN KEY (`fk_customer_id`) REFERENCES `customer` (`id`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `holds_account`
--

LOCK TABLES `holds_account` WRITE;
/*!40000 ALTER TABLE `holds_account` DISABLE KEYS */;
INSERT INTO `holds_account` VALUES (000000001,'3456345634563456'),(000000002,'2345234523452345'),(000000002,'5678567856785678'),(000000003,'1234123412341234'),(000000003,'4567456745674567');
/*!40000 ALTER TABLE `holds_account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `line_item`
--

DROP TABLE IF EXISTS `line_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `line_item` (
  `fk_purchase_agreement_id` int(9) unsigned zerofill NOT NULL,
  `fk_piece_of_eq_id` int(9) unsigned zerofill NOT NULL,
  PRIMARY KEY (`fk_purchase_agreement_id`,`fk_piece_of_eq_id`),
  KEY `fk_sn_ndx` (`fk_purchase_agreement_id`),
  KEY `fk_pa_ndx` (`fk_purchase_agreement_id`) USING BTREE,
  KEY `fk_sn_li_constraint` (`fk_piece_of_eq_id`),
  CONSTRAINT `fk_pa_constraint` FOREIGN KEY (`fk_purchase_agreement_id`) REFERENCES `purchase_agreement` (`id`) ON UPDATE CASCADE,
  CONSTRAINT `fk_sn_li_constraint` FOREIGN KEY (`fk_piece_of_eq_id`) REFERENCES `piece_of_eq` (`id_serial_number`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `line_item`
--

LOCK TABLES `line_item` WRITE;
/*!40000 ALTER TABLE `line_item` DISABLE KEYS */;
INSERT INTO `line_item` VALUES (000000001,000000005),(000000002,000000004),(000000003,000000003),(000000004,000000002),(000000005,000000001),(000000009,000000005);
/*!40000 ALTER TABLE `line_item` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `line_item_eq`
--

DROP TABLE IF EXISTS `line_item_eq`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `line_item_eq` (
  `fk_order_id` int(9) unsigned zerofill NOT NULL,
  `fk_model_id` int(9) unsigned zerofill NOT NULL,
  `eq_quantity` int(9) NOT NULL,
  `eq_price` decimal(9,2) NOT NULL,
  PRIMARY KEY (`fk_order_id`,`fk_model_id`),
  KEY `fk_order_ndx` (`fk_order_id`) USING BTREE,
  KEY `fk_model_ndx` (`fk_model_id`) USING BTREE,
  CONSTRAINT `fk_model_lie_constraint` FOREIGN KEY (`fk_model_id`) REFERENCES `product_category` (`id_model_number`) ON UPDATE CASCADE,
  CONSTRAINT `fk_order_lie_constraint` FOREIGN KEY (`fk_order_id`) REFERENCES `orders` (`id`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `line_item_eq`
--

LOCK TABLES `line_item_eq` WRITE;
/*!40000 ALTER TABLE `line_item_eq` DISABLE KEYS */;
INSERT INTO `line_item_eq` VALUES (000000001,000000005,1,75.00),(000000002,000000002,1,50.00),(000000002,000000005,1,54.00),(000000003,000000001,1,25.00),(000000004,000000003,1,36.00);
/*!40000 ALTER TABLE `line_item_eq` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `orders`
--

DROP TABLE IF EXISTS `orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `orders` (
  `id` int(9) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `date_placed` date NOT NULL,
  `date_received` date DEFAULT NULL,
  `fk_supplier_id` int(9) unsigned zerofill NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_supplier_constraint` (`fk_supplier_id`),
  CONSTRAINT `fk_supplier_constraint` FOREIGN KEY (`fk_supplier_id`) REFERENCES `supplier` (`id`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `orders`
--

LOCK TABLES `orders` WRITE;
/*!40000 ALTER TABLE `orders` DISABLE KEYS */;
INSERT INTO `orders` VALUES (000000001,'2019-02-01','2019-02-06',000000001),(000000002,'2014-02-02','2019-02-07',000000002),(000000003,'2019-02-03','2019-02-08',000000003),(000000004,'2019-02-04','2019-02-09',000000004),(000000005,'2019-02-05',NULL,000000005);
/*!40000 ALTER TABLE `orders` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `piece_of_eq`
--

DROP TABLE IF EXISTS `piece_of_eq`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `piece_of_eq` (
  `id_serial_number` int(9) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `type` varchar(64) NOT NULL,
  `description` text NOT NULL,
  `purchase_date` date NOT NULL,
  `purchase_price` decimal(9,2) NOT NULL DEFAULT '0.00',
  `sale_price` decimal(9,2) NOT NULL DEFAULT '0.00',
  `fk_product_category_id` int(9) unsigned zerofill NOT NULL DEFAULT '000000001',
  `fk_customer_id` int(9) unsigned zerofill NOT NULL,
  `fk_employee_id` int(9) unsigned zerofill NOT NULL,
  PRIMARY KEY (`id_serial_number`),
  KEY `fk_cust_poe_ndx` (`fk_customer_id`) USING BTREE,
  KEY `fk_emp_poe_ndx` (`fk_employee_id`) USING BTREE,
  KEY `fk_product_category_ndx` (`fk_product_category_id`),
  CONSTRAINT `fk_cust_poe_constraint` FOREIGN KEY (`fk_customer_id`) REFERENCES `customer` (`id`) ON UPDATE CASCADE,
  CONSTRAINT `fk_emp_poe_constraint` FOREIGN KEY (`fk_employee_id`) REFERENCES `employee` (`id`) ON UPDATE CASCADE,
  CONSTRAINT `fk_pc_model_constraint` FOREIGN KEY (`fk_product_category_id`) REFERENCES `product_category` (`id_model_number`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `piece_of_eq`
--

LOCK TABLES `piece_of_eq` WRITE;
/*!40000 ALTER TABLE `piece_of_eq` DISABLE KEYS */;
INSERT INTO `piece_of_eq` VALUES (000000001,'eq type one','Eq Description One','2019-02-01',75.00,95.00,000000001,000000002,000000001),(000000002,'eq type two','Eq Description two','2019-02-01',75.00,95.00,000000002,000000002,000000001),(000000003,'eq type three','Eq Description three','2019-02-01',75.00,95.00,000000003,000000002,000000001),(000000004,'eq type four','Eq Description four','2019-02-01',75.00,95.00,000000004,000000003,000000002),(000000005,'eq type five','Eq Description five','2019-02-01',75.00,95.00,000000005,000000003,000000002);
/*!40000 ALTER TABLE `piece_of_eq` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `product_category`
--

DROP TABLE IF EXISTS `product_category`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `product_category` (
  `id_model_number` int(9) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `description` text NOT NULL,
  `manufacturer` varchar(255) NOT NULL,
  `inv_count` int(11) NOT NULL DEFAULT '0',
  `reorder_quantity` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id_model_number`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `product_category`
--

LOCK TABLES `product_category` WRITE;
/*!40000 ALTER TABLE `product_category` DISABLE KEYS */;
INSERT INTO `product_category` VALUES (000000001,'ProductCatOne','ProductManOne',7,1),(000000002,'ProductCatTwo','ProductManTwo',7,1),(000000003,'ProductCatThree','ProductManThree',7,1),(000000004,'ProductCatFour','ProductManFour',7,1),(000000005,'ProductCatFive','ProductManFive',7,1),(000000006,'4fight LT (long Tail) Integral Size medium','Aeros',12,2);
/*!40000 ALTER TABLE `product_category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `purchase_agreement`
--

DROP TABLE IF EXISTS `purchase_agreement`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `purchase_agreement` (
  `id` int(9) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `payment_type` varchar(8) NOT NULL,
  `date` date NOT NULL,
  `time` time NOT NULL,
  `fk_customer_id` int(9) unsigned zerofill NOT NULL,
  `fk_cc_number` varchar(16) DEFAULT NULL,
  `fk_employee_id` int(9) unsigned zerofill NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_customer_id` (`fk_customer_id`),
  KEY `fk_cc_number` (`fk_cc_number`),
  KEY `fk_employee_id` (`fk_employee_id`),
  CONSTRAINT `fk_cc_pa_constraint` FOREIGN KEY (`fk_cc_number`) REFERENCES `credit_card` (`number`) ON UPDATE CASCADE,
  CONSTRAINT `fk_cust_pa_constraint` FOREIGN KEY (`fk_customer_id`) REFERENCES `customer` (`id`) ON UPDATE CASCADE,
  CONSTRAINT `fk_emp_pa_restraint` FOREIGN KEY (`fk_employee_id`) REFERENCES `employee` (`id`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `purchase_agreement`
--

LOCK TABLES `purchase_agreement` WRITE;
/*!40000 ALTER TABLE `purchase_agreement` DISABLE KEYS */;
INSERT INTO `purchase_agreement` VALUES (000000001,'Card','2019-02-01','05:25:24',000000003,'1234123412341234',000000001),(000000002,'Card','2019-02-01','06:25:24',000000003,'1234123412341234',000000002),(000000003,'Card','2019-02-01','06:25:24',000000002,'2345234523452345',000000003),(000000004,'Card','2019-02-01','06:25:24',000000002,'2345234523452345',000000004),(000000005,'Card','2019-02-01','06:25:24',000000001,'3456345634563456',000000005),(000000009,'Cash','2010-10-06','12:15:14',000000004,NULL,000000003);
/*!40000 ALTER TABLE `purchase_agreement` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `reservation`
--

DROP TABLE IF EXISTS `reservation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `reservation` (
  `id` int(9) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `fk_balloon_id` int(9) unsigned zerofill NOT NULL,
  `fk_customer_id` int(9) unsigned zerofill NOT NULL,
  `last_modified` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `fk_balloon_ndx` (`fk_balloon_id`),
  KEY `fk_customer_ndx` (`fk_customer_id`),
  CONSTRAINT `fk_balloon_constraint` FOREIGN KEY (`fk_balloon_id`) REFERENCES `balloon` (`id`) ON UPDATE CASCADE,
  CONSTRAINT `fk_customer_constraint` FOREIGN KEY (`fk_customer_id`) REFERENCES `customer` (`id`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reservation`
--

LOCK TABLES `reservation` WRITE;
/*!40000 ALTER TABLE `reservation` DISABLE KEYS */;
INSERT INTO `reservation` VALUES (000000001,000000004,000000001,'2019-02-22 03:17:52'),(000000002,000000002,000000002,'2019-02-22 03:18:20'),(000000003,000000003,000000003,'2019-02-22 03:18:20'),(000000004,000000006,000000001,'2019-02-22 03:18:20'),(000000005,000000006,000000004,'2019-02-22 03:18:20');
/*!40000 ALTER TABLE `reservation` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `return_item`
--

DROP TABLE IF EXISTS `return_item`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `return_item` (
  `id` int(9) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `fk_serial_id` int(9) unsigned zerofill NOT NULL,
  `reason` text NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_serial_ndx` (`fk_serial_id`),
  CONSTRAINT `fk_sn_r_constraint` FOREIGN KEY (`fk_serial_id`) REFERENCES `piece_of_eq` (`id_serial_number`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `return_item`
--

LOCK TABLES `return_item` WRITE;
/*!40000 ALTER TABLE `return_item` DISABLE KEYS */;
INSERT INTO `return_item` VALUES (000000001,000000001,'broken'),(000000002,000000002,'didnt want it'),(000000003,000000003,'smells funny'),(000000004,000000003,'tastes like eggs'),(000000005,000000005,'looked like my father');
/*!40000 ALTER TABLE `return_item` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `returns`
--

DROP TABLE IF EXISTS `returns`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `returns` (
  `id` int(9) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `fk_customer_id` int(9) unsigned zerofill NOT NULL,
  PRIMARY KEY (`id`),
  KEY `fk_cust_return_constraint` (`fk_customer_id`),
  CONSTRAINT `fk_cust_return_constraint` FOREIGN KEY (`fk_customer_id`) REFERENCES `customer` (`id`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `returns`
--

LOCK TABLES `returns` WRITE;
/*!40000 ALTER TABLE `returns` DISABLE KEYS */;
INSERT INTO `returns` VALUES (000000002,000000002),(000000003,000000002),(000000001,000000003),(000000005,000000003),(000000004,000000004);
/*!40000 ALTER TABLE `returns` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `salesperson`
--

DROP TABLE IF EXISTS `salesperson`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `salesperson` (
  `fk_employee_id` int(9) unsigned zerofill NOT NULL,
  `sales_count` int(9) NOT NULL DEFAULT '0',
  `commission_percentage` decimal(9,7) NOT NULL DEFAULT '0.0000000',
  `sales_amount` decimal(9,2) NOT NULL DEFAULT '0.00',
  PRIMARY KEY (`fk_employee_id`),
  CONSTRAINT `fk_employee_salesperson_constraint` FOREIGN KEY (`fk_employee_id`) REFERENCES `employee` (`id`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `salesperson`
--

LOCK TABLES `salesperson` WRITE;
/*!40000 ALTER TABLE `salesperson` DISABLE KEYS */;
INSERT INTO `salesperson` VALUES (000000001,10,0.1000000,100.00),(000000002,20,0.2000000,200.00),(000000003,30,0.3000000,300.00),(000000004,40,0.4000000,400.00),(000000005,50,0.5000000,500.00);
/*!40000 ALTER TABLE `salesperson` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `supplier`
--

DROP TABLE IF EXISTS `supplier`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `supplier` (
  `id` int(9) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `name` varchar(64) NOT NULL,
  `address` varchar(64) NOT NULL,
  `city` varchar(64) NOT NULL,
  `state` varchar(64) NOT NULL,
  `zip` varchar(10) NOT NULL,
  `phone` varchar(16) DEFAULT NULL,
  `fax` varchar(16) DEFAULT NULL,
  `contact_email` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `supplier`
--

LOCK TABLES `supplier` WRITE;
/*!40000 ALTER TABLE `supplier` DISABLE KEYS */;
INSERT INTO `supplier` VALUES (000000001,'Supplies R Us','1234 Address Place','Pocatello','Idaho','83201','5555555555','5555555555','timmseth@isu.edu'),(000000002,'Supplies R We','1234 Address Place','Pocatello','Idaho','83201','5555555555','5555555555','timmseth@isu.edu'),(000000003,'Supplies R You','1234 Address Place','Pocatello','Idaho','83201','5555555555','5555555555','timmseth@isu.edu'),(000000004,'Supplies R Them','1234 Address Place','Pocatello','Idaho','83201','5555555555','5555555555','timmseth@isu.edu'),(000000005,'Supplies R Other','1234 Address Place','Pocatello','Idaho','83201','5555555555','5555555555','timmseth@isu.edu');
/*!40000 ALTER TABLE `supplier` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-03-13  0:54:07
