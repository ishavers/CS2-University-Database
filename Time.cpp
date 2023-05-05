#include "Time.h"
#include <iostream>
#include <vector>
using namespace std;

Time::Time(){

}

void Time::SetDays(string day1){
	days.push_back(day1);
}

void Time::SetDays(string day1, string day2){
	days.push_back(day1);
	days.push_back(day2);
}

string Time::GetDays(){
	if(days.size() == 1){
    return(days.at(0));
  } else {
    return((days.at(0) + " " + days.at(1)));
  }
}

vector<string> Time::GetDayList(){
  return(days);
}

void Time::SetStart(string newStart){
	start = newStart;
}

void Time::SetEnd(string newEnd){
	end = newEnd;
}

