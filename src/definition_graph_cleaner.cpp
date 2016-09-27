#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include <time.h>

using namespace std;


int main()
{
	int i=0,j=0;
	std::string line;
	std::string temp;
	std::ofstream fout("Definition_graph_2.txt");
	std::ifstream file("Definitions_graph_1.txt");
	//char *sp;
	while(!file.eof())
	{
		getline(file,temp);
		line = temp;
		for(i=0; line[i]!='\0'; ++i)
    	{
        	while (!((line[i]>='a'&&line[i]<='z') || (line[i]>='A'&&line[i]<='Z' || line[i]=='\0' || ((line[i]==',')&&(line[i+1]==' ')) )))
        	{
            	for(j=i;line[j]!='\0';++j)
        	    {
            	    line[j]=line[j+1];
        	    }
        	    line[j]='\0';
        	}
    	}
    	for(i=0;i<=j;i++)
    		temp[i]=line[i];
    	//temp = line;
    	fout<<temp<<endl;

	}
	return 0;
}