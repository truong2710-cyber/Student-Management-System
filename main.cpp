#include <iostream>
#include <vector>
#include "student.h"
#include "subject.h"
#include "classs.h"
using namespace std;


int main(int argc, char** argv) {
	//test
	/*
	vector<Subject> v;
	vector<Student> vs;
	Subject PhysicsI("Physics I","PH1110",2,5);
	Subject PhysicsII("Physics II","PH1120",2,5);
	Subject PhysicsIII("Physics III","PH1130",2,5);
	v.push_back(PhysicsI);
	v.push_back(PhysicsII);
	v.push_back(PhysicsIII);
	Student s1("ABC",20190000,"Vietnam","male","IoT-01-K64",v,1);
	Student s2("BCD",20190001,"Vietnam","female","IoT-01-K64",v,2);
	vs.push_back(s1);
	vs.push_back(s2);
	cout<<s1.getName()<<endl;
	cout<<s1.getClassName()<<endl;
	cout<<s2.getAcademicCaution()<<endl;
	cout<<s1.getAcademicCaution()<<endl;
	Classs cl1(vs);
	cl1.deleteStudent(20190001);
	*/
	Classs cl1("IoT-K64");
	cl1.readCsv("data.csv");
	cl1.print();
	return 0;
}
