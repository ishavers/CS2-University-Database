#include "Name.h"
#include <string>
#include <iostream>
using namespace std;

class Name;

string Name::GetFname(){
	return(fname);
}

string Name::GetLname(){
	return(lname);
}

string Name::GetName(){
  return(fname + " " + lname);
}

void Name::SetFname(string tempName){
	fname = tempName;
}

void Name::SetLname(string tempName){
	lname = tempName;
}

Name::Name(string full){
  for(int i = 0; i < full.length(); ++i){
		if(full.at(i) == ','){
			fname = full.substr(i+1, full.length() - 2);
			lname = full.substr(0, i);
		}
	}
}

Name::Name(){
	fname = "First";
	lname = "Last";
}
void Name::deleteSpace(string first){
  string temp = first;
  if(!temp.empty() && temp[temp.size() - 1] == '\r'){
    temp.erase(temp.length()-1);
  }
  if(!temp.empty() && temp[temp.size() - 1] == ' '){
    temp.erase(temp.length()-1);
  }
    
  fname = temp;
}
