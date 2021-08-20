#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../SalaryModel.hpp"
#include "nlohmann/json.hpp"
#include "JsonExport.hpp"


using namespace std;
using json = nlohmann::json;

JsonExport::JsonExport(vector<SalaryModel> model){

	for (SalaryModel sm: model){
		json person = {
				{"employee ID: ", sm.getEmployeeid()},
				{"name: ", sm.getName()},
				{"age: ", sm.getAge()},
				{"department: ", sm.getDepartment()},
				{"hiredate: ", sm.getHiredate()},
				{"salary: ", sm.getSalary()},
				{"level: ", sm.getLevel()},
				{"subsidy: ", sm.getSubsidy()},
				{"total: ", sm.getTotal()}
		};
		jsonPerson.push_back(person);
	}

	// write in file
	ofstream f("output/datasheet.json");
	for(unsigned i = 0; i < jsonPerson.size(); i++){
		f << jsonPerson.at(i) << endl;
	}
}






