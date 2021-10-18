#include <iostream>
#include <vector>
#include "student.h"
#include "subject.h"
#include "classs.h"
#include "program.h"
using namespace std;


int main(int argc, char** argv) {
	//test
	Program program("Talented Program IT");
	program.readCsv("data/education_program.csv");
	program.print(); // khoi tao 1 chuong trinh dao tao (vd CTTN IT)
	
	
	Classs cl2("CTTN-IT-K64",program);
	cl2.readCsv("data/basic_data.csv"); // doc danh sach lop (cac thong tin co ban)
	cl2.orderByName(); // sap xep theo ten
	cl2.print();
	cl2.getRegisterInfoFromCsv("data/register_data.csv"); // lay thong tin dang ki lop o file csv
	//cout<<cl2.getStudents()[1].getSubjects().size();
	
	return 0;
}
