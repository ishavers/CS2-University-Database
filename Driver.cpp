#include <iostream>
#include "UnivMember.h"
#include "Student.h"
#include "Course.h"
#include "OfferedCourse.h"
#include "Name.h"
#include "ID.h"
#include "Time.h"
#include <vector>
#include <string>
#include <iomanip>
#include <ios>
#include <fstream>
#include <array>
#include <cctype>
#include <stdlib.h>
using namespace std;

class Student;
class Course;
class OfferedCourse;

//Callable instance of Courses
struct Courses{
        Course mainCourse;
        vector<OfferedCourse> Sections;
};


string View0();
string View1(vector<Courses>& ClassList);
string View2(Courses& SectionList);
string View3(Courses& Class, string CRN, vector<Student>& Students);
string View4(vector<Student>& Students, string sID, vector<Courses>& ClassList);
string View5(vector<Student>& Students);
string View6(vector<Student>& Students, vector<Courses>& ClassList, string sID, string todo);

//Searches the classlist for a course
bool Contains(vector<Courses>& toSearch, string& forSearch){
	for(int i = 0; i < toSearch.size(); ++i){
		if(forSearch == toSearch.at(i).mainCourse.GetCnum()){
			return(true);
		}
	}
	return(false);
}

//Deletes white space
string deleteSpace(string temp){
	if(!temp.empty() && temp[temp.size() - 1] == ' '){
		temp.erase(temp.length()-1);
	}
	return(temp);
}

//Seperates the string 
string FindName(string& fullLine, string& name){
	for(int i = 1; i < fullLine.length(); ++i){
		if(fullLine.at(i) == '"'){
			name = fullLine.substr(2, i-2);
			string newLine = fullLine.substr(i+1, fullLine.length()-1);
			return(newLine);
		}
	}
	return("No Name Found");
}

//Seperates the CRNs
void ParseCRN(string CRNLine, string myCRN[5]){
	for(int i = 0; i < CRNLine.length(); ++i){
                        if(CRNLine.at(i) == '\t' || CRNLine.at(i) == ' '){
                                CRNLine.erase(i, 1);
                        }
        }
	
	int j = 0;
	for(int i = 0; i < 5; ++i){
		myCRN[i] = CRNLine.substr(j, 5);
		j = j+5;
	}
}

//Seperate the course information
void ParseCourse(string& fullLine, Courses& myCourse, int s){
	int breaker = 0;
	string days;

	for(int i = 0; i < fullLine.length();++i){
		//Parse through the remaining data
		if(fullLine.at(i) == '\t'){
			switch(breaker){
				case 1:	
					//Section
					myCourse.Sections.at(s).SetSection(fullLine.substr(i+1, 3));
					break;
				case 4:
					//CRN
					myCourse.Sections.at(s).SetCRN(deleteSpace(fullLine.substr(i+1, 5)));
					break;
				case 6:
					//Instructor
					{
					int nameEnd = 0;
					if(fullLine.substr(i+1, 3) == "TBD"){
						myCourse.Sections.at(s).SetInstructorName(fullLine.substr(i+1, 3));
						myCourse.Sections.at(s).GetInstructorName();
					} else {
						int p = 0;
						for(int i = 0; i < fullLine.length(); ++i){
							if(fullLine.at(i) == '"'){
								p++;
							}
							if(p == 1){
								nameEnd = i;
							}
						}
						myCourse.Sections.at(s).SetInstructorName(fullLine.substr(i+2, nameEnd - (i+2)));
					}
					}
					break;
				case 7:
					//Days
					{
					int p = 0;
					int dayEnd = 0;
					for(int i = 0; i < fullLine.length(); ++i){
                                                if(fullLine.at(i) == '"'){
                                                	p++;
                                                }
						if(fullLine.find("TBD") == string::npos){
							if(p == 3){
								dayEnd = i;
							}
						} else {
                                                	if(p == 1){
                                                        	dayEnd = i;
                                        		}
						}
                                        }
					days = fullLine.substr(i+2, (dayEnd - (i+1)));
					}	
					break;
				case 8:
					myCourse.Sections.at(s).SetClassTime(days, fullLine.substr(i+1, 19));
					break;
			}
			breaker++;
		}
	}
}

void CanTakeClass(vector<Student>& Students, vector<Courses>& ClassList){
	OfferedCourse Class1;
	OfferedCourse Class2;
	
	for(int s = 0; s < Students.size(); ++s){
		//class1
		for(int i = 0; i < Students.at(s).GetSchedule().size() ; ++i){
			bool isLab = false;
			bool takeLab = false;
			bool canTakeCourse = true;
			//class2
			for(int j = 0; j <  Students.at(s).GetSchedule().size(); ++j){
				//Search through class list
				for(int c = 0; c < ClassList.size(); ++c){
					//Search for section
					for(int o = 0; o < ClassList.at(c).Sections.size(); ++o){
						//search for course assignment for class1 and class2
						if(Students.at(s).GetSchedule().at(i) == ClassList.at(c).Sections.at(o).GetCRN()){
							Class1 = ClassList.at(c).Sections.at(o);
						}
						if(Students.at(s).GetSchedule().at(j) == ClassList.at(c).Sections.at(o).GetCRN()){
							Class2 = ClassList.at(c).Sections.at(o);
						}
					}
				}
				//Check if it is the same class
                                if(Class1.GetCRN() != Class2.GetCRN()){
                                	//Class compatability check
                                        if(Class1 != Class2){
                                               	canTakeCourse = false;
					}
                                }

                                //check if is lab
                                if(Class1.GetCourseTitle().find("Lab") != string::npos){
                                	isLab = true;
                               	}

				//Lab compatability check
                                if(isLab){
                                        if(Class1.GetCnum() == Class2.GetCnum()){
                                                int l = Class2.GetCourseTitle().find("Lab");
                                                if(l == -1){
                                                       	takeLab = true;
                                                }
                               		}
                                }
			}
			if(isLab){
				if(!takeLab){
					canTakeCourse = false;
				}
			}
			if(!canTakeCourse){
                        	Students.at(s).Deroll(Class1.GetCRN());
                        	--i;
                	}
		}
	}
}

//back function
int BackCalled(vector<string>& path, vector<string>& prompts, int pathIdx, vector<Student>& Students, vector<Courses>& ClassList, string& navPrompt){
	//Checks if returning to the home screen
	if(pathIdx > 2){
		pathIdx = pathIdx-2;
		//Delete the backtracked views
        	for (int i = 2; i > 0;--i){
                	path.pop_back();
                	prompts.pop_back();
        	}
	} else {
		pathIdx = 0;
		for(int i = 2; i > 0; --i){
			path.pop_back();
			prompts.pop_back();
		}
	}
	
	//Set the prompt
	if(pathIdx >=  1){
		navPrompt = prompts.at(pathIdx-1);
	} else {
		navPrompt = "home";
	}
	
	cout << "pathIdx is " << pathIdx << endl;
	for(int i = 0; i < path.size(); ++i){
		cout << path.at(i) << "  " << prompts.at(i) << endl;
	}

	return(pathIdx);
}

//General catch all statement
string catchMistake(vector<string>& path, vector<string>& prompts, int& pathIdx){
	string newPrompt;
	
	if(pathIdx >= 2){
		pathIdx = pathIdx - 1;
	} else if(pathIdx == 1){
		pathIdx = 0;
	} else {
		pathIdx = -1;
	}

	if(pathIdx == -1){
		newPrompt = "home";
	} else if(pathIdx == 0){
		newPrompt = prompts.at(pathIdx); 
	} else {
		newPrompt = prompts.at(pathIdx);
	}

	path.pop_back();
	prompts.pop_back();

	return(newPrompt);
}

//checks all the inputs
void runViews(vector<string>& path, vector<string>& prompts, vector<Student>& Students, vector<Courses>& ClassList, int& pathIdx, string& navPrompt){
	pathIdx++;
        //Back check
        if(navPrompt == "back"){
         	pathIdx = BackCalled(path, prompts, pathIdx, Students, ClassList, navPrompt);
        }
        //View0 checks
        if (navPrompt == "student"){
         	navPrompt = View5(Students);
                path.push_back("View5");
                prompts.push_back(navPrompt);

        } else if (navPrompt == "course"){
                navPrompt = View1(ClassList);
               	path.push_back("View1");
                prompts.push_back(navPrompt);

        } else if (navPrompt == "home"){
                navPrompt = View0();
               	path.push_back("View0");
               	prompts.push_back(navPrompt);

        //View1 checks
        } else if (navPrompt.length() == 4){
         	for(int i = 0; i < ClassList.size();++i){
                	if(navPrompt == ClassList.at(i).mainCourse.GetCnum()){
                        	navPrompt = View2(ClassList.at(i));
                                path.push_back("View2");
                                prompts.push_back(navPrompt);
                       	}
                }
	//View2 checks
	} else if (navPrompt.length() == 5){
        	for(int i = 0; i < ClassList.size(); ++i){
                	for(int j = 0; j < ClassList.at(i).Sections.size(); ++j){
                        	if(navPrompt == ClassList.at(i).Sections.at(j).GetCRN()){
                                	navPrompt = View3(ClassList.at(i), navPrompt, Students);
                                       	path.push_back("View3");
                                        prompts.push_back(navPrompt);
                                }
                       	}
               	}
	//View3 checks
        } else if (navPrompt.length() == 9){
        	for(int i = 0; i < Students.size(); ++i){
                	if(navPrompt == Students.at(i).GetID()){
                    		navPrompt = View4(Students, navPrompt, ClassList);
                                path.push_back("View4");
                                prompts.push_back(navPrompt);
                        }
                }
	//View4 checks
        } else if (navPrompt == "add"){
		navPrompt = View6(Students, ClassList, prompts.at(pathIdx - 2),"add");
        	path.push_back("View6");
                prompts.push_back(navPrompt);

        } else if (navPrompt == "remove"){
                navPrompt = View6(Students, ClassList, prompts.at(pathIdx - 2), "remove");
		path.push_back("View6");
                prompts.push_back(navPrompt);
       	//Catchall error
        }
        if(navPrompt == "mistake"){
        	navPrompt = catchMistake(path, prompts, pathIdx);
        }

}

int main(){
	ifstream infile;
	vector <Student> Students; 
	vector <Courses> ClassList;
	ClassList.resize(26);
	string fullLine;

	//creates the instances of Students
	infile.open("StudentsWithCRNs.txt");

	while(getline(infile, fullLine)){
		string tempName;
		//Seperates the name from the rest of the string
		string CRNLine;
	        CRNLine = FindName(fullLine, tempName);
		
		Student tempStudent(tempName);
                tempStudent.DeleteSpace();

		//Seperates the CRNs
		string CRNs[5];
		ParseCRN(CRNLine, CRNs);

		for(int i = 0; i < 5; ++i){
			tempStudent.Enroll(CRNs[i]);
		}
		Students.push_back(tempStudent);
  	}
	infile.close();
	
	//Create a vector of course structures
	infile.open("CoursesFall2023Tab.txt");
	
	//Course count
	int j = 0;

	//Section count
	int s = 0;
	while(getline(infile, fullLine)){
		//Discard first instance
		if(j != 0){
		
			//Find the ending of the title
			int endTitle = 0;
			for(int i = 0; i < fullLine.length(); ++i){
				if(i > 20 && isdigit(fullLine.at(i))){
					endTitle = i;
					break; 
				}
			}
			
			string tempNum, tempName;
			//Create the course with title and number
			for(int i = 0; i < fullLine.length(); ++i){
				//Assigns course number
                		if(i == 5){
                        		tempNum = fullLine.substr(i, 4);
                		}
				
				//Assigns the course title
				if(i == 14){
					tempName = fullLine.substr(i, endTitle - (i+1));
				}
			}

			//Checks if the course has already been created
                       	if(Contains(ClassList, tempNum)){
				j--;
			} else {
				ClassList.at(j-1).mainCourse.SetCourseTitle(tempName);
				ClassList.at(j-1).mainCourse.SetCnum(tempNum);
				s = 0;
			}
			
			//Creates section
			ClassList.at(j-1).Sections.resize(s+1);
			ClassList.at(j-1).Sections.at(s).SetCourseTitle(tempName);
			ClassList.at(j-1).Sections.at(s).SetCnum(tempNum);
                        ParseCourse(fullLine, ClassList.at(j-1), s);
                        ++s;
		}
		++j;
	}
	infile.close();

	CanTakeClass(Students, ClassList);

	//Fill Class Roster
	for(int i = 0; i < Students.size(); ++i){
		vector<string> stuSched = Students.at(i).GetSchedule();
		for(int q = 0; q < Students.at(i).GetSchedule().size(); ++q){
			for(int p = 0; p < ClassList.size(); ++p){
				for(int z = 0; z < ClassList.at(p).Sections.size(); ++z){
					if(stuSched.at(q) == ClassList.at(p).Sections.at(z).GetCRN()){
						Students.at(i).GetID() + ClassList.at(p).Sections.at(z);
					}
				}
			}
		}
	}
	
	//Navigation
	vector<string> path;
	vector<string> prompts;

	int pathIdx = 0;
	
	//Welcome
	cout << "Welcome! You will use text entries to navigate through this system." << endl;
	cout << "You can enter 'back' at any point to return to your previous screen.";
        cout <<	"You can also enter 'end' to finish the program" << endl;
	
	path.push_back("View0");
	string navPrompt = View0();
	prompts.push_back(navPrompt);

	if(navPrompt == "mistake"){
		navPrompt = catchMistake(path, prompts, pathIdx);
	}
	do{
		runViews(path, prompts, Students, ClassList, pathIdx, navPrompt);
	}while(navPrompt != "end");

	return 0;
}

//Opening page and directory guide view 0
string View0(){
	string youProm0;

	//Promt
	cout << "Search by 'student' or 'course'" << endl;
	cin >> youProm0;
	for(int i = 0; i < youProm0.length(); ++i){
		youProm0.at(i) = tolower(youProm0.at(i));
	}

	cout << endl;

	//Input check
	if(youProm0 == "student"){
		return(youProm0);
	} else if(youProm0 == "course"){
		return(youProm0);
	} else if(youProm0 == "end"){
		exit(0);
	} else if(youProm0 == "back"){
		return(youProm0);
	}
	return("mistake");
}

//List of available courses
string View1(vector<Courses>& ClassList){
	string youProm1;
	
	//Display class list
	cout << setw(14) << "Course Number:" << setw(20) << left << "Description:" << endl;
	for(int i = 0; i < ClassList.size(); ++i){
		cout << setw(14) << left << ClassList.at(i).mainCourse.GetCnum();
	       	cout << setw(25) << left << ClassList.at(i).mainCourse.GetCourseTitle() << endl;
	}
	cout << "Enter a Course Number to view Sections:" << endl;
	
	cin >>youProm1;

	cout << endl;

	//verify input
	if(youProm1 == "back"){
		return(youProm1);
	} else if (youProm1 == "end"){
		exit(0);
	} else {
		for(int i = 0; i < ClassList.size(); ++i){
			if(youProm1 == ClassList.at(i).mainCourse.GetCnum()){
				return(youProm1);
			}
		}
	}
	return("mistake");
}

//List of course sections
string View2(Courses& SectionList){
	string youProm2;	
	
	//Draw
	cout << SectionList.mainCourse.GetCourseTitle() << endl;
	cout << setw(10) << "Section:" << setw(8) << left << "CRN:" << setw(5) << "Size:" << endl;
	cout << endl;
	for(int i = 0; i < SectionList.Sections.size(); ++i){
		cout << setw(10) << left << SectionList.Sections.at(i).GetSection();
		cout << setw(8) << left << SectionList.Sections.at(i).GetCRN();
		cout << setw(2) << left << SectionList.Sections.at(i).GetRoster().size() << "/35" << endl;
		SectionList.Sections.at(i).PrintTime();
		cout << endl << endl;
	}
	
	//Prompt
	cout << "Enter CRN to view Section information:" << endl;
	cin >> youProm2;

	cout << endl;

	//Entry verification
	if(youProm2 == "back"){
		return(youProm2);
	} else if(youProm2 == "end"){
		exit(0);
	}

	for(int i = 0; i < SectionList.Sections.size(); ++i){
		if(youProm2 == SectionList.Sections.at(i).GetCRN()){
			return(youProm2);
		} 
	}
	return("mistake");
}

//Class Roster
string View3(Courses& Class, string CRN, vector<Student>& Students){
	int currSection;
	string youProm3;

	for(int i = 0; i < Class.Sections.size(); ++i){
		if(CRN == Class.Sections.at(i).GetCRN()){
			currSection = i;
		}
	}

	//Draw
	cout << Class.mainCourse.GetCourseTitle() << " Section " << Class.Sections.at(currSection).GetSection() << endl;
	cout << setw(25) << "Class Roster" << setw(5) << "ID" << endl;
	
	for(int j = 0; j < Students.size(); ++j){
		if(Class.Sections.at(currSection).SearchRoster(Students.at(j).GetID())){
			string name = Students.at(j).GetFname() + " " + Students.at(j).GetLname();
			cout << setw(18) << left << name;
			cout << '\t' <<  setw(5) << Students.at(j).GetID() << endl;
		}
	}

	//Prompt
	cout << "Enter Student ID to view Student info: " << endl;
	cin >> youProm3;

	cout << endl;

	//Entry verification
        for(int i = 0; i < Students.size(); ++i){
		if(youProm3 == "back"){
			return(youProm3);
		} else if(youProm3 == "end"){
			exit(0);
		} else if (youProm3 == Students.at(i).GetID()){
			return(youProm3);
		}	
	}
	return("mistake");
}

//Student Information
string View4(vector<Student>& Students, string sID, vector<Courses>& ClassList){
	string youProm4;
	int currStudent;
	
	//Find student
	for(int i = 0; i < Students.size(); ++i){
		if(sID == Students.at(i).GetID()){
			currStudent = i;
		}
	}

	//Draw
	cout << Students.at(currStudent).GetFname() << " " << Students.at(currStudent).GetLname() << endl;
	cout << "ID: " << Students.at(currStudent).GetID() << endl << endl;
	cout << "Schedule: " << endl;
	
	for(int i = 0; i < Students.at(currStudent).GetSchedule().size(); ++i){
		for(int j = 0; j < ClassList.size(); ++j){
			for(int z = 0; z < ClassList.at(j).Sections.size(); ++z){
				if(Students.at(currStudent).GetSchedule().at(i) == ClassList.at(j).Sections.at(z).GetCRN()){
					cout << setw(40) << left << ClassList.at(j).mainCourse.GetCourseTitle(); 
					cout << setw(5) << ClassList.at(j).Sections.at(z).GetSection() << endl;
				}
				
			}	
		}
	}

	cout << "What would you like to do: 'add' a class, or 'remove' a class" << endl;
	cin >> youProm4;

	//Entry verification
	if(youProm4 == "add"){
		if(Students.at(currStudent).GetSchedule().size() == 5){
			cout << "Class Schedule full: no class can be added" << endl;
		} else {
			return(youProm4);
		}
	} else if(youProm4 == "remove"){
		if(Students.at(currStudent).GetSchedule().size() == 0){
			cout << "Class Schedule empty: no class can be removed" << endl;
		} else {
			return(youProm4);
		}
	} else if(youProm4 == "back"){
		return(youProm4);
	} else if(youProm4 == "end"){
		exit(0);
	}
	return("mistake");
}

//Student Search
string View5(vector<Student>& Students){
	string youProm5;
	
	//Draw
	cout << "STUDENT LIST" << endl;
	for(int i = 0; i < Students.size(); ++i){
		string name = Students.at(i).GetFname() + " " + Students.at(i).GetLname();
		cout << setw(23) << left << name << setw(10) << left << Students.at(i).GetID() << endl;
	}

	//Prompt
	cout <<  "Enter Student ID to view Student info: " << endl;
	cin >> youProm5;

	cout << endl;

	//Entry Verification
        for(int i = 0; i < Students.size(); ++i){
                if(youProm5 == "back"){
                        return(youProm5);
		} else if(youProm5 == "end"){
			exit(0);
                } else if (youProm5 == Students.at(i).GetID()){
                        return(youProm5);
                }
        }
        return("mistake");
}

//Remove/Add classes
string View6(vector<Student>& Students, vector<Courses>& ClassList, string sID, string todo){
	string youProm6;
	int currStudent;
	
	for(int i = 0; i < Students.size(); ++i){
		if(Students.at(i).GetID() == sID){
			currStudent = i;
		}
	}

	cout << "todo is " << todo << endl;
	//Prompt
	if(todo == "add"){
		cout << "Enter CRN of class to add to student schedule:" << endl;
		cin >> youProm6;
		if(youProm6 == "end"){
                        exit(0);
		}
		for(int i = 0; i < Students.at(currStudent).GetSchedule().size(); ++i){
			if(Students.at(currStudent).GetSchedule().at(i) == youProm6){
				cout << "Class already in schedule" << endl;
				return("back");
			}
		}
		
		for(int i = 0; i < ClassList.size(); ++i){
			for(int j = 0; j < ClassList.at(i).Sections.size(); ++j){
				if(youProm6 == ClassList.at(i).Sections.at(j).GetCRN()){
					Students.at(currStudent).Enroll(youProm6);
					Students.at(currStudent).GetID() + ClassList.at(i).Sections.at(j);
					return("back");
				}
			}
		}

	} else if(todo == "remove"){
		cout << "Enter CRN of class to remove from student schedule:" << endl;
		cin >> youProm6;
		if(youProm6 == "end"){
			exit(0);
		}
		for(int i = 0; i < Students.at(currStudent).GetSchedule().size(); ++i){
                        if(Students.at(currStudent).GetSchedule().at(i) == youProm6){
                                Students.at(currStudent).Deroll(youProm6);
                        }
                }

		for(int i = 0; i < ClassList.size(); ++i){
                        for(int j = 0; j < ClassList.at(i).Sections.size(); ++j){
                                if(youProm6 == ClassList.at(i).Sections.at(j).GetCRN()){
					Students.at(currStudent).GetID() - ClassList.at(i).Sections.at(j);
					return("back");
                                }
                        }
                }
	} else{
		return("back");
	}
	return("back");
}	
