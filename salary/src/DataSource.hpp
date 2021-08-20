#ifndef SRC_DATASOURCE_HPP_
#define SRC_DATASOURCE_HPP_

#include <iostream>
#include "SalaryModel.hpp"

using namespace std;

class DataSource{
private:
	vector<SalaryModel> models;

public:
    DataSource(string filePath);
    DataSource();
    int employed_length(int y, int m, int d);
    double subsidy_salary(string date, int level);
	const vector<SalaryModel>& getModels() const;
};


#endif /* SRC_DATASOURCE_HPP_ */
