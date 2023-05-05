#ifndef NAME_H
#define NAME_H
#include <string>
#include <iostream>
using namespace std;

class Name{
	public:
		Name();
    Name(string full);
		string GetFname();
		string GetLname();
    string GetName();
		void SetFname(string tempName);
		void SetLname(string tempName);
   
    void deleteSpace(string first);
	private:
    string fname;
    string lname;
};
#endif
