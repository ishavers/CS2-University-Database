#include "ID.h"
#include <string>
#include <iostream>
using namespace std;

//Set Function
void ID::SetID(int temp){
	ID_num = temp;
	full_ID = 'A' + to_string(ID_num);
}

//Get Function
string ID::GetID(){
	return(full_ID);
}

//Default constructor
ID::ID(){
  static int x = 10000000;
	ID_num = x;
	full_ID = 'A' + to_string(ID_num);
  ++x;
}

//Print function
void ID::Print(){
	cout << full_ID << endl;
}
