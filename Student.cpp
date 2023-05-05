#include "UnivMember.h"
#include "OfferedCourse.h"
#include "Student.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

//Default UnivMember Constructor
Student::Student():UnivMember(){
}

//UnivMember Constructor
Student::Student(string fullName):UnivMember(fullName){
}

int Student::GetMax(){
	return(MaxClasses);
}

void Student::SetMax(int newMax){
	MaxClasses = newMax;
}

vector<string> Student::GetSchedule(){
	/*
	cout << setw(35) << "Description" << setw(8) << "CRN" << setw(5) << "Section" << endl;
	for(int i = 0; i < Schedule.size(); i++){
		cout << setw(35) << Schedule.at(i).GetCourseTitle();
		cout << setw(8) << Schedule.at(i).GetCRN();
		cout << setw(5) << Schedule.at(i).GetSection() << endl;
	*/
	return(Schedule);
}

void Student::Enroll(string CRN){
	if(Schedule.size() < MaxClasses){
                Schedule.push_back(CRN);
        }else{
                cout << "Student Schedule is Full" << endl;
        }
}


void Student::Deroll(string CRN){
  for(int i = 0; i < Schedule.size(); ++i){
    if(Schedule.at(i) == CRN){
      Schedule.erase(Schedule.begin() + i);
    }
  }
}
