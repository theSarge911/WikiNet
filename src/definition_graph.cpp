#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include <time.h>

using namespace std;

std::string extract_keys(std::string text)
{
	std::string beginTag = "[[";
	std::string endTag = "]]";
	std::string null = "";

	std::size_t beginIdx = 0;
	std::size_t endIdx = 0;
		
	beginIdx = text.find(beginTag);
	endIdx = text.find(endTag);

	
	return null;
}

int main()
{
	int beginIdx,endIdx,id=0,temp;
	std::string line;
	std::string null = "";
	std::ifstream file("Definitions_POS.txt");
	std::ofstream fout("Definitions_graph.txt");

	while(getline(file,line))
	{
		temp = line.find(':')+3;
		fout<<line.substr(0,temp-3)<<": ";
		beginIdx = temp;
		endIdx = line.find("/NNP",temp);
		while(endIdx!=std::string::npos)
		{
			id = endIdx;
			while(1)
			{
				id--;
				if(line[id] == ' '){
					beginIdx = id;
					break;
				}
				if(id<0)
					break;				
			}
			if(beginIdx>5000||endIdx>5000)
				break;
			fout<<line.substr(beginIdx,endIdx-beginIdx)<<", ";
			endIdx = line.find("/NNP",endIdx+1);
		}

		fout<<endl;
		//char c = getchar();
	}
	return 0;
}