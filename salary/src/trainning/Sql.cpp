#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <numeric>
#include <map>
#include <iterator>
#include <bits/stdc++.h>
#include "../SalaryModel.hpp"
#include "../DataSource.hpp"
#include "Sql.hpp"

using namespace std;

Sql::Sql(vector<SalaryModel> model){
	this->person = model;
}

// getter
const vector<SalaryModel>& Sql::getPerson() const {
	return person;
}

void Sql::select(string type, string value, vector<string> stype){
	vector<SalaryModel> eligible;

	if(type != "orderby"){
		for (unsigned i = 0; i < person.size(); i++){
			if (type == "employeeid"){
				if (person.at(i).getEmployeeid() == stoi(value)){
					eligible.push_back(person.at(i));
				}
				else{
					countP += 1;
				}
			}
			else if (type == "name"){
				if (person.at(i).getName() == value){
					eligible.push_back(person.at(i));
				}
				else{
					countP += 1;
				}
			}
			else if (type == "age"){
				if (person.at(i).getAge() == stoi(value)){
					eligible.push_back(person.at(i));
				}
				else{
					countP += 1;
				}
			}
			else if (type == "department"){
				if (person.at(i).getDepartment() == value){
					eligible.push_back(person.at(i));
				}
				else{
					countP += 1;
				}
			}
			else if (type == "hiredate"){
				if (person.at(i).getHiredate() == value){
					eligible.push_back(person.at(i));
				}
				else{
					countP += 1;
				}
			}
			else if (type == "salary"){
				if (person.at(i).getSalary() == stoi(value)){
					eligible.push_back(person.at(i));
				}
				else{
					countP += 1;
				}
			}
			else if (type == "level"){
				if (person.at(i).getLevel() == stoi(value)){
					eligible.push_back(person.at(i));
				}
				else{
					countP += 1;
				}
			}
		}

		if (countP == person.size()){
			cout << "There is no such employee in the table" << endl;
		}
		else{
			selectInfo(eligible, stype, type);
		}
	}
	else{
		if (value == "employeeid"){
			sort(person.begin(), person.end(), idOrder);
		}
		else if(value == "name"){
			sort(person.begin(), person.end(), nameOrder);
		}
		else if(value == "age"){
			sort(person.begin(), person.end(), ageOrder);
		}
		else if(value == "department"){
			sort(person.begin(), person.end(), deptOrder);
		}
		else if(value == "hiredate"){
			sort(person.begin(), person.end(), dateOrder);
		}
		else if(value == "salary"){
			sort(person.begin(), person.end(), salaryOrder);
		}
		else if(value == "level"){
			sort(person.begin(), person.end(), levelOrder);
		}

		selectInfo(person, stype, value);
	}

}

void Sql::insert(int id, string name, int age, string department, string hiredate, int salary, int level){
	unsigned int sizeBf = person.size();
	bool valid = true;

	for (SalaryModel m: person){
		if ((m.getEmployeeid() == id) | (m.getName() == name)){
			valid = false;
			cout << "already in the table, please enter again" << endl;
			break;
		}
	}

	if (valid){
		SalaryModel sm(id, name, age, department, hiredate, salary, level);


		double subsidy = calculate.subsidy_salary(hiredate, level);
		double total = subsidy + salary;

		sm.setSubsidy(subsidy);
		sm.setTotal(total);

		person.push_back(sm);
	}

	if (person.size() > sizeBf){
		cout << "successful insert" << endl;
	}
	else{
		cout << "unsuccessful insert" << endl;
	}
}

void Sql::update(string type, string value, string utype, string uvalue){
	bool updated = false;

	if (type == "employeeid"){
		for (SalaryModel m: person){
			if (m.getEmployeeid() == stoi(value)){
				updateInfo(m, utype, uvalue);
				updated = true;
				break;
			}
		}
	}
	else if (type == "age"){
		for (SalaryModel m: person){
			if (m.getAge() == stoi(value)){
				updateInfo(m, utype, uvalue);
				updated = true;
			}
		}
	}
	else if (type == "name"){
		for (SalaryModel m: person){
			if (m.getName() == value){
				updateInfo(m, utype, uvalue);
				updated = true;
				break;
			}
		}
	}
	else if (type == "department"){
		for (SalaryModel m: person){
			if (m.getDepartment() == value){
				updateInfo(m, utype, uvalue);
				updated = true;
			}
		}
	}
	else if (type == "level"){
		for (SalaryModel m: person){
			if (m.getLevel() == stoi(value)){
				updateInfo(m, utype, uvalue);
				updated = true;
			}
		}
	}

	if (updated){
		cout << "successful update" << endl;
	}
	else{
		cout << "unsuccessful update. The condition info you entered is not in the table" << endl;
	}
}

void Sql::deleted(string type, string value){
	unsigned int sizeBf = person.size();

	if (type == "employeeid"){
		for (unsigned int i = 0; i < person.size(); i++){
			if (person.at(i).getEmployeeid() == stoi(value)){
				person.erase(person.begin() + i);
				break;
			}
		}
	}
	else if (type == "name"){
		for (unsigned int i = 0; i < person.size(); i++){
			if (person.at(i).getName() == value){
				person.erase(person.begin() + i);
				break;
			}
		}
	}
	else if (type == "age"){
		for (unsigned int i = 0; i < person.size(); ++i){
			if (person.at(i).getAge() == stoi(value)){
				person.erase(person.begin() + i);
				i--;
			}
		}
	}
	else if (type == "department"){
		for (unsigned int i = 0; i < person.size(); ++i){
			if (person.at(i).getDepartment() == value){
				person.erase(person.begin() + i);
				i--;
			}
		}
	}
	else if (type == "hiredate"){
		for (unsigned int i = 0; i < person.size(); ++i){
			if (person.at(i).getHiredate() == value){
				person.erase(person.begin() + i);
				i--;
			}
		}
	}
	else if (type == "level"){
		for (unsigned int i = 0; i < person.size(); ++i){
			if (person.at(i).getLevel() == stoi(value)){
				person.erase(person.begin() + i);
				i--;
			}
		}
	}
	else if (type == "salary"){
		for (unsigned int i = 0; i < person.size(); ++i){
			if (person.at(i).getSalary() == stoi(value)){
				person.erase(person.begin() + i);
				i--;
			}
		}
	}

	if (person.size() < sizeBf){
		cout << "successful delete" << endl;
	}
	else{
		cout << "unsuccessful delete" << endl;
	}
}

// helper method that help 'update' command to update
void Sql::updateInfo(SalaryModel sm, string utype, string uvalue){
	// update them
	if (utype == "age"){
		sm.setAge(stoi(uvalue));
	}
	else if (utype == "department"){
		sm.setDepartment(uvalue);
	}
	else if (utype == "hiredate"){
		sm.setHiredate(uvalue);

		double subsidy = calculate.subsidy_salary(uvalue, sm.getLevel());
		double total = subsidy + sm.getSalary();

		sm.setSubsidy(subsidy);
		sm.setTotal(total);
	}
	else if (utype == "salary"){
		sm.setSalary(stoi(uvalue));

		double total = sm.getSubsidy() + stoi(uvalue);
		sm.setTotal(total);
	}
	else if (utype == "level"){
		sm.setLevel(stoi(uvalue));

		double subsidy = calculate.subsidy_salary(sm.getHiredate(), stoi(uvalue));
		double total = subsidy + sm.getSalary();

		sm.setSubsidy(subsidy);
		sm.setTotal(total);
	}
}

// helper method that help 'select' command to print out the info
void Sql::selectInfo(vector<SalaryModel> sm, vector<string> stype, string ctype){
	if (stype[0] == "*"){
		printf("%-15s%-15s%-10s%-20s%-15s%-10s%-10s%-15s%-15s\n", "Empolyeeid", "Name", "Age",
				"Department", "Hiredate", "Salary", "Level", "Subsidy", "Total");
		for (SalaryModel m : sm){
			printf("%-15i%-15s%-10i%-20s%-15s%-10i%-10i%-15.2f%-15.2f\n", m.getEmployeeid(), m.getName().c_str(),
					m.getAge(), m.getDepartment().c_str(), m.getHiredate().c_str(), m.getSalary(),
					m.getLevel(), m.getSubsidy(), m.getTotal());
		}
	}
	else{
		for (string s: stype){
			if (s == "name"){
				printf("%-20s", s.c_str());
			}
			else if (s == "department"){
				printf("%-20s", s.c_str());
			}
			else if (s == "age"){
				printf("%-20s", s.c_str());
			}
			else if (s == "hiredate"){
				printf("%-20s", s.c_str());
			}
			else if (s == "salary"){
				printf("%-20s", s.c_str());
			}
			else if (s == "level"){
				printf("%-20s", s.c_str());
			}
			else if(s == "employeeid"){
				printf("%-20s", s.c_str());
			}
		}
		printf("%-20s\n", ctype.c_str());

		for(SalaryModel m :sm){
			for(string s: stype){
				if (s == "employeeid"){
					printf("%-20s", to_string(m.getEmployeeid()).c_str());
				}
				else if (s == "name"){
					printf("%-20s", m.getName().c_str());
				}
				else if (s == "department"){
					printf("%-20s", m.getDepartment().c_str());
				}
				else if (s == "age"){
					printf("%-20s", to_string(m.getAge()).c_str());
				}
				else if (s == "hiredate"){
					printf("%-20s", m.getHiredate().c_str());
				}
				else if (s == "salary"){
					printf("%-20s", to_string(m.getSalary()).c_str());
				}
				else if (s == "level"){
					printf("%-20s", to_string(m.getLevel()).c_str());
				}
			}

			if (ctype == "employeeid"){
				printf("%-20s", to_string(m.getEmployeeid()).c_str());
			}
			else if (ctype == "name"){
				printf("%-20s", m.getName().c_str());
			}
			else if (ctype == "department"){
				printf("%-20s", m.getDepartment().c_str());
			}
			else if (ctype == "age"){
				printf("%-20s", to_string(m.getAge()).c_str());
			}
			else if (ctype == "hiredate"){
				printf("%-20s", m.getHiredate().c_str());
			}
			else if (ctype == "salary"){
				printf("%-20s", to_string(m.getSalary()).c_str());
			}
			else if (ctype == "level"){
				printf("%-20s", to_string(m.getLevel()).c_str());
			}
			printf("\n");
		}
	}
}

// block of helper methods that help "order by" command to sort
bool Sql::idOrder(SalaryModel p1, SalaryModel p2){
	return (p1.getEmployeeid() < p2.getEmployeeid());
}
bool Sql::nameOrder(SalaryModel p1, SalaryModel p2){
	return (p1.getName() < p2.getName());
}
bool Sql::ageOrder(SalaryModel p1, SalaryModel p2){
	return (p1.getAge() < p2.getAge());
}
bool Sql::deptOrder(SalaryModel p1, SalaryModel p2){
	return (p1.getDepartment() < p2.getDepartment());
}
bool Sql::dateOrder(SalaryModel p1, SalaryModel p2){
	return (p1.getHiredate() < p2.getHiredate());
}
bool Sql::salaryOrder(SalaryModel p1, SalaryModel p2){
	return (p1.getSalary() < p2.getSalary());
}
bool Sql::levelOrder(SalaryModel p1, SalaryModel p2){
	return (p1.getLevel() < p2.getLevel());
}

