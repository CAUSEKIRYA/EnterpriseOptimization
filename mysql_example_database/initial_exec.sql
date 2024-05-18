-- Create database
create database EnterpriseOptimization;

-- Create user 'Manager' with all privileges for 'EnterpriseOptimization' database
create user 'Manager'@'localhost' identified by 'Pa$$W0rD1';
grant all privileges on EnterpriseOptimization.* to 'Manager'@'localhost';
