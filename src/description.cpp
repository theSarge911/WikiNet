while(getline(file,line))
{
  if(line.find("<title>")!=std::string::npos)
    title = text.substr(line.find("<title>") + 7,line.find("</title>") - 7 - line.find("<title>"));

  if(line.find("<text xml:space=")!= std::string::npos)
    k = 0;

  if(k==0)
  {
    s = s.append(" ");
    s = s.append(line);
    if(s.length()>2000)
      k = 1;
  }

  if(line.find("</text>")!= std::string::npos)
  {
    k = 1;
    fout<<"title"<<endl;
    fout<<s<<endl<<endl;
  }		
}
