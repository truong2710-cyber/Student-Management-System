#pragma once
#include "subject.h"
#include <vector>
#include <string>

class Program{
	private:
		vector<Subject> subjects;
		string name;
	public:
		Program(string name);
		void print();
		void readCsv(string path);
};
