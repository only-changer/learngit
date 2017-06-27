#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cstdlib>
using namespace std;
vector<string> str;
map<string,int> label;
map<string,int> data_label;
map<string,int> to_rigister;
int i = -1,j,k;
int r[32] = {0};
struct data_type
{
	int num;
	int mark = -1;
	int size;
	string chr;
};
data_type data[10000000];
int datanum = 0;
void ready()
{
	to_rigister["zero"] = 0;
	to_rigister["at"] = 1;
	to_rigister["v0"] = 2;
	to_rigister["v1"] = 3;
	to_rigister["a0"] = 4;
	to_rigister["a1"] = 5;
	to_rigister["a2"] = 6;
	to_rigister["a3"] = 7;
	to_rigister["t0"] = 8;
	to_rigister["t1"] = 9;
	to_rigister["t2"] = 10;
	to_rigister["t3"] = 11;
	to_rigister["t4"] = 12;
	to_rigister["t5"] = 13;
	to_rigister["t6"] = 14;
	to_rigister["t7"] = 15;
	to_rigister["s0"] = 16;
	to_rigister["s1"] = 17;
	to_rigister["s2"] = 18;
	to_rigister["s3"] = 19;
	to_rigister["s4"] = 20;
	to_rigister["s5"] = 21;
	to_rigister["s6"] = 22;
	to_rigister["s7"] = 23;
	to_rigister["t8"] = 24;
	to_rigister["t9"] = 25;
	to_rigister["gp"] = 28;
	to_rigister["sp"] = 29;
	to_rigister["fp"] = 30;
	to_rigister["ra"] = 31;
}
int main()
{
	ready();
	FILE *stdin1 = fopen("array_test1-mahaojun.s","r");
    FILE *stdin2 = fopen("array_test1-mahaojun.in","r");
	char chr[100];
	while (fscanf(stdin1,"%[^\n]",&chr) != EOF) 
	{
		++i;
		string s = chr;
		while (s[0] == '\t' || s[0] == ' ') s.erase(s.begin());
		str.push_back(s);
	    if (s[s.size()-1] == ':')  
		{
		    label[s] = i;

		}
	    fscanf(stdin1,"\n");
	}
	for (int k = 0;k < i;++k)
	{
		if(str[k] == ".data")
		{
			while (str[k + 1] != ".text")
			{
				++k;
				if (str[k].find(".word",0) != str[k].npos) 
				{
				     int j = str[k].find(".word",0) + 6;
				     string s ="";
				     while(j < str[k].size())
				     {
				     	 s = "";
				         for (;str[k][j] != ',' && j < str[k].size();++j)
				         {
				     	    s += str[k][j];
				         }
				         int p = atoi(s.c_str());
				         data_type d;
				         d.size = 4;
				         d.mark = 1;
				         d.num = p;
				         data[datanum] = d;
				         datanum += 4;
				         ++j;
				         cout<<d.begin<<' '<<d.end<<' '<<d.num<<endl;
				     }
				}
				if (str[k].find(".half",0) != str[k].npos) 
				{
				     int j = str[k].find(".half",0) + 6;
				     string s ="";
				     while(j < str[k].size())
				     {
				     	 s = "";
				         for (;str[k][j] != ',' && j < str[k].size();++j)
				         {
				     	    s += str[k][j];
				         }
				         int p = atoi(s.c_str());
				         data_type d;
				         d.size = 2;
				         d.mark = 2;
				         d.num = p;
				         data[datanum] = d;
				         datanum += 2;
				         ++j;
				         cout<<d.begin<<' '<<d.end<<' '<<d.num<<endl;
				     }
				}
				if (str[k].find(".byte",0) != str[k].npos) 
				{
				     int j = str[k].find(".byte",0) + 6;
				     string s ="";
				     while(j < str[k].size())
				     {
				     	 s = "";
				         for (;str[k][j] != ',' && j < str[k].size();++j)
				         {
				     	    s += str[k][j];
				         }
				         int p = atoi(s.c_str());
				         data_type d;
				         d.size = 1;
				         d.mark = 3;
				         d.num = p;
				         data[datanum] = d;
				         datanum += 1;
				         ++j;
				         cout<<d.begin<<' '<<d.end<<' '<<d.num<<endl;
				     }
				}
				if (str[k].find(".asciiz",0) != str[k].npos) 
				{
					int j = str[k].find("\"",0) + 1;
					string s = "";
					for (;j < str[k].size()-1;++j)
					{
						s += str[k][j];
					}                       
					s += '\0';       
					data_type d;
					d.size = s.size();
					d.mark = 4;
					d.chr = s;
                    data[datanum] = d;
					datanum += s.size();
					cout<<d.begin<<' '<<d.end<<' '<<d.chr<<endl;
				} else 
				if (str[k].find(".ascii",0) != str[k].npos) 
				{
					int j = str[k].find("\"",0) + 1;
					string s = "";
					for (;j < str[k].size()-1;++j)
					{
						s += str[k][j];
					}
					if (s.size() == 0) continue;
				    data_type d;
					d.size = s.size();
					d.mark = 5;
					d.chr = s;
                    data[datanum] = d;
					datanum += s.size();
					cout<<d.begin<<' '<<d.end<<' '<<d.chr<<endl;
				}  
				if (str[k].find(".align",0) != str[k].npos)
				{
			        int j = str[k].find(".align",0) + 7;
				    string s ="";
				    for (;j < str[k].size();++j)
				    {
				     	s += str[k][j];
				    }
				    int p = atoi(s.c_str());
				    int ans = 1;
				    for (int q = 1;q <= p;++q) ans *= 2;
				    datanum = (datanum / ans + 1) * ans; 
				}
				if (str[k].find(".space",0) != str[k].npos)
				{
			        int j = str[k].find(".space",0) + 7;
				    string s ="";
				    for (;j < str[k].size();++j)
				    {
				     	s += str[k][j];
				    }
				    int p = atoi(s.c_str());
				    datanum += p; 
				}
				if (str[k][str[k].size()-1] == ':')
				{
					data_label[str[k]] = datanum;
					cout<<str[k]<<' '<<datanum<<endl;
				}
			}
		}
	}
	j = label["main:"] ;
	while(true)
	{ 
	    ++j;
	    if (str[j].find("jal",0) != str[j].npos)
		{
		     r[31] = j + 1;
		     string s = "";
		     for (int k = str[j].find("jal",0) + 4;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     s += ':';
		     j = label[s];
		     continue;
		}
		if (str[j].find("li",0) != str[j].npos)
		{
			 string s = "";
			 int key;
		     for (int k = str[j].find("li",0) + 4;k < str[j].size() && str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		     else key = to_rigister[s];s = "";
		     for (k = str[j].find(",",0) + 1;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     int p = atoi(s.c_str());
		     r[key] = p;
		     continue;
		}
		if (str[j].find("syscall",0) != str[j].npos)
		{
			if (r[2] == 1) cout<<r[4]<<endl;else
			if (r[2] == 4) cout<<data[r[4]].chr<<endl;else
			if (r[2] == 5) fscanf(stdin2,"%d",&r[2]);else
			if (r[2] == 8)  
			{
				char chr[1000];
				fscanf(stdin2,"%[^\n]",&chr);
				data[r[4]].chr = chr;
				data[r[4]].mark = 5;
				data[r[4]].size = strlen(chr);
			}else
			if (r[2] == 10) return 0;else
			if (r[2] == 17) return r[4];else
			if (r[2] == 9)
			{
				r[2] = datanum;
				datanum += r[4];
			}
			continue;
		}
		if (str[j].find("sw",0) != str[j].npos)
		{
			 string s = "";
			 int key;
		     for (int k = str[j].find("li",0) + 4;k < str[j].size() && str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		     else key = to_rigister[s];s = "";
		     for (k = str[j].find(",",0) + 1;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (str[s].find("($",0) == str[s].npos)
		     {
		         
		     
		if (str[j].find("jr",0) != str[j].npos)
		{
		     string s = "";
			 int key;
		     for (int k = str[j].find("jr",0) + 4;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		     else key = to_rigister[s];
			 j = r[key];
			 continue;
		}
			
	}    
}











