#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include <time.h>

using namespace std;

int main()
{
	int beginIdx,endIdx,temp;
	std::string line;
	std::string topic;
	std::string temp_line;
	std::ifstream file("tmp.txt");
	std::ofstream fout("Definitions_graph_1.txt");
	while(getline(file,line))
	{
		if(line.find(':')>500)
			continue;
		if((line.find("#REDIRECT")<500)||(line.find("#Redirect")<500))
			continue;
		temp = line.find(':');
		/*topic = line.substr(0,temp);
		beginIdx = 0;
		while(topic.find('/')<topic.find(':'))
		{
			if(topic.find('/',beginIdx+1)<50)
			{
				fout<<line.substr(beginIdx,line.find('/',beginIdx+1))<<": ";
				beginIdx = line.find('/', beginIdx+1);
			}
			else 
				fout<<topic": ";
		}*/
		fout<<line.substr(0,temp)<<": ";		
		endIdx = line.find(' ');
		beginIdx = endIdx+1;
		line = line.substr(beginIdx,line.length()-beginIdx);
		while(1)
		{
			temp_line = line.substr(0,line.find(' '));
			if((temp_line.find("/FW")!=string::npos)||(temp_line.find("/JJ")!=string::npos)||(temp_line.find("/JJR")!=string::npos)||(temp_line.find("/JJS")!=string::npos)||(temp_line.find("/NN")!=string::npos)||(temp_line.find("/NNS")!=string::npos)||(temp_line.find("/NNP")!=string::npos)||(temp_line.find("/NNPS")!=string::npos))
			{
				fout<<temp_line.substr(0,temp_line.find('/'))<<", ";
			}
			line = line.substr(line.find(' ')+1);
			if(line.find(' ')>500)
			{
				break;
			}
		}
		fout<<endl;
	}
	return 0;
}