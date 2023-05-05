#include "Course.h"
#include <string>
#include <iostream>
using namespace std;

Course::Course(){
	cName = "Course name";
	Cnum = "000000";
}

Course::Course(string tempNum, string tempName){
	cName = tempName;
	Cnum = tempNum;
}

string Course::GetCnum(){
	return(Cnum);
}

void Course::SetCnum(string tempNum){
	Cnum = tempNum;
}

string Course::GetCourseTitle(){
	return(cName);
}

void Course::SetCourseTitle(string tempName){
	cName = tempName;
}

void Course::PrintInfo(){
	cout << "Course Information:" << endl;
	cout << "   Course Number: " << Cnum << endl;
	cout << "   Course Title: " << cName << endl;
}
