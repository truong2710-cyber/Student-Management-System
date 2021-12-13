#include "classs.h"
#include "student.h"
#include "program.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <memory>
#include <cstdio>
#include <cstring>
using namespace std;

vector<Student> Classs::findStudentByName(string name){
	vector<Student> result;
	for (int i=0;i<this->students.size();i++){
		if (this->students[i].getName()==name)
			result.push_back(this->students[i]);
	}
	return result;
}

Student* Classs::findStudentByID(int ID){
	for (int i=0;i<this->students.size();i++){
		if (this->students[i].getID()==ID){
			return (&this->students[i]);
		}	
	}
	return nullptr;
}

void Classs::addStudent(Student student){
	// ham them 1 sinh vien vao lop 
	this->students.push_back(student);
	this->class_size++;
}

int extractID(string line){
	//ham trich xuat ID tu 1 row trong file csv
	int start=line.find(',');
	int end=line.find(',',start+1);
	return stoi(line.substr(start+1,end-start-1));
}

bool Classs::deleteStudent(int ID){
	// ham xoa 1 sinh vien co MSSV cho truoc
	string line;
	int id,check=0;
	string filename=path.substr(5);
	const char* datapath = filename.c_str();
	
	for (int i=0;i<students.size();i++){
		if (students[i].getID()==ID){
			this->students.erase(students.begin()+i);
			class_size--;
			check=1;
			break;
		}
	}
	
	if (check){
		ifstream file;
		ofstream newfile;
		
		file.open("register_data.csv");
		newfile.open("newfile1.csv");
		getline(file,line);
		newfile<<line<<endl;
		while(getline(file,line)){
			id=extractID(line);
			if (id!=ID) newfile<<line<<endl;
		}
		file.close();
		newfile.close();
		remove("register_data.csv");
		rename("newfile1.csv","register_data.csv");
		
	
		file.open(path.substr(5));
		newfile.open("newfile.csv");
		getline(file,line);
		newfile<<line<<endl;
		while(getline(file,line)){
			id=extractID(line);
			if (id!=ID) newfile<<line<<endl;
		}
		file.close();
		newfile.close();
		remove(datapath);
		rename("newfile.csv",datapath);
		
		return true;
	}
	return false;
}

void Classs::print(){
	// ham in danh sach lop
	cout<<"-----------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Class: "<<this->class_name<<endl<<"Size: "<<this->class_size<<endl;
	cout<<"-----------------------------------------------------------------------------------------------------"<<endl;
	cout<<"|"
		<<left
		<<setw(4)
		<<"#"<<"|"
		<<left
		<<setw(20)
		<<"Name"<<"|"
		<<left
		<<setw(12)
		<<"ID"<<"|"
		<<left
		<<setw(20)
		<<"Date of birth"<<"|"
		<<left
		<<setw(20)
		<<"Native place"<<"|"
		<<left
		<<setw(12)
		<<"Gender"<<"|"
		<<left
		<<setw(5)
		<<"GPA"<<"|"
		<<endl;
	cout<<"-----------------------------------------------------------------------------------------------------"<<endl;
	for (int i=0;i<this->students.size();i++){
		cout<<"|"
		<<left
		<<setw(4)
		<<i+1<<"|"
		<<left
		<<setw(20)
		<<this->students[i].getName()<<"|"
		<<left
		<<setw(12)
		<<this->students[i].getID()<<"|"
		<<left
		<<setw(20)
		<<this->students[i].getBirthday()<<"|"
		<<left
		<<setw(20)
		<<this->students[i].getNativePlace()<<"|"
		<<left
		<<setw(12)
		<<this->students[i].getGender()<<"|"
		<<left
		<<setw(5)
		<<fixed<<setprecision(2)<<this->students[i].getGPA()<<"|"
		<<endl;
	}
	cout<<"-----------------------------------------------------------------------------------------------------"<<endl;
	return;
}

vector<string> split(string s,string delimiter){
	//ham tach cac thanh phan trong 1 row cua file csv
    size_t pos_start=0,pos_end,delim_len=delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end=s.find(delimiter,pos_start))!=string::npos){
        token=s.substr(pos_start,pos_end-pos_start);
        pos_start=pos_end+delim_len;
        res.push_back (token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

void Classs::readCsv(){
	// doc file csv de co duoc cac thong tin co ban ve sv trong lop: ten, MSSV, que quan, gioi tinh, ngay sinh, muc canh cao hien tai
	vector<Student> list;
	int count=0;
	ifstream file(path);
	if (!file.is_open()) {
		cout<<"Error: Can not open file!";
		return;
	}
	string line;
	getline(file,line);
	while(getline(file,line)){
		vector<string> v=split(line,",");
		Student student(v[0],stoi(v[1]),v[2],v[3],v[4],stoi(v[5]),this->class_name);
		list.push_back(student);
		count++;
	}
	this->students=list;
	this->class_size=count;
	file.close();
}

void Classs::getRegisterInfoFromCsv(string path){
	//lay thong tin dang ki hp tu file csv
	ifstream file(path);
	if (!file.is_open()) {
		cout<<"Error: Can not open file!";
		return;
	}
	string line;
	getline(file,line);
	while(getline(file,line)){
		vector<string> v=split(line,",");
		Student* student=this->findStudentByID(stoi(v[1]));
		if (student==nullptr) continue;
		Subject subject=*this->program.findSubject(v[2]);
		(*student).addSubject(subject);
		(*student).addMid10(-1);
		(*student).addFinal10(-1);
		(*student).addFinal4(-1);
		(*student).addFinalChar("X");
	}
	file.close();
}

bool criterionName(Student s1, Student s2){
	//dinh nghia thu tu cua ten (Vietnam)
	string name1=s1.getName(),name2=s2.getName();
	size_t index1, index2, index3, index4;
	index1=name1.find(" ");
	index2=name1.rfind(" ");
	index3=name2.find(" ");
	index4=name2.rfind(" ");
	if (name1.substr(index2+1)!=name2.substr(index4+1))
		return name1.substr(index2+1)<name2.substr(index4+1);
	else if (name1.substr(0,index1)!=name2.substr(0,index3))
		return name1.substr(0,index1)<name2.substr(0,index3);
	else return name1.substr(index1,index2-index1)<name2.substr(index3,index4-index3);
}

bool criterionGPA(Student s1, Student s2){
	return s1.getGPA()>s2.getGPA();
}

void Classs::orderByGPA(){
	//sap xep theo GPA
	sort(this->students.begin(),this->students.end(),criterionGPA);
}
void Classs::orderByName(){
	//sap xep theo ten
	sort(this->students.begin(),this->students.end(),criterionName);
}



