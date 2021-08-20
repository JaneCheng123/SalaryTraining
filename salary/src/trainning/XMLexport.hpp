#ifndef SRC_XMLEXPORT_HPP_
#define SRC_XMLEXPORT_HPP_

#include <string>
#include <vector>
#include "../SalaryModel.hpp"
#include "../tinyxml2.h"

using namespace std;

class XMLexport{
private:
	vector<SalaryModel> model;

public:
	XMLexport(vector<SalaryModel> model);
};


#endif /* SRC_XMLEXPORT_HPP_ */
