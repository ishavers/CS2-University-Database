#include "Course.h"
#include "OfferedCourse.h"
#include "Student.h"
#include "Time.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void operator +(string sID, OfferedCourse& Class){
        Class.roster.push_back(sID);
}


void operator -(string sID, OfferedCourse& Class){
  for(int i = 0; i < Class.roster.size(); ++i){
    if(sID == Class.roster.at(i)){
      Class.roster.erase(Class.roster.begin() + i);
    }
  }
}

bool operator !=(OfferedCourse& class1, OfferedCourse& class2){
  //Returns true if classes do not line up
  //Check if  time's of the two classes overlap
  vector<string> Class1days = class1.GetDayList();
  vector<string> Class2days = class2.GetDayList();
  int days1 = Class1days.size();
  int days2 = Class2days.size();
  
  for(int i = 0; i < days1; ++i){
    for(int j = 0; j < days2; ++j){
      if(Class1days.at(i) == Class2days.at(j)){
        if(class1.GetStart() == class2.GetStart()){
          return true;
        } else if (class1.GetEnd() == class2.GetEnd()){
          return true;
        }
      }
    }
  }
  return false;
}


void OfferedCourse::operator =(OfferedCourse& class2){
  this->SetCourseTitle(class2.GetCourseTitle());
  this->SetCnum(class2.GetCnum());
  this->SetInstructorName(class2.instructor);
  this->SetCRN(class2.GetCRN());
  this->SetClassTime(class2.GetClassTime());
  this->SetSection(class2.GetSection());
  this->roster = class2.roster;
}


OfferedCourse::OfferedCourse():Course(){
	instructor = "None";
  MAXSIZE = 30;
}

OfferedCourse::OfferedCourse(string tempNum, string tempSection, string tempName, string tempCRN, string tempTeacher, string tempDays, string tempHours):Course(tempName, tempNum){
	instructor = tempTeacher;
  CRN = tempCRN;
  SectNo = tempSection;
  MAXSIZE = 30;
  
  //Parse Days
  for(int i = 0; i < tempDays.length(); ++i){
    if(tempDays.at(i) == ','){
      meetingTime.SetDays(tempDays.substr(0,i), tempDays.substr(i+1, (tempDays.length() - (i+1))));
    }
  }
  if((meetingTime.GetDays().size()) == 0){
    meetingTime.SetDays(tempDays);
  }
  
  //Parse Time
  for(int i = 0; i < tempHours.length(); ++i){
    if(tempHours.at(i) == '-'){
      meetingTime.SetStart(tempHours.substr(0, i-2));
      meetingTime.SetEnd(tempHours.substr(i+2, tempHours.length()-1));
    } 
  }
}

string OfferedCourse::GetInstructorName(){
	return(instructor);
}

void OfferedCourse::SetInstructorName(string tempTeacher){
	instructor = tempTeacher;
}

Time& OfferedCourse::GetClassTime(){
	return(meetingTime);
}

void OfferedCourse::SetClassTime(Time& newTime){
  meetingTime = newTime;
}
void OfferedCourse::SetClassTime(string tempDays, string tempHours){
	//Parse Days
  for(int i = 0; i < tempDays.length(); ++i){
    if(tempDays.at(i) == ','){
      meetingTime.SetDays(tempDays.substr(0,i), tempDays.substr(i+1, (tempDays.length() - (i+1))));
    }
  }
  if(tempDays.find(",") == string::npos){
    meetingTime.SetDays(tempDays);
  }
  
  //Parse Time
  for(int i = 0; i < tempHours.length(); ++i){
    if(tempHours.at(i) == '-'){
      meetingTime.SetStart(tempHours.substr(0, 8));
      meetingTime.SetEnd(tempHours.substr(i+2, 8));
    } 
  }
}

void OfferedCourse::PrintTime(){
  cout << "Days: " << meetingTime.GetDays() << endl;
  cout << "Time: " << meetingTime.GetStart() << '-' << meetingTime.GetEnd() << endl;
}

string OfferedCourse::GetSection(){
  return(SectNo); 
}

void OfferedCourse::SetSection(string newSect){
  SectNo = newSect;
}

string OfferedCourse::GetCRN(){
  return(CRN);
}

void OfferedCourse::SetCRN(string newCRN){
  CRN = newCRN;
}
vector<string> OfferedCourse::GetRoster(){
  return(roster);
}

bool OfferedCourse::SearchRoster(string sID){
  for(int i = 0; i < roster.size(); ++i){
    if(sID == roster.at(i)){
      return(true);
    }
  }
  return(false);
} 