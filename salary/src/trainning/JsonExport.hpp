#ifndef SRC_JSONEXPORT_HPP_
#define SRC_JSONEXPORT_HPP_

#include <string>
#include <vector>
#include "../SalaryModel.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class JsonExport{
private:
	vector<SalaryModel> model;
	vector<json> jsonPerson;

public:
	JsonExport(vector<SalaryModel> model);
};


#endif /* SRC_JSONEXPORT_HPP_ */
