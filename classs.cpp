#include "classs.h"
#include "student.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void Classs::addStudent(Student student){
	// ham them 1 sinh vien vao lop 
	this->students.push_back(student);
}

void Classs::deleteStudent(int ID){
	// ham xoa 1 sinh vien co MSSV cho truoc
	for (int i=0;i<students.size();i++){
		if (students[i].getID()==ID){
			this->students.erase(students.begin()+i);
			class_size--;
			return;
		}
	}
	cout<<"Error: Can not find student with ID "<<ID<<endl;
}

void Classs::print(){
	// ham in danh sach lop
	cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"Class: "<<this->class_name<<endl;
	cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"|"
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
		<<setw(22)
		<<"Academic caution level"<<"|"
		<<endl;
	cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
	for (int i=0;i<this->students.size();i++){
	cout<<"|"
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
		<<setw(22)
		<<this->students[i].getAcademicCaution()<<"|"
		<<endl;
	}
	cout<<"----------------------------------------------------------------------------------------------------------------";
	return;
}

vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void Classs::readCsv(string path){
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
		Student student(v[0],stoi(v[1]),v[2],v[3],v[4],stoi(v[5]));
		list.push_back(student);
		count++;
	}
	this->students=list;
	this->class_size=count;
}
