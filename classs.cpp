#include "classs.h"

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
			break;
		}
	}
}

void Classs::print(){
	// ham in danh sach lop
	return;
}

