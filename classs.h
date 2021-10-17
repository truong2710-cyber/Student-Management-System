#pragma once
#include <vector>
#include "student.h"
using namespace std;

class Classs{
	private:
		vector<Student> students;   // danh sach sinh vien trong lop
		int class_size=0;			// si so lop
		string class_name;
	public:
		Classs(string name){
			class_name=name;
		}
		Classs(string name,vector<Student> students){
			this->students=students;
			class_size=students.size();
			class_name=name;
		}
		int getSize(){
			return this->class_size;	
		}
		vector<Student> getStudents(){
			return this->students;
		}
		string getName(){
			return this->class_name;
		}
		void addStudent(Student student);
		void deleteStudent(int ID);
		void print();
		void readCsv(string path);
};
