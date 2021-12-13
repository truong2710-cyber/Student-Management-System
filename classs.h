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
		string path;
	public:
		Classs(string name,Program program,string path){
			class_name=name;
			this->program=program;
			this->path=path;
		}
		Classs(string name,vector<Student> students,Program program,string path){
			this->students=students;
			class_size=students.size();
			class_name=name;
			this->program=program;
			this->path=path;
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
		bool deleteStudent(int ID);
		void print();
		void readCsv();
		Student* findStudentByID(int ID);
		vector<Student> findStudentByName(string name);
		void orderByGPA();
		void orderByName();
		void getRegisterInfoFromCsv(string path);
		string getPath(){
			return this->path;
		}
		void setPath(string path){
			this->path=path;
		}
};

vector<string> split (string s, string delimiter); 
int extractID(string line);
