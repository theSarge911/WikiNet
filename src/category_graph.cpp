#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

class Cat
{
	public:
		string article;
		deque<string> category;
};


Cat check_Cat(std::string text)
{
	Cat *a;
	a = new Cat;

	std::string beginTag = ":";
	std::string endTag = ",";
	std::string null = "";

	std::size_t beginIdx = 0;
	std::size_t endIdx = 0;
		
	beginIdx = text.find(beginTag);
	a->article = text.substr(0,beginIdx);
	endIdx = text.find(endTag,beginIdx+1);
	a->category.push_back(text.substr(beginIdx+3,endIdx-beginIdx-3));
	
	while(1)
	{
		beginIdx = text.find(endTag,beginIdx+1);
		endIdx = text.find(endTag,beginIdx+1);
		if(beginIdx!=std::string::npos && endIdx!=std::string::npos){
			a->category.push_back(text.substr(beginIdx+3,endIdx-beginIdx-3));
		}
		else break;	
	}

	return *a;
}

int main()
{
	Cat A,B;
	string line="",line1="";
	std::ifstream file("Category.txt");
	std::ifstream file1("Category.txt");
	std::ofstream fout("Category_Network.txt");

	//Build Graph
	//naive method: use 2 iterators and compare each class to one another.
	//   Save computation by comparing each pair only once.
	
	while(!file.eof())
	{
		getline(file,line);
		while(!file1.eof())
		{
			getline(file1,line1);
			A = check_Cat(line);
			B = check_Cat(line1);
			if(A.article != B.article)
			{
				int k=0;
				for(int i=0;i<A.category.size();i++)
				{
					for(int j=0;j<B.category.size();j++)
					{
						if(A.category[i]==B.category[j])
							k++;
					}
				}
				if(k!=0)
					fout<<A.article<<"\t \t"<<B.article<<"\t \t"<<(k*1.0/(A.category.size()+B.category.size()-k))<<endl;
			}
			line1.clear();
			//printf("%d",1);
		}
		file1.clear();
		file1.seekg(0,ios::beg);		
		line.clear();

	}
	file1.close();
	file.close();

	return 0;
}