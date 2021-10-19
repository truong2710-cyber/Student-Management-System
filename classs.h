#pragma once
#include <vector>
#include <memory>
#include "student.h"
#include "program.h"
using namespace std;

class Classs{
	private:
		vector<Student> students;   // danh sach sinh vien trong lop
		int class_size=0;			// si so lop
		string class_name;
		Program program;
	public:
		Classs(string name,Program program){
			class_name=name;
			this->program=program;
		}
		Classs(string name,vector<Student> students,Program program){
			this->students=students;
			class_size=students.size();
			class_name=name;
			this->program=program;
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
		Student* findpStudentByID(int ID);
		pair<Student,bool> findStudentByID(int ID);
		vector<Student> findStudentByName(string name);
		void orderByGPA();
		void orderByName();
		void getRegisterInfoFromCsv(string path);
};

vector<string> split (string s, string delimiter); 
