#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include <time.h>

using namespace std;

int main()
{
	string line;
	
	std::ifstream file("Definitions.txt");
	std::ofstream fout("Definitions_clean.txt");

	/*std::ifstream file("Infobox.txt");
	std::ofstream fout("Infobox_clean.txt");*/

	size_t beginIdx=0,endIdx=0;

	while(getline(file,line))
	{
		
		while(line.find("&quot;")!=string::npos)
		{
			beginIdx = line.find("&quot;");
			line[beginIdx] = ' ';
			line[beginIdx+1] = ' ';
			line[beginIdx+2] = ' ';
			line[beginIdx+3] = ' ';
			line[beginIdx+4] = ' ';
			line[beginIdx+5] = '\"';
		}

		while(line.find("&lt;")!=string::npos)
		{
			beginIdx = line.find("&lt;");
			line[beginIdx] = ' ';
			line[beginIdx+1] = ' ';
			line[beginIdx+2] = ' ';
			line[beginIdx+3] = '<';
		}

		
		while(line.find("&gt;")!=string::npos)
		{
			beginIdx = line.find("&gt;");
			line[beginIdx] = '>';
			line[beginIdx+1] = ' ';
			line[beginIdx+2] = ' ';
			line[beginIdx+3] = ' ';
		}

		
		while(line.find("&amp;")!=string::npos)
		{
			beginIdx = line.find("&amp;");
			line[beginIdx] = ' ';
			line[beginIdx+1] = ' ';
			line[beginIdx+2] = ' ';
			line[beginIdx+3] = ' ';
			line[beginIdx+4] = '&';
		}

		while(line.find("\t|")!=string::npos)
		{
			beginIdx = line.find("\t|");
			line[beginIdx] = '\t';
			line[beginIdx+1] = ' ';
		}

		if(line.length()<2)
		{
			fout<<endl;
			continue;
		}
		fout<<line[0];
		for(int i=1;i<line.length();i++)
		{
			//cout<<line<<endl;
			if(line[i]!=' '){
				fout<<line[i];
				//k++;
			}
			if(line[i]==' ')
			{
				if(line[i-1]!=' ')
				{
					fout<<line[i];
					//k++;
				}
			}
		}
		fout<<endl;
	}
	return 0;
}