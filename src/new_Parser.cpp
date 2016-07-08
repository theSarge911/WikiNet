#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>
#include <time.h>

std::string extract_Def(std::string text);
std::string extract_Cat(std::string text);
std::string extract_info(std::string text);
std::string extract_links(std::string text);
std::string check_Tag(std::string text, std::string tag);

using namespace std;

int main()
{
	clock_t startTime = clock();

	std::string line;
	std::string null = "";
	std::ifstream file("../wikidump/wiki.xml");
	//std::ifstream file("wiki_test.xml");
	std::ofstream fout("Output.txt");
	std::ofstream fdef("Definitions.txt");
	std::ofstream fcat("Category.txt");
	std::ofstream finfo("Infobox.txt");
	std::ofstream flink("Links.txt");
	if (!file.is_open())
	{
		std::cout<<"Unable to open file"<<std::endl;
	}

	std::string tag[5];
	
	tag[0] = "<title>";
	tag[1] = "<sitename>";
	tag[2] = "<id>";
	tag[3] = "<username>";
	tag[4] = "<parentid>";

	static int i=0,k=0,l=0,length=0;
		
	while(getline(file,line))
	{
		
		static std::string tmp = "",tmp1 = "";
		static std::string title = "",title_temp = "";		
		
		//Code to get the tags.
		for(int j=0;j<5;j++)
		{
			tmp = tag[j];
			tmp1 = check_Tag(line,tmp);
			if(tmp==tag[0] && tmp1!="")
			{
				i++;
				fout<<std::endl;
				fout<<"Page Number :"<<i<<std::endl;
				fout<<tmp.substr(1,tmp.length()-2)<<": "<<tmp1<<std::endl;
				title = tmp1;
			}
			else if(tmp1 != "")
				fout<<tmp.substr(1,tmp.length()-2)<<": "<<tmp1<<std::endl;

		}


		//Code to get hyperlinks
		if(null.compare(extract_links(line))!=0)
		{
			if(title.compare(title_temp)!=0)
			{
				title_temp = title;
				if(l==0){
					flink<<title<<":  "<<extract_links(line)<<",  ";
					l=1;
				}
				else
					flink<<std::endl<<title<<":  "<<extract_links(line)<<",  ";
			}
			else
				flink<<extract_links(line)<<",  ";
		}

		//Code to get the category.
		if(null.compare(extract_Cat(line))!=0)
		{
			if(title.compare(title_temp)!=0)
			{
				title_temp = title;
				if(l==0){
					fcat<<title<<":  "<<extract_Cat(line)<<",  ";
					l=1;
				}
				else
					fcat<<std::endl<<title<<":  "<<extract_Cat(line)<<",  ";
			}
			else
				fcat<<extract_Cat(line)<<",  ";
		}

		//Code to extract Definitions
		if(line.find("</text>")!=std::string::npos)
			k=0;
		
		if(k==1||k==2)
		{
			if(k==2)
			{
				finfo<<"\t"<<line<<std::endl;
				if(line.find("}}")!=std::string::npos&&line.find("|")==std::string::npos){
					finfo<<std::endl;
					k=1;
				}
			}
			if(k==1){
				fdef<<" "<<line;
				length = length + line.length();
				if(length>500){
					fdef<<std::endl<<std::endl;
					k=0;
				}
			}
		}

		if(null.compare(extract_Def(line))!=0)
		{
			length = 0;
			fdef<<title<<": "<<extract_Def(line);
			length = extract_Def(line).length();
			if(extract_Def(line)=="[[INFOBOX]]"){
				finfo<<extract_Def(line)<<": "<<title<<endl;
				k=2;
			}
			else if(line.find("#REDIRECT")!=std::string::npos||line.find("#Redirect")!=std::string::npos||line.find("#redirect")!=std::string::npos||line.find("</text>")!=std::string::npos){
				k=0;
				fdef<<std::endl<<std::endl;
			}
			else 
				k=1;
		}
				
	}
	std::cout<<"EOF reached"<<std::endl;
	std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." <<std::endl;
	return 0;
}

std::string extract_Def(std::string text)
{
	std::string beginTag = "<text xml:space=";
	std::string null = "";

	std::size_t beginIdx = 0;
		
	beginIdx = text.find(beginTag);
		
	if(beginIdx!=std::string::npos){
		if(text.find("infobox")!=std::string::npos||text.find("Infobox")!=std::string::npos)
			return "[[INFOBOX]]";
		return text.substr(beginIdx + beginTag.length() + 11,text.length() - beginTag.length() - 11);		
	}
	
	return null;
}

std::string extract_Cat(std::string text)
{
	std::string beginTag = "[[Category:";
	std::string endTag = "]]";
	std::string null = "";

	std::size_t beginIdx = 0;
	std::size_t endIdx = 0;
		
	beginIdx = text.find(beginTag);
	endIdx = text.find(endTag);

	if(beginIdx!=std::string::npos){
		std::string C = text.substr(beginIdx + beginTag.length(),endIdx - beginTag.length()-beginIdx);
		if(C.find('|')!=std::string::npos)
			return null;
		return C;
	}
	return null;
}

std::string extract_links(std::string text)
{
	std::string beginTag = "[[";
	std::string endTag = "]]";
	std::string null = "";

	std::size_t beginIdx = 0;
	std::size_t endIdx = 0;
		
	beginIdx = text.find(beginTag);
	endIdx = text.find(endTag);

	if(beginIdx!=std::string::npos){
		std::string C = text.substr(beginIdx + beginTag.length(),endIdx - beginTag.length()-beginIdx);
		if((C.find("Category")!=std::string::npos||C.find("Image:")!=std::string::npos||C.find("px")!=std::string::npos||C.find("File:")!=std::string::npos||C.find("&lt;")!=std::string::npos||C.find('#')!=std::string::npos)&&(C.find("[[")==std::string::npos))
		{
			return null;
		}
		if(C.find("[[")!=std::string::npos)
			return C.substr(C.find("[[")+2,C.length()-C.find("[[")-2);
		if(C.find('|')!=std::string::npos)
			return C.substr(C.find('|')+1,C.length()-C.find('|')-1);
		return C;
	}
	return null;
}


std::string check_Tag(std::string text, std::string tag)
{
	std::size_t beginIdx = 0;
	std::size_t endIdx = 0;
	std::string null= "";

	std::string openTag(tag);
	std::string closeTag = tag.insert(1,"/");

	beginIdx = text.find(openTag);
	endIdx = text.find(closeTag);
	
	if(beginIdx!=std::string::npos)
		return text.substr(beginIdx + openTag.length(),endIdx - beginIdx - openTag.length());
	return null;
}