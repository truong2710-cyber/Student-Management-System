#include <iostream>
#include <vector>
#include "student.h"
#include "subject.h"
#include "classs.h"
using namespace std;


int main(int argc, char** argv) {
	//test
	
	vector<Subject> v;
	vector<Student> vs;
	Subject PhysicsI("Physics I","PH1110",2,5,0.3);
	Subject PhysicsII("Physics II","PH1120",2,5,0.3);
	Subject PhysicsIII("Physics III","PH1130",2,5,0.3);
	v.push_back(PhysicsI);
	v.push_back(PhysicsII);
	v.push_back(PhysicsIII);
	Student s1("Vo Van A",20191234,"14/5/2001","Ha Noi","male","IT1",v,2);
	Student s2("Bui Thanh C",20190001,"29/9/2001","Hoa Binh","female","IoT-01-K64",v,2);
	s1.print_info();
	vs.push_back(s1);
	vs.push_back(s2);
	/*
	cout<<s1.getName()<<endl;
	cout<<s1.getClassName()<<endl;
	cout<<s2.getAcademicCaution()<<endl;
	cout<<s1.getAcademicCaution()<<endl;
	*/
	Classs cl1("IoT-01-K64",vs);
	cl1.deleteStudent(20190001);
	
	Classs cl2("IoT-K64");
	cl2.readCsv("data.csv");
	cl2.print();
	return 0;
}
