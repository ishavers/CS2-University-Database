#ifndef Course_H
#define Course_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Course{
	public:
		Course();
		Course(string tempNum, string tempName);
   
		string GetCnum();
		void SetCnum(string tempNum);
   
		string GetCourseTitle();
		void SetCourseTitle(string tempName);
   
		void PrintInfo();
	private:
		string cName;
		string Cnum;
};

#endif
