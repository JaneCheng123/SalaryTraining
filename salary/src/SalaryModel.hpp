#ifndef SALARYMODEL_HPP_
#define SALARYMODEL_HPP_

#include <string>

using namespace std;

class SalaryModel{

private:
	int employeeid;
	string name;
	int age;
	string department;
	string hiredate;
	int salary;
	int level;
	double subsidy;
	double total;


public:
	SalaryModel(int id, string name, int age, string department, string hiredate, int salary, int level);

	int getAge() const;

	void setAge(int age);

	const string& getDepartment() const;

	void setDepartment(const string &department);

	int getEmployeeid() const;

	void setEmployeeid(int employeeid);

	const string& getHiredate() const;

	void setHiredate(const string &hiredate);

	int getLevel() const;

	void setLevel(int level);

	const string& getName() const;

	void setName(const string &name) ;

	int getSalary() const;

	void setSalary(int salary);

	double getSubsidy() const;

	void setSubsidy(double subsidy);

	double getTotal() const;

	void setTotal(double total);

	string getString();
};


#endif /* SALARYMODEL_HPP_ */
