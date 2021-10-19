#include <iostream>
#include <vector>
#include "student.h"
#include "subject.h"
#include "classs.h"
#include "program.h"
#include <memory>
using namespace std;

Program initProgram(string name, string path){
	Program program(name);
	program.readCsv(path);
	return program;
}

vector<Classs> initClasses(Program program){
	vector<Classs> classes;
	Classs cl1("CTTN-IT-K64",program);
	cl1.readCsv("data/basic_data.csv"); 
	cl1.getRegisterInfoFromCsv("data/register_data.csv");
	//cout<<cl1.getStudents()[0].getSubjects().size()<<endl;
	classes.push_back(cl1);
	
	Classs cl2("IT1-01",program);
	cl2.readCsv("data/basic_data2.csv"); 
	cl2.getRegisterInfoFromCsv("data/register_data.csv");
	classes.push_back(cl2);
	
	return classes;
}

void printClassInfo(vector<Classs> classes){
	string name;
	cout<<"Enter class name: ";
	cin.ignore();
	getline(cin,name);
	while(true){
		for (Classs classs:classes){
			if (classs.getName()==name){
				int i;
				cout<<"Choose sort method(1/2):"<<endl;
				cout<<"1. By name"<<endl;
				cout<<"2. By GPA"<<endl;
				do{
					cin>>i;
					if (i!=1 && i!=2) 
						cout<<"Invalid input! Please choose again: ";
				} while(i!=1 && i!=2);
				if (i==1) classs.orderByName();
				if (i==2) classs.orderByGPA();
				classs.print();
				return;
			}
		}
		cout<<"Error: Can not find class "<<name<<"!"<<endl;
		cout<<"Enter again (or enter 'exit' to quit): ";
		getline(cin,name);
		if (name=="exit") return;
	}
}

vector<Student> searchByName(vector<Classs> classes, string name){
	vector<Student> result;
	for (Classs classs:classes){
		vector<Student> temp=classs.findStudentByName(name);
		result.insert(result.end(),temp.begin(),temp.end());
	}
	return result;
}

Student* searchpByID(vector<Classs> &classes, int ID){
	for (int i=0;i<classes.size();i++){
		Student* temp=classes[i].findpStudentByID(ID);
		if (temp!=nullptr){
			//(*temp).print_info();
			return classes[i].findpStudentByID(ID);
		}
	}
	return nullptr;
}

pair<Student,bool> searchByID(vector<Classs> classes, int ID){
	pair<Student,bool> temp;
	for (Classs classs:classes){
		temp=classs.findStudentByID(ID);
		if (temp.second==true){
			//(*temp).print_info();
			return temp;
		}
	}
	//cout<<"Can not find student with ID "<<ID<<endl;
	return make_pair(temp.first,false);
}

void searchStudentInfo(vector<Classs> classes){
	vector<Student> result;
	cout<<"Choose search method(1/2):"<<endl;
	cout<<"1. Search by name"<<endl;
	cout<<"2. Search by ID"<<endl;
	int i;
	do{
		cin>>i;
		if (i!=1 && i!=2) 
			cout<<"Invalid input! Please choose again: ";
	} while(i!=1 && i!=2);
	if (i==1){
		string name;
		cout<<"Enter full name: ";
		cin.ignore();
		getline(cin,name);
		vector<Student> result=searchByName(classes,name);
		if (result.size()==0){
			cout<<"No result found!"<<endl;
			return;
		}
		for (int i=0;i<result.size();i++){
			result[i].print_info();
		}
	}
	if (i==2){
		int ID;
		cout<<"Enter ID: ";
		cin>>ID;
		pair<Student,bool> result=searchByID(classes,ID);
		if (result.second==true){
			(result.first).print_info();
			return;
		}
		cout<<"No result found!"<<endl;
	}
}

void updateScore(vector<Classs> &classes){
	int ID;
	string code;
	vector<float> mid,final;
	float temp;
	cout<<"Enter ID: ";
	cin>>ID;
	Student* student=searchpByID(classes,ID);
	if (student==nullptr){
		cout<<"Can not find student with ID "<<ID;
		return;
	}
	for (int i=0;i<(*student).getSubjects().size();i++){
		cout<<(*student).getSubjects()[i].getCode()<<": "<<(*student).getSubjects()[i].getName()<<endl;
		cout<<"Enter mid-term score: ";
		cin>>temp;
		mid.push_back(temp);
		cout<<"Enter final exam score: ";
		cin>>temp;
		final.push_back(temp);
	}
	(*student).print_info();
	(*student).update_scores(mid,final);
	cout<<"Score updated successfully!"<<endl;
}

void printMenu(){
	cout<<"+--------------------------------------------------------------------+"<<endl;
	cout<<"|                     STUDENT MANAGEMENT SYSTEM                      |"<<endl;
	cout<<"+--------------------------------------------------------------------+"<<endl;
	cout<<"|1. Print class information                                          |"<<endl;
	cout<<"|2. Search student information                                       |"<<endl;
	cout<<"|3. Update student's score                                           |"<<endl;
	cout<<"|4. Update student's personal information                            |"<<endl;
	cout<<"|5. Delete a student from system                                     |"<<endl;
	cout<<"|6. Exit                                                             |"<<endl;
	cout<<"+--------------------------------------------------------------------+"<<endl;           
}

int main(int argc, char** argv) {
	//test
	int choice;
	Program program=initProgram("Talented Program IT","data/education_program.csv");
	vector<Classs> classes=initClasses(program);
	while (true){
	printMenu();
	cout<<"Please enter your choice: ";
	do{
		cin>>choice;
		if (choice!=1 && choice!=2 && choice!=3 && choice !=4 && choice!=5 && choice!=6)
			cout<<"Invalid input! Please enter again: ";
	}while (choice!=1 && choice!=2 && choice!=3 && choice !=4 && choice!=5 && choice!=6);
	switch(choice){
		case 1:
			printClassInfo(classes);
			break;
		case 2:
			searchStudentInfo(classes);
			break;
		case 3:
			updateScore(classes);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			cout<<"Bye! See ya later!";
			return 0;
			break;
	}
	}
	return 0;
}
