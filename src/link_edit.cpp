#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include <time.h>

int main()
{
	std::string sentence;
	std::ifstream file("Links.txt");
	std::ofstream fout("Links_clean.txt");
	while(getline(file,sentence)){
		if(sentence.find("Wikipedia")!=std::string::npos)
			continue;
		for(int i=0; i<sentence.size(); i++)
			if(!(sentence[i]=='{' || sentence[i]=='}' || sentence[i]=='[' || sentence[i]==']'))
				fout<<sentence[i];
		fout<<std::endl;
	}
	return 0;
}