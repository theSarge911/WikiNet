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
	int k=0;
	
	std::ifstream file("Definitions_clean.txt");
	std::ofstream fout("Definitions_clean2.txt");

	/*std::ifstream file("Infobox.txt");
	std::ofstream fout("Infobox_clean.txt");*/

	size_t beginIdx=0,endIdx=0;
	//line = "Wikipedia:Administrators: :''WP:A redirects here. You may be looking for [[Wikipedia:Announcements]]'' {{shortcut|[[WP:ADMIN]] <br /> [[WP:SYSOP]] <br /> [[WP:A]]}} [[File:Wikipedia Administrator.svg|thumbnail|This is the symbol of a Wikipedia administrator. It shows the site's logo with a [[mop]], as administrators are often linked to [[janitor]]s.]] '''Administrators''', also called '''admins''' or '''sysops''' ('''sys'''tem '''op'''erators), are users who can use special [[Special:ListGroupRights/Admin|tools]] that help keep Wikipedia running smoothly. They can use these tools because they are trusted by the community, but this does not make them better or more important than anybody else. The opinion of an administrator, for example, should not be counted as more important than the opinion of a person who chooses to change Wikipedia with an IP address just because they have administrator rights.";
	while(getline(file,line))
	{
		//remove file:,image:,tags,[[INFOBOX]] }}
		if(line.find("Category:")<10||line.find("Template:")<10||line.find("Wikipedia")<10||line.find("MediaWiki")<10){
			continue;
			k=1;
		}

		if(k==1)
		{
			continue;
			k=0;
		}

		while(line.find("[[INFOBOX]] }}")!=string::npos)
		{
			beginIdx = line.find("[[INFOBOX]] }}");
			for(int i=0;i<=13;i++)
			{
				line[beginIdx+i] = ' ';
				//cout<<"k";
			}
		}

		while(line.find("<")<10000&&line.find(">",line.find("<")+1)<10000)
		{
			beginIdx = line.find("<");
			endIdx = line.find(">",beginIdx+1);
			
			for(int i=beginIdx;i<=endIdx;i++)
			{
				line[i] = ' ';
			}
			//char c =getchar();
		}

		while(line.find("[[Image")<10000&&line.find("]]",line.find("[[Image")+1)<10000)
		{
			beginIdx = line.find("[[Image");
			endIdx = line.find("]]",beginIdx+1)+1;
			
			for(int i=beginIdx;i<=endIdx;i++)
			{
				line[i] = ' ';
			}
			//char c =getchar();
		}

		while(line.find("[[image")<10000&&line.find("]]",line.find("[[image")+1)<10000)
		{
			beginIdx = line.find("[[image");
			endIdx = line.find("]]",beginIdx+1)+1;
			
			for(int i=beginIdx;i<=endIdx;i++)
			{
				line[i] = ' ';
			}
			//char c =getchar();
		}

		while(line.find("[[File")<10000&&line.find("]]",line.find("[[File")+1)<10000)
		{
			beginIdx = line.find("[[File");
			endIdx = line.find("]]",beginIdx+1)+1;
			
			for(int i=beginIdx;i<=endIdx;i++)
			{
				line[i] = ' ';
			}
			//char c =getchar();
		}

		while(line.find("[[Category")<10000&&line.find("]]",line.find("[[Category")+1)<10000)
		{
			beginIdx = line.find("[[Category");
			endIdx = line.find("]]",beginIdx+1)+1;
			
			for(int i=beginIdx;i<=endIdx;i++)
			{
				line[i] = ' ';
			}
			//char c =getchar();
		}

		while(line.find("[http:")<10000)
		{
			beginIdx = line.find("[http:");
			
			
			for(int i=beginIdx;;i++)
			{
				if(line[i]==' ')
					break;
				line[i] = ' ';
			}
			//char c =getchar();
		}

		while(line.find("{{")<10000&&line.find("}}",line.find("{{")+1)<10000)
		{
			beginIdx = line.find("{{");
			endIdx = line.find("}}",beginIdx+1)+1;
			
			for(int i=beginIdx;i<=endIdx;i++)
			{
				line[i] = ' ';
			}
			//cout<<'k'<<endl;
		}

		while(line.find("[[")<10000)
		{
			beginIdx = line.find("[[");
			//endIdx = line.find("]]",beginIdx+1)+1;
			
			line[beginIdx] = ' ';
			line[beginIdx + 1] = ' ';
			//char c =getchar();
		}

		while(line.find("]]")<10000)
		{
			beginIdx = line.find("]]");
			//endIdx = line.find("]]",beginIdx+1)+1;
			
			line[beginIdx] = ' ';
			line[beginIdx + 1] = ' ';
			//char c =getchar();
		}

		while(line.find("{{")<10000)
		{
			beginIdx = line.find("{{");
			//endIdx = line.find("]]",beginIdx+1)+1;
			
			line[beginIdx] = ' ';
			line[beginIdx + 1] = ' ';
			//char c =getchar();
		}

		while(line.find("}}")<10000)
		{
			beginIdx = line.find("}}");
			//endIdx = line.find("]]",beginIdx+1)+1;
			
			line[beginIdx] = ' ';
			line[beginIdx + 1] = ' ';
			//char c =getchar();
		}

		if(line.length()>2)
		{
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
			fout<<endl<<endl;
		}
		
		
	}
	return 0;
}