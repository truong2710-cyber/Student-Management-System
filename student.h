#pragma once
#include <vector>
#include "subject.h"

using namespace std;

class Student{
	private:
		string name;
		int ID;
		string native_place;
		string birthday;
		string gender;
		string class_name;    // lop cua sinh vien
		vector<Subject> subjects;  // subjects of a student in this semester
		int academic_caution=0; // muc canh cao
		vector<float> scores_mid_10; // diem qua trinh cac mon thang 10
		vector<float> scores_final_10; // diem ck cac mon thang 10
		vector<float> scores_final_4; // diem tong ket cac mon thang 4
		vector<string> scores_final_char; // diem chu tong ket cac mon (A+,A,...)
		float GPA=-1;
		string rank="X";   // kem, yeu, TB yeu, TB, kha, gioi, xuat sac
		int pass=0;		// so tin chi qua
		int fail=0;	// so tin chi truot
		int fee=0;     // hoc phi ki nay
	public:
		Student(){
		}
		Student(string name, int ID, string birthday, string native_place, string gender, string class_name,vector<Subject> subjects, int cur_ac_level){
			// ham khoi tao
			this->name=name;
			this->ID=ID;
			this->birthday=birthday;
			this->native_place=native_place;
			this->gender=gender;
			this->class_name=class_name;
			this->subjects=subjects;
			this->academic_caution=cur_ac_level;
			this->scores_mid_10.resize(subjects.size(),-1);
			this->scores_final_10.resize(subjects.size(),-1);
			this->scores_final_4.resize(subjects.size(),-1);
			this->scores_final_char.resize(subjects.size(),"X");
			this->rank="X";
		}  
		Student(string name, int ID, string birthday, string native_place, string gender, int cur_ac_level,string class_name){
			this->name=name;
			this->ID=ID;
			this->birthday=birthday;
			this->native_place=native_place;
			this->gender=gender;
			this->academic_caution=cur_ac_level;
			this->class_name=class_name;
			this->rank="X";
		}
		string getName(){
			return this->name;
		}
		void setName(string name){
			this->name=name;
		}
		int getID(){
			return this->ID;
		}
		string getBirthday(){
			return this->birthday;
		}
		void setBirthday(string birthday){
			this->birthday=birthday;
		}
		string getNativePlace(){
			return this->native_place;
		}
		void setNativePlace(string native_place){
			this->native_place=native_place;
		}
		string getGender(){
			return this->gender;
		}
		void setGender(string gender){
			this->gender=gender;
		}
		string getClassName(){
			return this->class_name;
		}
		void setClassName(string class_name){
			this->class_name=class_name;
		}
		vector<Subject> getSubjects(){
			return this->subjects;
		}
		int getAcademicCaution(){
			return this->academic_caution;
		}
		vector<float> getScoresMid10(){
			return this->scores_mid_10;
		}
		vector<float> getScoresFinal10(){
			return this->scores_final_10;
		}
		vector<float> getScoresFinal4(){
			return this->scores_final_4;
		}
		vector<string> getScoresFinalChar(){
			return this->scores_final_char;
		}
		float getGPA(){
			return this->GPA;
		}
		string getRank(){
			return this->rank;
		}
		int getPass(){
			return this->pass;
		}
		int getFail(){
			return this->fail;
		}
		int getTotalCredit(){
			int count=0;
			for (int i=0;i<this->subjects.size();i++){
				count+=this->subjects[i].getCredit();
			}
			return count;
		}
		void addSubject(Subject subject);
		void addMid10(float score);
		void addFinal10(float score);
		void addFinal4(float score);
		void addFinalChar(string score);
		int getFee();
		void update_scores(vector<float> scores_mid_10, vector<float> scores_final_10);               
		// nhap diem qt va ck, dong thoi tinh toan diem thang 4, diem chu, gpa, muc canh cao, xep hang, tin chi qua, khong qua
		void print_info();		// in ra ttin sv
};
