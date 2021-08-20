#ifndef SRC_SQL_HPP_
#define SRC_SQL_HPP_
#include <string>
#include <vector>
#include "../SalaryModel.hpp"
#include "../DataSource.hpp"
#include <iostream>

using namespace std;

class Sql{
private:
	vector<SalaryModel> person;
	DataSource calculate;
	unsigned int countP = 0;
	void updateInfo(SalaryModel sm, string utype, string uvalue);
	void selectInfo(vector<SalaryModel> sm, vector<string> stype, string ctype);
	bool static idOrder(SalaryModel p1, SalaryModel p2);
	bool static nameOrder(SalaryModel p1, SalaryModel p2);
	bool static ageOrder(SalaryModel p1, SalaryModel p2);
	bool static deptOrder(SalaryModel p1, SalaryModel p2);
	bool static dateOrder(SalaryModel p1, SalaryModel p2);
	bool static salaryOrder(SalaryModel p1, SalaryModel p2);
	bool static levelOrder(SalaryModel p1, SalaryModel p2);


public:
    Sql(vector<SalaryModel> model);

    void select(string type, string value, vector<string>);
    void insert(int id, string name, int age, string department, string hiredate, int salary, int level);
    void update(string type, string value, string utype, string uvalue);
    void deleted(string type, string value);
	const vector<SalaryModel>& getPerson() const;
};



#endif /* SRC_SQL_HPP_ */
