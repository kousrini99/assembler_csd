#include<bits/stdc++.h>
using namespace std;

string tobinary(string s)
{
	int num=0;
	string str="";
	for(int i=0;i<s.length();i++)
	{
		num=num*10+(s[i]-'0');
	}
	if(num>=pow(2,16))
	  return "";
	for(int i=0;i<16;i++)
	{
		if(num%2==0)
		  str+="0";
		else
		  str+="1";
		num/=2;
	}
	reverse(str.begin(),str.end());
	return str;
}

int main()
{
	unordered_map<string,int> label_table;
	ifstream fin1;
	int count=0;
	fin1.open("source.txt");
	ofstream fout1;
	fout1.open("machinecode1.txt");

	while(!fin1.eof())
	{
		string line;
		int flag=0;
		getline(fin1,line);
		for(int i=0;i<line.length();i++)
		{
			if(isalnum(line[i]))
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		  continue;
		if(line[line.length()-1]==':')
		{
			line.erase(line.length()-1,line.length());
			label_table[line]=count;
			continue;
		}
		count++;
	}
	fin1.close();
	fin1.open("source.txt");
	count=0;
	while(!fin1.eof())
	{
		string info[3]={"","",""};
	    string r[3]={"","",""};
		string command="";
		int pos,flag=0;
		string line;
		getline(fin1,line);
		for(int i=0;i<line.length();i++)
		{
			if(isalnum(line[i]))
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		  continue;
		flag=0;
		if(line[0]=='\t'||line[0]==' ')
		{
			line.erase(0,1);
		}
		if(line[line.length()-1]==':')
		{
			cout<<endl;
			continue;
		}
		count++;
		for (int i=0;i<line.length();i++)
		{
			if(line[i]=='\t'||line[i]==' ')
			{
				pos=i+1;
				break;
			}
			else
			  command+=line[i];
		}
		ifstream fin2;
		fin2.open("symbol table for assembly.txt");
		while(fin2)
		{
			string match;
			getline(fin2,match);
			if(match==command)
			{
				flag=1;
				getline(fin2,match);
				string temp1="";
				int k=0;
				for (int i=0;i<match.length();i++)
				{
					if(match[i]=='\t')
					{
						info[k++]=temp1;
						temp1="";
					}
					else
					{
						temp1+=match[i];
					}
				}
				info[k++]=temp1;
			//	cout<<info[0]<<info[1]<<info[2]<<endl;
				break;
			}
		}
		if(flag==0)
		{
			cout<<"Syntax error in line "<<count<<endl;
			cout<<"Specified operation is invalid\n";
			cout<<line;
			return 0;
		}
		flag=0;
		fin2.close();
		int k=0;
		string temp="";
		for (int i=pos;i<line.length();i++)
		{
			if(line[i]==','||line[i]=='(')
			{
				if(temp==""||temp==" "||temp==",")
				{
					cout<<"Syntax error in line "<<count<<endl;
					cout<<"Additional symbols used\n";
					cout<<line;
					return 0;
				}
				ifstream fin2;
				fin2.open("symbol table for assembly.txt");
				flag=0;
				while(fin2)
				{
					string match;
					getline(fin2,match);
					if(match==temp)
					{
						flag=1;
						getline(fin2,match);
					//	cout<<match<<endl;//ddbug
						r[k++]=match;
					//	cout<<r[k-1]<<endl;//debug
						break;
					}
				}
				if(flag==0)
				{
					cout<<"Syntax error in line "<<count<<endl;
					cout<<"Invalid register\n";
					cout<<line;
					return 0;
				}
				fin2.close();
				temp="";	  
			}
			else if(line[i]!=')')
			   temp+=line[i];
		}
		flag=0;
		//ifstream fin2;
			//cout<<"debug"<<endl;//edbug
			    if(isdigit(temp[0]))
			    {
			    	if(info[1]!="")
			    	{
			    		cout<<"Syntax error in line "<<count<<endl;
					    cout<<"Invalid operand used for the operation \n";	
					    cout<<line;
					    return 0;
					}
			    	r[2]=tobinary(temp);
			    	if(r[2]=="")
			    	{
			    		cout<<"Math error-beyond range in line "<<count<<endl;
			    		cout<<line;
			    		return 0;
					}
			    	fout1<<info[0]<<r[0]<<r[1]<<r[2]<<info[2]<<info[1]<<endl;
			    	continue;
				}
				if(temp==""||temp==" "||temp==",")
				{
					cout<<"Syntax error in line "<<count<<endl;
					cout<<"Additional symbols used\n";	
					cout<<line;
					return 0;
				}
				fin2.open("symbol table for assembly.txt");
				while(fin2)
				{
					string match;
					getline(fin2,match);
					if(match==temp)
					{
						flag=1;
						getline(fin2,match);
						r[k++]=match;
						break;
					}
				}
				fin2.close();
				if(flag==0)
				{
					cout<<"Syntax error in line "<<count<<endl;
					cout<<"Invalid Operand\n";
					cout<<line;
					return 0;
				}
				//cout<<r[1]<<endl;
				fout1<<info[0]<<r[0]<<r[1]<<r[2]<<info[2]<<info[1]<<endl;
	}
	fin1.close();
	fout1.close();
}
