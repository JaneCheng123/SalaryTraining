#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <numeric>
#include <boost/algorithm/string.hpp>
#include "../DataSource.hpp"

using namespace std;
using namespace boost::algorithm;

// default constructor
DataSource::DataSource(){}

DataSource::DataSource(string filePath){
	// read file
	ifstream datasheet;
	datasheet.open(filePath);

	// ignore the header
	string header;
	getline(datasheet, header);

	while(datasheet.good()){
		string line;
		getline(datasheet, line, '\n');

		vector<string> comp;
		istringstream ss{line};
		string token;

		while(getline(ss, token, ',')){
			if (!token.empty()){
				comp.push_back(token);
			}
		}

		SalaryModel eachModel(stoi(comp[0]), comp[1], stoi(comp[2]), comp[3], comp[4], stoi(comp[5]), stoi(comp[6]));
		double subsidy = subsidy_salary(comp[4], stoi(comp[6]));
		double total = subsidy + stoi(comp[5]);
		eachModel.setSubsidy(subsidy);
		eachModel.setTotal(total);

		models.push_back(eachModel);
	}
	datasheet.close();
}

// method to calculate how long does the person got employed
int DataSource::employed_length(int y, int m, int d){
	if (m < 3){
		y--, m += 12;
	}
	return 365*y + y/4 - y/100 + (153*m -457)/5 + d -306;
}

// method to calculate the amount of subsidy
double DataSource::subsidy_salary(string date, int level){
	vector<string> getDate;
	split(getDate, date, is_any_of("-"));

	int year = stoi(getDate[0]);
	int month = stoi(getDate[1]);
	int day = stoi(getDate[2]);

	int hire_length = (employed_length(2021, 6, 1) - employed_length(year, month, day)) / 365;

	return hire_length * 100 + level* 100;
}

// getter
const vector<SalaryModel>& DataSource::getModels() const {
	return models;
}



