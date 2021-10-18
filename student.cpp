#include "student.h"
#include "subject.h"
#include <iostream>
#include <iomanip>
#define fee_unit 600000
using namespace std;

float convert_10_to_4(float score){
	if (score>=8.5) return 4; // A, A+
	if (8<=score) return 3.5; // B+
	if (7<=score) return 3; // B
	if (6.5<=score) return 2.5; // C+
	if (5.5<=score) return 2; // C
	if (5<=score) return 1.5; // D+
	if (4<=score) return 1; // D
	return 0; // F
}
string convert_10_to_char(float score){
	if (score>=9.5) return "A+"; // A+
	if (8.5<=score) return "A"; // A
	if (8<=score) return "B+"; // B+
	if (7<=score) return "B"; // B
	if (6.5<=score) return "C+"; // C+
	if (5.5<=score) return "C"; // C
	if (5<=score) return "D+"; // D+
	if (4<=score) return "D"; // D
	return "F"; // F
}
// implement mot so ham phuc tap cua class Student trong student.h
void Student::update_scores(vector<float> scores_mid_10, vector<float> scores_final_10){
	int count=0,count_credit=0;
	float GPA=0;
	this->scores_mid_10=scores_mid_10;
	this->scores_final_10=scores_final_10;
	for (int i=0;i<this->scores_mid_10.size();i++){
		if (this->scores_mid_10[i]!=-1 && this->scores_final_10[i]!=-1){
			float mid_term_weight=this->subjects[i].getWeight();
			float final_score=mid_term_weight*this->scores_mid_10[i]+(1-mid_term_weight)*this->scores_final_10[i];
			float final_score_4=convert_10_to_4(final_score);
			int credit=this->subjects[i].getCredit();
			if (final_score_4==0) this->fail+=credit;
			else this->pass+=credit;
			this->scores_final_4[i]=final_score_4;
			this->scores_final_char[i]=convert_10_to_char(final_score);
			count++;
			count_credit+=credit;
			GPA+=credit*final_score_4;
		}
	}
	if (count==this->scores_mid_10.size()){
		GPA/=count_credit;
		this->GPA=GPA;
	}
}

int Student::getFee(){
	//tinh hoc phi dua vao so tin chi hoc phi cua Subjects ma sv do dki (don vi VND)
	int count_fee_unit=0;
	for (int i=0;i<this->subjects.size();i++){
		count_fee_unit+=this->subjects[i].getFeeCredit();
	}
	this->fee=count_fee_unit*fee_unit;
	return this->fee;
}

void Student::print_info(){
	cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Name: "<<this->name<<endl;
	cout<<"ID: "<<this->ID<<endl;
	cout<<"Class: "<<this->class_name<<endl;
	cout<<"Native place: "<<this->native_place<<endl;
	cout<<"Date of birth: "<<this->birthday<<endl;
	cout<<"Gender: "<<this->gender<<endl;
	cout<<"GPA: "<<fixed<<setprecision(2)<<this->GPA<<endl;
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
		<<fixed<<setprecision(1)<<this->subjects[i].getWeight()<<"|"
		<<left
		<<setw(20)
		<<fixed<<setprecision(1)<<this->scores_mid_10[i]<<"|"
		<<left
		<<setw(20)
		<<fixed<<setprecision(1)<<this->scores_final_10[i]<<"|"
		<<left
		<<setw(15)
		<<fixed<<setprecision(1)<<this->scores_final_4[i]<<"|"
		<<left
		<<setw(17)
		<<this->scores_final_char[i]<<"|"
		<<endl;
	}
	cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"*Note: -1 or X mean currently unavailable."<<endl;
}
