#ifndef OfferedCourse_H
#define OfferedCourse_H
#include "Course.h"
#include "Student.h"
#include "Time.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class OfferedCourse: public Course{
	public:
    void friend operator +(string sID, OfferedCourse& Class);
    void friend operator -(string sID, OfferedCourse& Class);
    bool friend operator !=(OfferedCourse& class1, OfferedCourse& class2);
    void operator =(OfferedCourse& class2);
 
		OfferedCourse();
		OfferedCourse(string tempNum, string tempSection, string tempName, string tempCRN, string tempTeacher, string tempDays, string tempHours);
		
    string GetInstructorName();
		void SetInstructorName(string tempTeacher);
    
  
		Time& GetClassTime();
		void SetClassTime(string tempDays, string tempHours);
    void SetClassTime(Time& newTime);
    void PrintTime();
    
    string GetStart(){
      return(meetingTime.GetStart());
    }
    string GetEnd(){
      return(meetingTime.GetEnd());
    }
    vector<string> GetDayList(){
      return(meetingTime.GetDayList());
    }
   
    string GetSection();
    void SetSection(string newSect);
    
    string GetCRN();
    void SetCRN(string newCRN);
    
    vector<string> GetRoster();
    bool SearchRoster(string sID);
    
    
	private:
		string instructor;
    string CRN;
    Time meetingTime;
    string SectNo;
    vector <string> roster;
    int MAXSIZE;
};

#endif
