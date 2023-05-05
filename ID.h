#ifndef ID_H
#define ID_H
#include <iostream>
#include <string>
using namespace std;

//Declaration of class ID
class ID{
	public: 
		ID();
		string GetID();
		void SetID(int temp);
		void Print();
	private:
		int ID_num;
		string full_ID;
};

#endif
