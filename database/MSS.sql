-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Oct 06, 2021 at 11:33 AM
-- Server version: 10.4.21-MariaDB
-- PHP Version: 8.0.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `MSS`
--
CREATE DATABASE IF NOT EXISTS `MSS` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `MSS`;

-- --------------------------------------------------------

--
-- Table structure for table `Module`
--

CREATE TABLE `Module` (
  `Modul_ID` int(10) UNSIGNED NOT NULL,
  `PL_ID` int(10) UNSIGNED NOT NULL,
  `Typ_ID` int(10) UNSIGNED NOT NULL,
  `Slot` tinyint(3) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `Platform`
--

CREATE TABLE `Platform` (
  `PL_ID` int(11) UNSIGNED NOT NULL,
  `Name` text DEFAULT NULL,
  `AbfrageZeit` time NOT NULL,
  `AbfrageInterval` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `Typ`
--

CREATE TABLE `Typ` (
  `Typ_ID` int(10) UNSIGNED NOT NULL,
  `Bezeichnung` text DEFAULT NULL,
  `Decoder` text NOT NULL,
  `Farbe` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `Wert`
--

CREATE TABLE `Wert` (
  `Wert_ID` int(10) UNSIGNED NOT NULL,
  `Modul_ID` int(10) UNSIGNED NOT NULL,
  `Zeit` datetime NOT NULL,
  `Wert` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `Module`
--
ALTER TABLE `Module`
  ADD PRIMARY KEY (`Modul_ID`);

--
-- Indexes for table `Platform`
--
ALTER TABLE `Platform`
  ADD PRIMARY KEY (`PL_ID`);

--
-- Indexes for table `Typ`
--
ALTER TABLE `Typ`
  ADD PRIMARY KEY (`Typ_ID`);

--
-- Indexes for table `Wert`
--
ALTER TABLE `Wert`
  ADD PRIMARY KEY (`Wert_ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `Module`
--
ALTER TABLE `Module`
  MODIFY `Modul_ID` int(10) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `Typ`
--
ALTER TABLE `Typ`
  MODIFY `Typ_ID` int(10) UNSIGNED NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `Wert`
--
ALTER TABLE `Wert`
  MODIFY `Wert_ID` int(10) UNSIGNED NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
