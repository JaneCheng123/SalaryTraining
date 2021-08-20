#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../SalaryModel.hpp"
#include "../tinyxml2.h"
#include "XMLexport.hpp"

using namespace tinyxml2;
using namespace std;

XMLexport::XMLexport(vector<SalaryModel> model){
	this->model = model;

	XMLDocument doc;
	doc.LinkEndChild(doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\""));

	auto root = doc.NewElement("employees");

	for (SalaryModel sm: model){
		auto personElement = doc.NewElement("employee");

		// id
		auto idElement = doc.NewElement("employee ID");
		idElement->SetText(sm.getEmployeeid());
		// name
		auto nameElement = doc.NewElement("name");
		const char* n = sm.getName().c_str();
		nameElement ->SetText(n);
		// age
		auto ageElement = doc.NewElement("age");
		ageElement ->SetText(sm.getAge());
		// department
		auto deptElement = doc.NewElement("department");
		const char* d = sm.getDepartment().c_str();
		deptElement ->SetText(d);
		// hiredate
		auto dateElement = doc.NewElement("hireDate");
		const char* h = sm.getHiredate().c_str();
		dateElement ->SetText(h);
		// salary
		auto salaryElement = doc.NewElement("salary");
		salaryElement->SetText(sm.getSalary());
		// level
		auto levelElement = doc.NewElement("level");
		levelElement->SetText(sm.getLevel());
		// subsidy
		auto subsidyElement = doc.NewElement("subsidy");
		subsidyElement->SetText(sm.getSubsidy());
		// total
		auto totalElement = doc.NewElement("total");
		totalElement->SetText(sm.getTotal());

		// link below <employee> element
		personElement ->LinkEndChild(idElement);
		personElement ->LinkEndChild(nameElement);
		personElement ->LinkEndChild(ageElement);
		personElement ->LinkEndChild(deptElement);
		personElement ->LinkEndChild(dateElement);
		personElement ->LinkEndChild(salaryElement);
		personElement ->LinkEndChild(levelElement);
		personElement ->LinkEndChild(subsidyElement);
		personElement ->LinkEndChild(totalElement);

		// link below <employees> element
		root ->LinkEndChild(personElement);
	}
	doc.LinkEndChild(root);


	doc.SaveFile("output/datasheet.xml");

}


