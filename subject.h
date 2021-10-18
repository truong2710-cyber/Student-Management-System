#pragma once
#include <string>
using namespace std;

class Subject{
	private:
		string name;   // ten hoc phan
		string code;   // ma hoc phan
		int credit;   // tin chi hoc phan
		int fee_credit;		// tin chi hoc phi
		float mid_term_weight; // trong so qua trinh
	public:
		Subject(string name, string code, int credit, int fee_credit, float mid_term_weight){
			this->name=name;
			this->code=code;
			this->credit=credit;
			this->fee_credit=fee_credit;
			this->mid_term_weight=mid_term_weight;
		}
		string getName(){
			return this->name;
		}
		string getCode(){
			return this->code;
		}
		int getCredit(){
			return this->credit;
		}
		int getFeeCredit(){
			return this->fee_credit;
		}
		float getWeight(){
			return this->mid_term_weight;
		}
};
