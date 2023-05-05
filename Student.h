#ifndef Student_H
#define	Student_H
#include "UnivMember.h"
#include "OfferedCourse.h"
#include "Course.h" 
#include <string>
#include <vector>
using namespace std;

class Student: public UnivMember {
	public:
		Student();
		Student(string fullName);

		int GetMax();
		void SetMax(int newMax);

		vector<string> GetSchedule();

		void Enroll(string CRN);
    void Deroll(string CRN);

	private:
		vector <string> Schedule;
		int MaxClasses = 5;
};


#endif
