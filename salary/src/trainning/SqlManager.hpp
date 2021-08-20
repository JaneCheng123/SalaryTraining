#ifndef SRC_TRAINNING_SQLMANAGER_HPP_
#define SRC_TRAINNING_SQLMANAGER_HPP_

#include <iostream>
#include <vector>
#include "../SalaryModel.hpp"

using namespace std;

class SqlManager{
private:
	vector<SalaryModel> models;
	vector<string> comps = {"employeeid", "name", "age", "department", "hiredate", "level", "salary", "*"};
	bool isvalid(int high, int low, int number);

public:
	void run(vector<SalaryModel> person);
	const vector<SalaryModel>& getModels() const;

};


#endif /* SRC_TRAINNING_SQLMANAGER_HPP_ */
