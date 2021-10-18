#include "student.h"
#include "subject.h"
#include <iostream>
#include <iomanip>
using namespace std;

// implement mot so ham phuc tap cua class Student trong student.h
void Student::update_scores(vector<float> scores_mid_10, vector<float> scores_final_10){
	//...
	return;
}

float Student::getFee(){
	//tinh hoc phi dua vao so tin chi hoc phi cua Subjects ma sv do dki
	return 0;
}

void Student::print_info(){
	cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Name: "<<this->name<<endl;
	cout<<"ID: "<<this->ID<<endl;
	cout<<"Class: "<<this->class_name<<endl;
	cout<<"Native place: "<<this->native_place<<endl;
	cout<<"Date of birth: "<<this->birthday<<endl;
	cout<<"Gender: "<<this->gender<<endl;
	cout<<"GPA: "<<this->GPA<<endl;
	cout<<"Rank: "<<this->rank<<endl;
	cout<<"Pass: "<<this->pass<<endl;
	cout<<"Fail: "<<this->fail<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"|"
		<<left
		<<setw(50)
		<<"Name"<<"|"
		<<left
		<<setw(10)
		<<"Code"<<"|"
		<<left
		<<setw(8)
		<<"Credit"<<"|"
		<<left
		<<setw(20)
		<<"Mid-term weight"<<"|"
		<<left
		<<setw(20)
		<<"Mid-term grade"<<"|"
		<<left
		<<setw(20)
		<<"End-term grade"<<"|"
		<<left
		<<setw(15)
		<<"Final grade"<<"|"
		<<left
		<<setw(17)
		<<"Final grade(char)"<<"|"
		<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	for (int i=0;i<this->subjects.size();i++){
		cout<<"|"
		<<left
		<<setw(50)
		<<this->subjects[i].getName()<<"|"
		<<left
		<<setw(10)
		<<this->subjects[i].getCode()<<"|"
		<<left
		<<setw(8)
		<<this->subjects[i].getCredit()<<"|"
		<<left
		<<setw(20)
		<<this->subjects[i].getWeight()<<"|"
		<<left
		<<setw(20)
		<<this->scores_mid_10[i]<<"|"
		<<left
		<<setw(20)
		<<this->scores_final_10[i]<<"|"
		<<left
		<<setw(15)
		<<this->scores_final_4[i]<<"|"
		<<left
		<<setw(17)
		<<this->scores_final_char[i]<<"|"
		<<endl;
	}
	cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
}
