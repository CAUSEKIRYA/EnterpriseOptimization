-- MySQL dump 10.13  Distrib 8.0.36, for Linux (x86_64)
--
-- Host: localhost    Database: EnterpriseOptimization
-- ------------------------------------------------------
-- Server version	8.0.36-0ubuntu0.22.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Materials`
--

DROP TABLE IF EXISTS `Materials`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Materials` (
  `id` int NOT NULL,
  `name` char(32) NOT NULL,
  `quantity` float NOT NULL,
  `price` decimal(8,2) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Materials`
--

LOCK TABLES `Materials` WRITE;
/*!40000 ALTER TABLE `Materials` DISABLE KEYS */;
INSERT INTO `Materials` VALUES (1,'Silver 925',90,33.00),(2,'Silver 960',382,48.00),(3,'Silver 999',348,61.00),(4,'Gold 375',256,2436.00),(5,'Gold 585',457,3800.00),(6,'Gold 750',325,4872.00),(7,'Gold 900',72,5847.00),(8,'Gold 999',193,6490.00),(9,'Diamond',1,93217.00),(10,'Ruby',13,78915.00),(11,'Emerald',5,46609.00),(12,'Agate',15,930.00),(13,'Amethyst',3,1468.00),(14,'Amber',17,167.00),(15,'Malachite',9,219.00),(16,'Pomegranate',15,6365.00),(17,'Chrysolite',11,9582.00),(18,'Topaz',20,5871.00);
/*!40000 ALTER TABLE `Materials` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Orders`
--

DROP TABLE IF EXISTS `Orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Orders` (
  `id` int NOT NULL,
  `product_id` int NOT NULL,
  `count` int NOT NULL DEFAULT '1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Orders`
--

LOCK TABLES `Orders` WRITE;
/*!40000 ALTER TABLE `Orders` DISABLE KEYS */;
INSERT INTO `Orders` VALUES (1,3,3),(2,4,1),(3,8,1),(4,6,1),(5,7,3),(6,8,3),(7,19,3),(8,8,1),(9,20,2),(10,5,1),(11,14,1),(12,2,1),(13,13,3),(14,12,3),(15,3,2),(16,10,1),(17,16,2),(18,1,1),(19,5,2),(20,14,2),(21,15,3),(22,3,2),(23,16,2),(24,10,2),(25,16,3),(26,14,2),(27,8,1),(28,17,1),(29,1,2),(30,16,3),(31,9,2),(32,8,1),(33,6,1),(34,13,2),(35,12,2),(36,10,2),(37,20,1),(38,14,3),(39,17,3),(40,10,2),(41,9,1),(42,2,2),(43,15,1),(44,9,2),(45,2,3),(46,1,1),(47,20,2),(48,14,1),(49,3,1),(50,15,1);
/*!40000 ALTER TABLE `Orders` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ProductNames`
--

DROP TABLE IF EXISTS `ProductNames`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ProductNames` (
  `id` int NOT NULL,
  `name` char(64) NOT NULL,
  `price` decimal(10,2) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ProductNames`
--

LOCK TABLES `ProductNames` WRITE;
/*!40000 ALTER TABLE `ProductNames` DISABLE KEYS */;
INSERT INTO `ProductNames` VALUES (1,'Golden ring with pomegranates',0.00),(2,'Silver ring with pomegranates',0.00),(3,'Silver ring with ambers',0.00),(4,'Golden ring with ambers',0.00),(5,'Golden ring with chrysolite',0.00),(6,'Silver ring with chrysolite',0.00),(7,'Golden ring with amethysts',0.00),(8,'Golden ring with malachite',0.00),(9,'Golden ring with ruby',0.00),(10,'Silver ring with amber',0.00),(11,'Silver ring with rubies',0.00),(12,'Silver ring with topaz',0.00),(13,'Golden ring with amethysts',0.00),(14,'Silver ring with a big emerald',0.00),(15,'Silver ring with a big chrysolites',0.00),(16,'Golden ring with 50 diamonds',0.00),(17,'Golden ring with amber',0.00),(18,'Silver ring with amethyst',0.00),(19,'Golden ring with topazes',0.00),(20,'Golden ring with agates',0.00);
/*!40000 ALTER TABLE `ProductNames` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Products`
--

DROP TABLE IF EXISTS `Products`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Products` (
  `id` int NOT NULL,
  `material_id` int NOT NULL,
  `quantity` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Products`
--

LOCK TABLES `Products` WRITE;
/*!40000 ALTER TABLE `Products` DISABLE KEYS */;
INSERT INTO `Products` VALUES (1,6,1.2),(1,16,0.12),(2,3,1.02),(2,16,0.04),(3,3,2.33),(3,14,0.1),(4,6,2.4),(4,14,0.14),(5,5,2.67),(5,17,0.17),(6,2,1.4),(6,17,0.1),(7,8,1.5),(7,13,0.18),(8,5,2.46),(8,15,0.09),(9,5,1.88),(9,10,0.06),(10,3,1.95),(10,14,0.1),(11,2,2),(11,10,0.17),(12,4,2.94),(12,18,0.03),(13,7,2.61),(13,13,0.1),(14,1,2.71),(14,11,0.06),(15,1,1.59),(15,17,0.16),(16,7,1.13),(16,9,0.15),(17,8,2.07),(17,14,0.07),(18,2,2.57),(18,13,0.07),(19,5,2.32),(19,18,0.11),(20,6,1.55),(20,12,0.13);
/*!40000 ALTER TABLE `Products` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-04-30 22:29:59
