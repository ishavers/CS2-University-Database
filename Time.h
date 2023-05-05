#ifndef Time_H
#define Time_H
#include <iostream>
#include <vector>
using namespace std;

class Time{
	public:
		Time();
		
		void SetDays(string day1);
		void SetDays(string day1, string day2);
		string GetDays();
    vector<string> GetDayList();

		void SetStart(string newStart);
		string GetStart(){
			return(start);
		}

		void SetEnd(string newEnd);
		string GetEnd(){
			return(end);
		}
	private:
		vector<string> days;
		string start;
		string end;
};

#endif
