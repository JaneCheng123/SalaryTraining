#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <numeric>
#include <map>
#include <bits/stdc++.h>
#include "../SalaryModel.hpp"
#include "Stat.hpp"

using namespace std;

Stat::Stat(vector<SalaryModel> model){
	this->models = model;
}

// total commend
void Stat::total(){
	double totalSalary;
	for (unsigned i = 0; i < models.size(); i++){
		totalSalary += models.at(i).getTotal();
	}

	// print out echarts
	ofstream f;
	f.open("output/total.html");

	f <<("<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n");
	f <<("<title>TotalSalary</title>\n");
	f <<("<script src=\"../echarts.min.js\"></script>\n</head>\n");
	f <<("<body>\n<div id=\"main\" style=\"width: 1800px;height:800px;\"></div>\n");
	f <<("<script type=\"text/javascript\">\n");
	f <<("var myChart = echarts.init(document.getElementById('main'));\n");
	f <<("var option = {\n\t");
	f <<("tooltip:{\n\t\tformatter: '{a} <br/>{b} : {c}%'\n\t},\n\t");
	f <<("series: [{\n\t\tname: 'Pressure',\n\t\ttype: 'gauge',\n\t\tdetail: {\n\t\t\t");
	f <<("formatter: '{value}'\n\t\t},\n\t\t");
	f <<("data: [{\n\t\t\t");
    f <<("value: ") << to_string(totalSalary) << (",\n\t\t\t");
	f <<("name: 'TotalSalary'\n\t\t}]\n\t}]\n};\n");
	f <<("myChart.setOption(option);\n");
	f <<("</script></body></html>");

	f.close();
}

// dept commend
void Stat::dept(){
	map<string, double> deptSalary;

	for (SalaryModel sm: models){
		if(deptSalary.find(sm.getDepartment()) != deptSalary.end()){
			deptSalary[sm.getDepartment()] += sm.getTotal();
		}
		else{
			deptSalary[sm.getDepartment()] = sm.getTotal();
		}
	}


	// print out echarts
	ofstream f;
	f.open("output/dept.html");

	f <<("<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n");
	f <<("<title>DepartmentSalary</title>\n");
	f <<("<script src=\"../echarts.min.js\"></script>\n</head>\n");
	f <<("<body>\n<div id=\"main\" style=\"width: 1800px;height:800px;\"></div>\n");
	f <<("<script type=\"text/javascript\">\n");
	f <<("var myChart = echarts.init(document.getElementById('main'));\n");
	f <<("var option = {\n\t");
	f <<("tooltip:{},\n\t");
	f <<("xAxis: {\n\t\tdata:[");
	for(auto const &pair: deptSalary) {
		if (counter == deptSalary.size() - 1){
			f << ("'" + pair.first + "'");
			counter = 0;
		}
		else{
			f << ("'" + pair.first + "',");
			counter += 1;
		}
	}
	f <<("]\n\t},\n\tyAxis:{},\n");
	f <<("\tseries:[{\n\t\tname:'sale',\n\t\ttype:'bar',\n\t\tdata:[");
	for(auto &pair: deptSalary) {
		if (counter == deptSalary.size() - 1){
			f <<(to_string(pair.second));
			counter = 0;
		}
		else{
			f <<(to_string(pair.second)) << ",";
			counter += 1;
		}
	}
	f <<("]\n\t}]\n}\n");
	f <<("myChart.setOption(option);\n");
	f <<("</script></body></html>");
	f.close();
}

// date commend
void Stat::date(){
	map<string, int> hiredateNum;

	for (SalaryModel sm: models){
		string year = sm.getHiredate().substr(0, 4);

		if(hiredateNum.find(year) != hiredateNum.end()){
			hiredateNum[year] += 1;
		}
		else{
			hiredateNum[year] = 1;
		}
	}

	// print out echarts
	ofstream f;
	f.open("output/date.html");

	f <<("<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n");
	f <<("<title>DateSalary</title>\n");
	f <<("<script src=\"../echarts.min.js\"></script>\n</head>\n");
	f <<("<body>\n<div id=\"main\" style=\"width: 1800px;height:800px;\"></div>\n");
	f <<("<script type=\"text/javascript\">\n");
	f <<("var myChart = echarts.init(document.getElementById('main'));\n");
	f <<("var option = {\n\t");
	f <<("tooltip:{},\n\t");
	f <<("xAxis: {\n\t\tdata:[");
	for(auto &pair: hiredateNum){
		if (counter == hiredateNum.size() - 1){
			f <<("'" + pair.first + "'");
			counter = 0;
		}
		else{
			f <<("'" + pair.first + "',");
			counter += 1;
		}
	}
	f <<("]\n\t},\n\tyAxis:{},\n");
	f <<("\tseries:[{\n\t\tname:'sale',\n\t\ttype:'bar',\n\t\tdata:[");
	for(auto &pair: hiredateNum) {
		if (counter == hiredateNum.size() - 1){
			f <<(to_string(pair.second));
			counter = 0;
		}
		else{
			f <<(to_string(pair.second) + ",");
			counter += 1;
		}
	}
	f <<("]\n\t}]\n}\n");
	f <<("myChart.setOption(option);\n");
	f <<("</script></body></html>");
	f.close();
}

// level commend
void Stat::level(){
	map<int, double> levelSalary;
	map<int, int> levelNum;
	map<int, double> levelAvg;

	for (SalaryModel sm: models){
		if(levelSalary.find(sm.getLevel()) != levelSalary.end()){
			levelSalary[sm.getLevel()] += sm.getTotal();
			levelNum[sm.getLevel()] += 1;
		}
		else{
			levelSalary[sm.getLevel()] = sm.getTotal();
			levelNum[sm.getLevel()] = 1;
		}
	}

	for (auto &pair: levelSalary){
		levelAvg[pair.first] = pair.second;
	}

	for (auto &pair: levelNum){
		levelAvg[pair.first] = levelAvg[pair.first]/pair.second;
	}


	// print out echarts
	ofstream f;
	f.open("output/level.html");

	f <<("<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n");
	f <<("<title>LevelSalary</title>\n");
	f <<("<script src=\"../echarts.min.js\"></script>\n</head>\n");
	f <<("<body>\n<div id=\"main\" style=\"width: 1800px;height:800px;\"></div>\n");
	f <<("<script type=\"text/javascript\">\n");
	f <<("var myChart = echarts.init(document.getElementById('main'));\n");
	f <<("var option = {\n\t");
	f <<("tooltip:{},\n\t");
	f <<("xAxis: {\n\t\tdata:[");
	for(auto &pair: levelAvg){
		if (counter == levelAvg.size() - 1){
			f <<("'" + to_string(pair.first) + "'");
			counter = 0;
		}
		else{
			f <<("'" + to_string(pair.first) + "',");
			counter += 1;
		}
	}
	f <<("]\n\t},\n\tyAxis:{},\n");
	f <<("\tseries:[{\n\t\tname:'sale',\n\t\ttype:'line',\n\t\tdata:[");
	for(auto &pair: levelAvg) {
		if (counter == levelAvg.size() - 1){
			f <<(to_string(pair.second));
			counter = 0;
		}
		else{
			f <<(to_string(pair.second) + ",");
			counter += 1;
		}
	}
	f <<("]\n\t}]\n}\n");
	f <<("myChart.setOption(option);\n");
	f <<("</script></body></html>");
	f.close();
}

// age commend
void Stat::age(){
	map<int, double> ageSalary;

	for (SalaryModel sm: models){
		int ageInterval = (sm.getAge() - 20) / 10;

		if(ageSalary.find(ageInterval) != ageSalary.end()){
			ageSalary[ageInterval] += sm.getTotal();
		}
		else{
			ageSalary[ageInterval] = sm.getTotal();
		}
	}

	// print out echarts
	ofstream f;
	f.open("output/age.html");

	f <<("<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n");
	f <<("<title>AgeSalary</title>\n");
	f <<("<script src=\"../echarts.min.js\"></script>\n</head>\n");
	f <<("<body>\n<div id=\"main\" style=\"width: 1800px;height:800px;\"></div>\n");
	f <<("<script type=\"text/javascript\">\n");
	f <<("var myChart = echarts.init(document.getElementById('main'));\n");
	f <<("var option = {\n\t");
	f <<("tooltip:{},\n\t");
	f <<("xAxis: {\n\t\tdata:['20-29','30-39','40-49','50-59']");
	f <<("\n\t},\n\tyAxis:{},\n");
	f <<("\tseries:[{\n\t\tname:'sale',\n\t\ttype:'bar',\n\t\tdata:[");
	for(unsigned i = 0; i<ageSalary.size(); i++){
		if(counter == 9){
			f <<(to_string(ageSalary.at(i))+"");
			counter = 0;
		}
		else{
			f <<(to_string(ageSalary.at(i))+",");
			counter += 1;
		}
	}
	f <<("]\n\t}]\n}\n");
	f <<("myChart.setOption(option);\n");
	f <<("</script></body></html>");
	f.close();
}

// min commend
void Stat::min(){
	vector<double> allSalaries;
	for (unsigned i = 0; i < models.size(); i++){
		allSalaries.push_back(models.at(i).getTotal());
	}

	sort(allSalaries.begin(), allSalaries.end());

	// print out echarts
	ofstream f;
	f.open("output/min.html");

	f <<("<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n");
	f <<("<title>MinSalary</title>\n");
	f <<("<script src=\"../echarts.min.js\"></script>\n</head>\n");
	f <<("<body>\n<div id=\"main\" style=\"width: 1800px;height:800px;\"></div>\n");
	f <<("<script type=\"text/javascript\">\n");
	f <<("var myChart = echarts.init(document.getElementById('main'));\n");
	f <<("var option = {\n\t");
	f <<("tooltip:{},\n\t");
	f <<("xAxis: {\n\t\tdata:['Top1','Top2','Top3','Top4','Top5','Top6','Top7','Top8','Top9','Top10']");
	f <<("\n\t},\n\tyAxis:{},\n");
	f <<("\tseries:[{\n\t\tname:'sale',\n\t\ttype:'bar',\n\t\tdata:[");
	f << to_string(allSalaries.at(0)) << (",");
	f << to_string(allSalaries.at(1)) << (",") << to_string(allSalaries.at(2)) << (",");
	f << to_string(allSalaries.at(3)) << (",") << to_string(allSalaries.at(4)) << (",");
	f << to_string(allSalaries.at(5)) << (",") << to_string(allSalaries.at(6)) << (",");
	f << to_string(allSalaries.at(7)) << (",") << to_string(allSalaries.at(8)) << (",");
	f << to_string(allSalaries.at(9));
	f <<("]\n\t}]\n}\n");
	f <<("myChart.setOption(option);\n");
	f <<("</script></body></html>");

	f.close();
}
