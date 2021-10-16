#pragma once
#include <vector>
#include "student.h"
using namespace std;

class Classs{
	private:
		vector<Student> students;   // danh sach sinh vien trong lop
		int class_size=0;			// si so lop
	public:
		Classs(vector<Student> students){
			this->students=students;
			class_size=students.size();
		}
		void addStudent(Student student);
		void deleteStudent(int ID);
		void print();
};
