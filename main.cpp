#include <iostream>
#include <vector>
#include "student.h"
#include "subject.h"
#include "classs.h"
#include "program.h"
#include <memory>
#include <fstream>
#include <windows.h>
using namespace std;
int class_index=-1;

Program initProgram(string name, string path){
	Program program(name);
	program.readCsv(path);
	return program;
}

vector<Classs> initClasses(Program program){
	vector<Classs> classes;
	Classs cl1("ET-E9",program,"data/basic_data.csv");
	cl1.readCsv(); 
	cl1.getRegisterInfoFromCsv("data/register_data.csv");
	classes.push_back(cl1);
	
	Classs cl2("ET1-01",program,"data/basic_data2.csv");
	cl2.readCsv(); 
	cl2.getRegisterInfoFromCsv("data/register_data.csv");
	classes.push_back(cl2);
	
	return classes;
}

void printClassInfo(vector<Classs> classes){
	string name;
	cout<<"Class list:"<<endl;
	int i=1;
	for (Classs classs:classes){
		cout<<i++<<". "<<classs.getName()<<endl;
	}
	cout<<"Enter class name: ";
	cin.ignore();
	getline(cin,name);
	while(true){
		bool found=false;
		for (Classs classs:classes){
			if (classs.getName()==name){
				int i;
				cout<<"Choose sort method(1/2):"<<endl;
				cout<<"1. By name"<<endl;
				cout<<"2. By GPA"<<endl;
				do{
					cin>>i;
					if (i!=1 && i!=2) 
						cout<<"Invalid input! Please choose again: ";
				} while(i!=1 && i!=2);
				if (i==1) classs.orderByName();
				if (i==2) classs.orderByGPA();
				classs.print();
				found=true;
			}
		}
		if (!found)
			cout<<"Error: Can not find class "<<name<<"!"<<endl;
		cout<<"Enter again (or enter 'exit' to quit): ";
		if (found) cin.ignore();
		getline(cin,name);
		if (name=="exit"){
			cout<<endl;
			return;
		} 
	}
}

vector<Student> searchByName(vector<Classs> classes, string name){
	vector<Student> result;
	for (Classs classs:classes){
		vector<Student> temp=classs.findStudentByName(name);
		result.insert(result.end(),temp.begin(),temp.end());
	}
	return result;
}

Student* searchByID(vector<Classs> &classes, int ID){
	for (int i=0;i<classes.size();i++){
		Student* temp=classes[i].findStudentByID(ID);
		if (temp!=nullptr){
			class_index=i;
			return temp;
		}
	}
	return nullptr;
}

void searchStudentInfo(vector<Classs> classes){
	vector<Student> result;
	cout<<"Choose search method (1/2):"<<endl;
	cout<<"1. Search by name"<<endl;
	cout<<"2. Search by ID"<<endl;
	int i;
	do{
		cin>>i;
		if (i!=1 && i!=2) 
			cout<<"Invalid input! Please choose again: ";
	} while(i!=1 && i!=2);
	if (i==1){
		string name;
		cout<<"Enter full name: ";
		cin.ignore();
		getline(cin,name);
		vector<Student> result=searchByName(classes,name);
		if (result.size()==0){
			cout<<"No result found!"<<endl;
			return;
		}
		for (int i=0;i<result.size();i++){
			result[i].print_info();
		}
	}
	if (i==2){
		int ID;
		cout<<"Enter ID: ";
		cin>>ID;
		Student* result=searchByID(classes,ID);
		if (result!=nullptr){
			(*result).print_info();
			return;
		}
		cout<<"No result found!"<<endl;
	}
}

void updateScore(vector<Classs> &classes){
	int ID;
	string code;
	vector<float> mid,final;
	string temp;
	cout<<"Enter ID: ";
	cin>>ID;
	cin.ignore();
	Student* student=searchByID(classes,ID);
	if (student==nullptr){
		cout<<"Can not find student with ID "<<ID<<endl;
		return;
	}
	vector<float> cur_mid=(*student).getScoresMid10(), cur_final=(*student).getScoresFinal10();
	
	for (int i=0;i<(*student).getSubjects().size();i++){
		if (cur_mid[i]!=-1 && cur_final[i]!=-1){
			mid.push_back(-1);
			final.push_back(-1);
			continue;
		}
		cout<<(*student).getSubjects()[i].getCode()<<": "<<(*student).getSubjects()[i].getName()<<endl;
		if (cur_mid[i]==-1){
			cout<<"Enter mid-term score: ";
			getline(cin,temp);
			if (temp!="")
				mid.push_back(stof(temp));
			else mid.push_back(-1);
		}
		else mid.push_back(-1);
		if (cur_final[i]==-1){
			cout<<"Enter final exam score: ";
			getline(cin,temp);
			if (temp!="")
				final.push_back(stof(temp));
			else final.push_back(-1);
		}
		else final.push_back(-1);
	}
	(*student).update_scores(mid,final);
	cout<<"Score updated successfully!"<<endl;
	(*student).print_info();
}

void updateInfo(vector<Classs> &classes){
	int ID,id;
	float temp;
	string line,name,birthday,native_place,gender;
	cout<<"Enter ID: ";
	cin>>ID;
	
	Student* student=searchByID(classes,ID);
	if (student==nullptr){
		cout<<"Can not find student with ID "<<ID<<endl;
		return;
	}
	cout<<"Update personal information for student with ID "<<ID<<":"<<endl;
	cout<<"Name: "; 
	cin.ignore();
	getline(cin,name);
	(*student).setName(name);
	cout<<"Date of birth: "; 
	getline(cin,birthday);
	(*student).setBirthday(birthday);
	cout<<"Native place: "; 
	getline(cin,native_place);
	(*student).setNativePlace(native_place);
	cout<<"Gender: "; 
	getline(cin,gender);
	(*student).setGender(gender);
	
	ifstream file;
	ofstream newfile;
		
	file.open("register_data.csv");
	newfile.open("newfile1.csv");
	getline(file,line);
	newfile<<line<<endl;
	while(getline(file,line)){
		id=extractID(line);
		if (id!=ID) newfile<<line<<endl;
		else newfile<<name<<line.substr(line.find(','))<<endl;
	}
	file.close();
	newfile.close();
	remove("register_data.csv");
	rename("newfile1.csv","register_data.csv");
	
	string filename=classes[class_index].getPath().substr(5);
	const char* datapath = filename.c_str();
	
	file.open(datapath);
	newfile.open("newfile.csv");
	getline(file,line);
	newfile<<line<<endl;
	while(getline(file,line)){
		id=extractID(line);
		if (id!=ID) newfile<<line<<endl;
		else newfile<<name<<","<<id<<","<<birthday<<","<<native_place<<","<<gender<<line.substr(line.rfind(','))<<endl;
	}
	file.close();
	newfile.close();
	remove(datapath);
	rename("newfile.csv",datapath);
	
	cout<<"Information updated successfully!"<<endl;
	(*student).print_info();
}

void deleteStudent(vector<Classs> &classes){
	int ID;
	cout<<"Enter ID: ";
	cin>>ID;
	
	for (int i=0;i<classes.size();i++){
		if (classes[i].deleteStudent(ID)){
			cout<<"Student with ID "<<ID<<" is removed successfully!"<<endl<<endl;
			return;
		}
	}
	cout<<"Can not find student with ID "<<ID<<endl<<endl;
}

bool checkDuplicate(vector<Classs> &classes, int ID){
	Student* student=searchByID(classes,ID);
	if (student!=nullptr) 
		return true;
	return false;
}

Classs* findClass(vector<Classs> &classes, string name){
	for (int i=0;i<classes.size();i++){
		if (classes[i].getName()==name)
			return &classes[i];
	}
	return nullptr;
}

void addStudent(vector<Classs> &classes,Program program){
	int ID,academic_caution_level,num_subjects;
	string name,birthday,native_place,gender,code,class_name;
	vector<Subject> subjects;
	cout<<"Enter ID: ";
	do{
		cin>>ID;
		if (checkDuplicate(classes,ID))
			cout<<"ID already exists! Please enter another ID: ";
	} while(checkDuplicate(classes,ID));
	cin.ignore();
	cout<<"Class name: ";
	do{
		getline(cin,class_name);
		if (findClass(classes,class_name)==nullptr)
			cout<<"Can not find class "<<class_name<<"! Please enter again: ";
	} while (findClass(classes,class_name)==nullptr);
	Classs* classs=findClass(classes,class_name);
	cout<<"Name: ";
	getline(cin,name);
	cout<<"Date of birth: ";
	getline(cin,birthday);
	cout<<"Native place: ";
	getline(cin,native_place);
	cout<<"Gender: ";
	getline(cin,gender);
	cout<<"Academic caution level: ";
	cin>>academic_caution_level;
	cout<<"Enter number of subjects: ";
	cin>>num_subjects;
	cout<<"Enter subject codes: "<<endl;
	cin.ignore();
	
	ofstream regfile;
	regfile.open("register_data.csv",ios_base::app);
	if (!regfile.is_open()) {
		cout<<"Error: Can not open file!";
		return;
	}
	for (int i=0;i<num_subjects;i++){
		cout<<i+1<<". ";
		do{
			getline(cin,code);
			if (program.findSubject(code)==nullptr)
				cout<<"Error: Can not find subject with code "<<code<<". Please enter again: "<<endl;
		} while(program.findSubject(code)==nullptr);
		Subject sub=*program.findSubject(code);
		subjects.push_back(sub);
		regfile<<name<<","<<ID<<","<<code<<","<<sub.getName()<<","<<sub.getCredit()<<endl;
	}
	regfile.close();
	Student student(name,ID,birthday,native_place,gender,class_name,subjects,academic_caution_level);
	(*classs).addStudent(student);
	ofstream file;
	string filename=(*classs).getPath().substr(5);
	const char* datapath = filename.c_str();
	file.open(datapath,ios_base::app);
	if (!file.is_open()) {
		cout<<"Error: Can not open file!";
		return;
	}
	file<<name<<","<<ID<<","<<birthday<<","<<native_place<<","<<gender<<","<<academic_caution_level<<endl;
	file.close();
	cout<<"Student with ID "<<ID<<" is added to class "<<class_name<<" successfully!"<<endl;
	(*classs).print();
}

void printMenu(){
	cout<<"+--------------------------------------------------------------------+"<<endl;
	cout<<"|                     STUDENT MANAGEMENT SYSTEM                      |"<<endl;
	cout<<"+--------------------------------------------------------------------+"<<endl;
	cout<<"|1. Print class information                                          |"<<endl;
	cout<<"|2. Print education program                                          |"<<endl;
	cout<<"|3. Search student information                                       |"<<endl;
	cout<<"|4. Update student's score                                           |"<<endl;
	cout<<"|5. Update student's personal information                            |"<<endl;
	cout<<"|6. Add a student to system                                          |"<<endl;
	cout<<"|7. Delete a student from system                                     |"<<endl;
	cout<<"|8. Clear console                                                    |"<<endl;
	cout<<"|9. Exit                                                             |"<<endl;
	cout<<"+--------------------------------------------------------------------+"<<endl;           
}

int main(int argc, char** argv) {
	//test
	int choice;
	Program program=initProgram("ET Program","data/education_program.csv");
	vector<Classs> classes=initClasses(program);
	if (!SetCurrentDirectory(".\\data")) cout<<"Error! Can not find data!"<<endl;
	while (true){
		printMenu();
		cout<<"Please enter your choice: ";
		do{
			cin>>choice;
			if (choice!=1 && choice!=2 && choice!=3 && choice !=4 && choice!=5 && choice!=6 && choice!=7 && choice!=8 && choice!=9)
				cout<<"Invalid input! Please enter again: ";
		} while (choice!=1 && choice!=2 && choice!=3 && choice !=4 && choice!=5 && choice!=6 && choice!=7 && choice!=8 && choice!=9);
		switch(choice){
			case 1:
				printClassInfo(classes);
				break;
			case 2:
				program.print();
				break;
			case 3:
				searchStudentInfo(classes);
				break;
			case 4:
				updateScore(classes);
				break;
			case 5:
				updateInfo(classes);
				break;
			case 6:
				addStudent(classes,program);
				break;
			case 7:
				deleteStudent(classes);
				break;
			case 8:
				system("cls");
				break;
			case 9:
				cout<<"Bye! See ya later!";
				return 0;
				break;
		}
	}
	return 0;
}
