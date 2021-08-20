#include <iostream>
#include <string>
#include <regex>

#include "StatManager.hpp"
#include "Stat.hpp"

void StatManager::run(vector<SalaryModel> person){
	bool run = true;

	while(run){
		// read input
		cout << "Enter text in stat: \"total\", \"dept\", \"date\", \"level\", \"age\", \"min\", or \"return\" to return:" << endl;
		string statComd;
		cin >> statComd;

		// create the STAT object
		Stat statObj(person);

		if (statComd == "return"){
			run = false;
		}
		else if (statComd == "total"){
			statObj.total();
		}
		else if (statComd == "dept"){
			statObj.dept();
		}
		else if (statComd == "date"){
			statObj.date();
		}
		else if (statComd == "level"){
			statObj.level();
		}
		else if (statComd == "age"){
			statObj.age();
		}
		else if (statComd == "min"){
			statObj.min();
		}
	}
}

