#ifndef SRC_STAT_HPP_
#define SRC_STAT_HPP_

#include <string>

using namespace std;

class Stat{
private:
	vector<SalaryModel> models;
	unsigned int counter = 0;

public:
    Stat(vector<SalaryModel> model);

    void total();
    void dept();
    void date();
    void level();
	void age();
	void min();
};



#endif /* SRC_STAT_HPP_ */
