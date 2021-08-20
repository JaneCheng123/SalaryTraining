#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <numeric>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

#include "SqlManager.hpp"
#include "Sql.hpp"

using namespace std;
using namespace boost::algorithm;

void SqlManager::run(vector<SalaryModel> person){
	this->models = person;
	bool run = true;

	while (run){
		//read input and set all to lower case
		cout << "Enter command in sql or \"return\" to return:" << endl;
		string sqlComd;
		getline(cin, sqlComd);
		to_lower(sqlComd);

		// check whether the input contains 'where' , 'oder by', 'set', and 'from'
		bool validWhere = sqlComd.find("where") != string::npos;
		bool validSet = sqlComd.find("set") != string::npos;
		bool validFrom = sqlComd.find("from") != string::npos;
		bool validOb = sqlComd.find("order by") != string::npos;

		// remove the whitespace
		sqlComd = regex_replace(sqlComd, regex("\\s+"), "");

		// create the SQL object
		Sql sqlObj(models);

		if (sqlComd.substr(0, 6) == "select" && validFrom){
			// only has 'where' command
			if (validWhere && !validOb){
				// get the index of 'select' and 'from' and put the string that between them into a new string
				// put the string that after 'where' into a new string
				int spos = sqlComd.find("from");
				int wpos = sqlComd.find("where");
				string getSel = sqlComd.substr(6, (spos - 6));
				string getCond = sqlComd.substr(wpos+5);

				// handle the select
				vector<string> selCom;
				split(selCom, getSel, is_any_of(","));

				// handle the condition
				vector<string> condCom;
				split(condCom, getCond, is_any_of("="));

				if ((condCom[0] == "department") | (condCom[0] == "name")){
					condCom[1][0] = toupper(condCom[1][0]);
				}

				// first check is the condition is valid or not
				if (find(comps.begin(), comps.end(), condCom[0]) != comps.end()){
					// second check is the select column is valid or not
					for (string col: selCom){
						if (find(comps.begin(), comps.end(), col) == comps.end()){
							cout << "Invalid select column name. please enter again." << endl;
						}
					}

					sqlObj.select(condCom[0], condCom[1], selCom);
				}
				else{
					cout << "Invalid condition. please enter again" << endl;
				}

			}
			// only has 'order by' command
			else if (validOb && !validWhere){
				// get the index of 'select' and 'from' and put the string that between them into a new string
				// put the string that after 'where' into a new string
				int fpos = sqlComd.find("from");
				int opos = sqlComd.find("orderby");
				string getSel = sqlComd.substr(6, (fpos - 6));
				string getCond = sqlComd.substr(opos+7);

				// handle the select
				vector<string> selCom;
				split(selCom, getSel, is_any_of(","));

				// first check is the condition is valid or not
				if (find(comps.begin(), comps.end(), getCond) != comps.end()){
					// second check is the select column is valid or not
					for (string col: selCom){
						if (find(comps.begin(), comps.end(), col) == comps.end()){
							cout << "Invalid select column name. please enter again." << endl;
						}
					}

					sqlObj.select("orderby", getCond, selCom);
				}
				else{
					cout << "Invalid condition. please enter again" << endl;
				}
			}
			else{
				cout << "Invalid command. please enter again." << endl;
			}
		}
		else if (sqlComd.substr(0, 6) == "insert" && sqlComd.substr(6, 4) == "into"){
			/**
			 * hiredate scenarios
			 * insert into tb_salary (1,1,1,1,1,1,1) values(123, haha, 32, testing, 2010-1-1, 1234, 3)
			 * insert into tb_salary (1,1,1,1,1,1,1) values(123, haha, 32, testing, 2010 1 1, 1234, 3)
			 * insert into tb_salary(employeeid,name,age,department,hiredate,salary,level)values(123, haha, 32, testing, 2010-1-1, 1234, 3)
			 */
			int fpos = sqlComd.find("(");
			int bpos = sqlComd.find(")");

			string types = sqlComd.substr(fpos+1, (bpos - fpos - 1 ));
			vector<string> getType;
			split(getType, types, is_any_of(","));

			if (getType[0] == "employeeid" &&
					getType[1] == "name" &&
					getType[2] == "age" &&
					getType[3] == "department" &&
					getType[4] == "hiredate" &&
					getType[5] == "salary" &&
					getType[6] == "level"){
				sqlComd = regex_replace(sqlComd, regex("[()]"), "");
				int pos = sqlComd.find("values");
				string getComp = sqlComd.substr(pos+6);

				vector<string> getInfo;
				split(getInfo, getComp, is_any_of(","));

				// capitalize the first letter
				// handle bad input for name and department
				getInfo[1][0] = toupper(getInfo[1][0]);
				getInfo[3][0] = toupper(getInfo[3][0]);

				// handle bad input for hiredate
				vector<string> getDate;
				split(getDate, getInfo[4], is_any_of("-"));

				if (getDate.size() == 3 && isvalid(2021, 1940, stoi(getDate[0])) &&
						isvalid(12, 01, stoi(getDate[1])) && isvalid(31, 01, stoi(getDate[2]))){
					sqlObj.insert(stoi(getInfo[0]), getInfo[1], stoi(getInfo[2]), getInfo[3], getInfo[4], stoi(getInfo[5]), stoi(getInfo[6]));
					models = sqlObj.getPerson();
				}
				else{
					cout << "Invalid hiredate form or dates number, please enter again." << endl;
				}
			}
			else{
				cout << "Invalid column name, please enter again." << endl;
			}
		}
		else if (sqlComd.substr(0, 6) == "update" && validSet && validWhere){
			// get the index of 'set' and 'where' and put the string that between them into a new string
			// put the string that after 'where' into a new string
			int spos = sqlComd.find("set");
			int wpos = sqlComd.find("where");
			string getSet = sqlComd.substr(spos+3, (wpos - spos - 3));
			string getCond = sqlComd.substr(wpos+5);

			// handle the set
			vector<string> setCom;
			getSet = regex_replace(getSet, regex("[=]"), ",");
			split(setCom, getSet, is_any_of(","));

			// handle the condition
			vector<string> condCom;
			split(condCom, getCond, is_any_of("="));

			if ((condCom[0] == "department") | (condCom[0] == "name")){
				condCom[1][0] = toupper(condCom[1][0]);
			}

			for (unsigned int i = 0; i< setCom.size(); i+=2){
				if (find(comps.begin(), comps.end(), setCom[i]) != comps.end()){
					sqlObj.update(condCom[0], condCom[1], setCom[i], setCom[i+1]);
					models = sqlObj.getPerson();
				}
				else{
					cout << "Invalid set column name, please enter again." << endl;
					break;
				}
			}
		}
		else if (sqlComd.substr(0, 6) == "delete" && sqlComd.substr(6, 4) == "from" && validWhere){
			// get the index of 'where' and put the string that after the 'where' into a new string
			int pos = sqlComd.find("where");
			string getComp = sqlComd.substr(pos+5);

			// split the string by '='
			vector<string> getInfo;
			split(getInfo, getComp, is_any_of("="));

			if ((getInfo[0] == "department") | (getInfo[0] == "name")){
				getInfo[1][0] = toupper(getInfo[1][0]);
			}

			if (find(comps.begin(), comps.end(), getInfo[0]) != comps.end()){
				sqlObj.deleted(getInfo[0], getInfo[1]);
				models = sqlObj.getPerson();
			}
			else{
				cout << "Invalid variable name, please enter again." << endl;
			}
		}
		else if (sqlComd.substr(0, 6) == "return"){
			run = false;
		}
		else{
			cout << "Invalid command, please enter again." << endl;
		}
	}
}

// getter
const vector<SalaryModel>& SqlManager::getModels() const {
	return models;
}

// helper method that check whether the dates are in the valid range
bool SqlManager::isvalid(int high, int low, int number){
	return low <= number && number <= high;
}

