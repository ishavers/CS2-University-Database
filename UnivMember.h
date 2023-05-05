#ifndef UnivMember_H
#define UnivMember_H
#include <iostream>
#include <string>
#include "ID.h"
#include "Name.h"
using namespace std;

class UnivMember{
	public:
		UnivMember();
		UnivMember(string fullName);
		string GetID();

		string GetFname();
    string GetLname();

		string GetRole();
		void SetRole(string newRole);
  
    void Print();
    void DeleteSpace();
	private:
		ID UnivID;
		Name UnivName;
		string Role;
};

#endif
