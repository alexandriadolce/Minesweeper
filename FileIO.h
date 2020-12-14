#pragma once
#include <string>
#include <fstream>
using namespace std;
class FileIO
{ 
private:
	string fileBase;
	ofstream outputFile;
	ifstream inputFIle;
public:
	FileIO(string = "scores");
};

