#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <numeric>
#include <map>
#include <bits/stdc++.h>

#include "SalaryModel.hpp"
#include "DataSource.hpp"
#include "trainning/JsonExport.hpp"
#include "trainning/XMLexport.hpp"
#include "trainning/StatManager.hpp"
#include "trainning/SqlManager.hpp"

using namespace std;

int main(){
	vector<SalaryModel> sm;
	bool run = true;

	// read the datasheet.csv file
	DataSource readFile("datasheet.cvs.csv");
	sm = readFile.getModels();

	while (run){
		// get the input
		cout << "Enter your command: \"sql\", \"stat\", \"export\" or \"exit\" to exit:" << endl;
		string comd;
		cin >> comd;
		cin.ignore();

		if (comd == "exit"){
			run = false;
		}
		else if (comd == "sql"){
			SqlManager sqlm;
			sqlm.run(sm);
			sm = sqlm.getModels();
		}
		else if (comd == "stat"){
			StatManager stam;
			stam.run(sm);
		}
		else if (comd == "export"){
			JsonExport jsonExpt(sm);
			XMLexport xmlExpt(sm);
		}
		else{
			cout << "Invalid command, please enter again." << endl;
		}
	}
	return 0;
}


