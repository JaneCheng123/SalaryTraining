#include <iostream>
#include "../SalaryModel.hpp"
using namespace std;


SalaryModel::SalaryModel(int id, string name, int age, string department, string hiredate, int salary, int level){
	this->employeeid = id;
	this->name = name;
	this->age = age;
	this->department = department;
	this->hiredate = hiredate;
	this->salary = salary;
	this->level = level;
}

int SalaryModel::getAge() const {
	return age;
}

void SalaryModel::setAge(int age) {
	this->age = age;
}

const string& SalaryModel::getDepartment() const {
	return department;
}

void SalaryModel::setDepartment(const string &department) {
	this->department = department;
}

int SalaryModel::getEmployeeid() const {
	return employeeid;
}

void SalaryModel::setEmployeeid(int employeeid) {
	this->employeeid = employeeid;
}

const string& SalaryModel::getHiredate() const {
	return hiredate;
}

void SalaryModel::setHiredate(const string &hiredate) {
	this->hiredate = hiredate;
}

int SalaryModel::getLevel() const {
	return level;
}

void SalaryModel::setLevel(int level) {
	this->level = level;
}

const string& SalaryModel::getName() const {
	return name;
}

void SalaryModel::setName(const string &name) {
	this->name = name;
}

int SalaryModel::getSalary() const {
	return salary;
}

void SalaryModel::setSalary(int salary) {
	this->salary = salary;
}

double SalaryModel::getSubsidy() const {
	return subsidy;
}

void SalaryModel::setSubsidy(double subsidy) {
	this->subsidy = subsidy;
}

double SalaryModel::getTotal() const {
	return total;
}

void SalaryModel::setTotal(double total) {
	this->total = total;
}

string SalaryModel::getString(){
	return (to_string(this->employeeid) + ", " + this->name + ", " + to_string(this->age) + ", " + this->department + ", " + this->hiredate + ", " + to_string(this->salary) + ", " + to_string(this->level) + ", " + to_string(subsidy) + ", " + to_string(total));
}



