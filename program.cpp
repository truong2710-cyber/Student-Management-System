#include "program.h"
#include "subject.h"
#include "classs.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

Program::Program(string name){
	this->name=name;
}
Program::Program(){
}
void Program::readCsv(string path){
	string line;
	ifstream file(path);
	if (!file.is_open()) {
		cout<<"Error: Can not open file!";
		return;
	}
	getline(file,line);
	while(getline(file,line)){
		vector<string> v=split(line,",");
		Subject subject(v[1],v[0],stoi(v[2]),stoi(v[4]),stof(v[3]));
		this->subjects.push_back(subject);
	}
}

void Program::print(){
	cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<this->name<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"|"
		<<left
		<<setw(60)
		<<"Name"<<"|"
		<<left
		<<setw(10)
		<<"Code"<<"|"
		<<left
		<<setw(10)
		<<"Credit"<<"|"
		<<left
		<<setw(20)
		<<"Mid-term weight"<<"|"
		<<left
		<<setw(15)
		<<"Fee credit"<<"|"
		<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
	for(int i=0;i<this->subjects.size();i++){
		cout<<"|"
			<<left
			<<setw(60)
			<<this->subjects[i].getName()<<"|"
			<<left
			<<setw(10)
			<<this->subjects[i].getCode()<<"|"
			<<left
			<<setw(10)
			<<this->subjects[i].getCredit()<<"|"
			<<left
			<<setw(20)
			<<this->subjects[i].getWeight()<<"|"
			<<left
			<<setw(15)
			<<this->subjects[i].getFeeCredit()<<"|"
			<<endl;
	}
	cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
}

Subject* Program::findSubject(string code){
	for (int i=0;i<this->subjects.size();i++){
		if (this->subjects[i].getCode()==code)
			return &this->subjects[i];
	}
	//cout<<"Error: Can not find subject with code "<<code<<" in education program!"<<endl;
	return nullptr;
}
