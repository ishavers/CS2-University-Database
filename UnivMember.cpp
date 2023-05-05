#include "UnivMember.h"
#include "Name.h"
#include "ID.h"
#include <iostream>
#include <string>
using namespace std;

//default constructor
UnivMember::UnivMember(){
	UnivName = Name();
	Role = "Null";
}

//custom constructor
UnivMember::UnivMember(string fullName){
	UnivName = Name(fullName);
	Role = "Null";
}

//getter for ID
string UnivMember::GetID(){
	return(UnivID.GetID());
}

//getter for first name
string UnivMember::GetFname(){
	return(UnivName.GetFname());
}

//getter for last name
string UnivMember :: GetLname(){
  return(UnivName.GetLname());
}

//getter for role
string UnivMember::GetRole(){
	return(Role);
}

//setter for role
void UnivMember::SetRole(string newRole){
	Role = newRole;
}

//deletes space
void UnivMember:: DeleteSpace(){
  UnivName.deleteSpace(UnivName.GetFname());
}

//Print function
void UnivMember::Print(){
  cout << UnivName.GetFname() << " " << UnivName.GetLname() << endl;
  cout << "ID: " << UnivID.GetID() << endl;
} 