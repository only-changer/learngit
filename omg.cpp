#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cstdlib>
const int N = 10000000;
using namespace std;
vector<string> str;
map<string,int> label;
map<string,int> data_label;
map<string,int> to_rigister;
int i = -1,j,k = 0;
int r[32] = {0};
int lo = 0, hi = 0;
struct data_type
{
	int num;
	int mark = -1;
	int size;
	int current_size = 0;
	string chr;
};
data_type datar[N];
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
string check(string s)
{
	string ss;
	for (int i = 0;i < s.size();++i)
	{
		if (s[i] == '\\') 
		{
			if (s[i+1] == '\\') ss += '\\\\';
			if (s[i+1] == '\'') ss += '\\\'';
			if (s[i+1] == '\"') ss += '\\\"';
			if (s[i+1] == 'n') ss += '\n';
			if (s[i+1] == 't') ss += '\t';
			if (s[i+1] == '0') ss += '\0';
			if (s[i+1] == 'r') ss += '\r';
			++i;
		} else ss += s[i];
	}
	return ss;
}
int main()
{
	r[29] = N;
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
	for (k = 0;k < i;++k)
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
				         datar[datanum] = d;
				         datanum += 4;
				         ++j;
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
				         datar[datanum] = d;
				         datanum += 2;
				         ++j;
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
				         datar[datanum] = d;
				         datanum += 1;
				         ++j;
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
					s = check(s);                    
					s += '\0';       
					data_type d;
					d.size = s.size();
					d.mark = 4;
					d.chr = s;
                    datar[datanum] = d;
					datanum += s.size();
				} else 
				if (str[k].find(".ascii",0) != str[k].npos) 
				{
					int j = str[k].find("\"",0) + 1;
					string s = "";
					for (;j < str[k].size()-1;++j)
					{
						s += str[k][j];
					}
					s = check(s);
					if (s.size() == 0) continue;
				    data_type d;
					d.size = s.size();
					d.mark = 5;
					d.chr = s;
                    datar[datanum] = d;
					datanum += s.size();
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
					//cout<<str[k]<<' '<<datanum<<endl;
				}
			}
		}
	}
	j = label["main:"] ;
	while(j < str.size()-1)
	{ 
	    ++j;
	  //  cout<<j<<' '<<str[j]<<endl;
	    if (str[j].find("jal",0) != str[j].npos)
		{
		     r[31] = j + 1;
		     string s = "";
		     for (k = str[j].find("jal",0) + 4;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     s += ':';
		     j = label[s];
		     continue;
		}
		if (str[j].find("li",0) != str[j].npos)
		{
			 string s = "";
			 int key;
		     for (k = str[j].find("li",0) + 4;k < str[j].size() && str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		     else key = to_rigister[s];s = "";
		     for (k = str[j].find(",",0) + 1;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     int p = atoi(s.c_str());
		     r[key] = p;
		     continue;
		}
		if (str[j].find("syscall",0) != str[j].npos)
		{
			//cout << r[2] << ' ' << r[4] << endl;
			if (r[2] == 1) cout<<r[4];else
			if (r[2] == 4) cout<<datar[r[4]].chr;else
				if (r[2] == 5) {
					fscanf(stdin2, "%d", &r[2]); 
				}
				else
			if (r[2] == 8)  
			{
				char chr[1000];
				fscanf(stdin2,"%[^\n]",&chr);
				datar[r[4]].chr = chr;
				datar[r[4]].mark = 5;
				datar[r[4]].size = strlen(chr);
			}else
			if (r[2] == 10) return 0;else
			if (r[2] == 17) return r[4];else
			if (r[2] == 9)
			{
				r[2] = datanum;
				datar[datanum].mark = 6;
				datar[datanum].size = r[4];
				datar[datanum].current_size = 0;
				datanum += r[4];
			}
			continue;
		}
		if (str[j].find("sb", 0) != str[j].npos)
		{
			string s = "";
			int key;
			for (k = str[j].find("sb", 0) + 4; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
			else key = to_rigister[s]; s = "";
			for (k = str[j].find(",", 0) + 1; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			//cout << "               " << r[key] << endl;
			if (s.find("($", 0) == s.npos)
			{
				s += ':';
				datar[data_label[s]].chr = char(r[key]);
				datar[data_label[s]].mark = 5;
				datar[data_label[s]].size = 1;
			}
			else
			{
				string ss = ""; int ke = -1;
				for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
				int p = atoi(ss.c_str()); ss = "";
				for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
				if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
				else ke = to_rigister[ss];
				int t = r[ke] + p;
				datar[t].chr = char(r[key]);
				datar[t].mark = 3;
				datar[t].size = 1;
			}
			continue;
		}
		if (str[j].find("sw",0) != str[j].npos)
		{
			 string s = "";
			 int key;
		     for (k = str[j].find("sw",0) + 4;k < str[j].size() && str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		     else key = to_rigister[s];s = "";
		     for (k = str[j].find(",",0) + 1;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s.find("($",0) == s.npos)
		     {
		     	 s += ':';
		         datar[data_label[s]].num = r[key];
		         datar[data_label[s]].mark = 1;
		         datar[data_label[s]].size = 4;
		     }else
		     {
		     	 string ss = "";int ke = -1;
		     	 for (k = 0;k < s.find("($",0);++k) if (s[k] != ' ') ss += s[k]; 
		     	 int p = atoi(ss.c_str());ss = "";
		     	 for (k = s.find("($",0) + 2;k < s.size() - 1;++k) if (s[k] != ' ') ss += s[k];
		     	 if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
		     	 else ke = to_rigister[ss];
		     	 int t = r[ke] + p;
		     	 datar[t].num = r[key];
		         datar[t].mark = 1;
		         datar[t].size = 4;
		     }
		     continue;
		}
		if (str[j].find("lb",0) != str[j].npos)
		{
			 string s = "";
			 int key;
		     for (k = str[j].find("lb",0) + 4;k < str[j].size() && str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		     else key = to_rigister[s];s = "";
		     for (k = str[j].find(",",0) + 1;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s.find("($",0) == s.npos)
		     {
				 s += ':';
				 r[key] = datar[data_label[s]].num;
		     }else
		     {
		     	 string ss = "";int ke = -1;
		     	 for (k = 0;k < s.find("($",0);++k) if (s[k] != ' ') ss += s[k];
		     	 int p = atoi(ss.c_str());ss = "";
		     	 for (k = s.find("($",0) + 2;k < s.size()-1;++k) if (s[k] != ' ') ss += s[k];
		     	 if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
		     	 else ke = to_rigister[ss];
		     	 int t = r[ke] + p;
		     	 r[key] = datar[t].num ;
		     }
		     continue;
		}
		if (str[j].find("lw",0) != str[j].npos)
		{
			 string s = "";
			 int key;
		     for (k = str[j].find("lw",0) + 4;k < str[j].size() && str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		     else key = to_rigister[s];s = "";
		     for (k = str[j].find(",",0) + 1;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s.find("($",0) == s.npos)
		     {
				 s += ':';
		         r[key] = datar[data_label[s]].num;
		     }else
		     {
		     	 string ss = "";int ke = -1;
		     	 for (k = 0;k < s.find("($",0);++k) if (s[k] != ' ') ss += s[k];
		     	 int p = atoi(ss.c_str());ss = "";
		     	 for (k = s.find("($",0) + 2;k < s.size()-1;++k) if (s[k] != ' ') ss += s[k];
		     	 if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
		     	 else ke = to_rigister[ss];
		     	 int t = r[ke] + p;
		     	 r[key] = datar[t].num ;
		     }
		     continue;
		}
		if (str[j].find("jr",0) != str[j].npos)
		{
		     string s = "";
			 int key;
		     for ( k = str[j].find("jr",0) + 4;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		     else key = to_rigister[s];
			 j = r[key] - 1;
			 continue;
		}
		if (str[j].find("add",0) != str[j].npos)
		{
		     string s = "";
			 int key1,key2,key3;
		     for (k = str[j].find("add",0) + 5;k < str[j].size() && str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		         else key1 = to_rigister[s];s = "";
		     for (k = str[j].find('$',k) + 1;str[j][k] != ',' && k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		         else key2 = to_rigister[s];s = "";k += 2;   
		     for (;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s.find('$',0) != s.npos)
		     {
		     	 s.erase(s.begin());
		         if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
		         else key3 = to_rigister[s];
		         r[key1] = r[key2] + r[key3];
		     }
		     else
		     {
		     	int q = atoi(s.c_str());
		     	r[key1] = r[key2] + q;
		     }
             continue;
		 }
		if (str[j].find("sub",0) != str[j].npos)
		{
		     string s = "";
			 int key1,key2,key3;
		     for (k = str[j].find("sub",0) + 5;k < str[j].size() && str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		         else key1 = to_rigister[s];s = "";
		     for (k = str[j].find('$',k) + 1;str[j][k] != ',' && k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		         else key2 = to_rigister[s];s = "";k += 2;   
		     for (;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s.find('$',0) != s.npos)
		     {
		     	 s.erase(s.begin());
		         if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
		         else key3 = to_rigister[s];
		         r[key1] = r[key2] - r[key3];
		     }
		     else
		     {
		     	int q = atoi(s.c_str());
		     	r[key1] = r[key2] - q;
		     }
             continue;
		 }
		if (str[j].find("mul",0) != str[j].npos)
		{
		     string s = "";
			 int key1,key2,key3;
		     for (k = str[j].find("mul",0) + 5;k < str[j].size() && str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		         else key1 = to_rigister[s];s = "";
		     for (k = str[j].find('$',k) + 1;str[j][k] != ',' && k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		         else key2 = to_rigister[s];s = "";k += 2;   
		     for (;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s.find('$',0) != s.npos)
		     {
		     	 s.erase(s.begin());
		         if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
		         else key3 = to_rigister[s];
		         r[key1] = r[key2] * r[key3];
		     }
		     else
		     {
		     	int q = atoi(s.c_str());
		     	r[key1] = r[key2] * q;
		     }
             continue;
		 }
		if (str[j].find("div", 0) != str[j].npos)
		{
			string s = "";
			int key1, key2, key3;
			for (k = str[j].find("div", 0) + 5; k < str[j].size() && str[j][k] != ','; ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			else key1 = to_rigister[s]; s = "";
			for (k = str[j].find('$', k) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_rigister[s]; s = ""; k += 2;
			lo = r[key1] / r[key2];
			hi = r[key1] % r[key2];
			//cout << r[key1] << ' ' << r[key2] << ' ' << lo << ' ' << hi << endl;
			continue;
		}
		if (str[j].find("mfhi", 0) != str[j].npos)
		{
			string s = "";
			int key;
			for (k = str[j].find("mfhi", 0) + 6; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
			else key = to_rigister[s];
			r[key] = hi;
			continue;
		}
		if (str[j].find("mflo", 0) != str[j].npos)
		{
			string s = "";
			int key;
			for (k = str[j].find("mflo", 0) + 6; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
			else key = to_rigister[s];
			r[key] = lo;
			continue;
		}
		 if (str[j].find("move",0) != str[j].npos)
		 {
		 	 string s = "";
			 int key1,key2;
		     for (k = str[j].find("move",0) + 6;k < str[j].size() && str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		         else key1 = to_rigister[s];s = "";
		     for (k = str[j].find('$',k) + 1;str[j][k] != ',' && k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		         else key2 = to_rigister[s];s = "";
			 r[key1] = r[key2];
		 }
		 if (str[j].find("ble",0) != str[j].npos)
		 {
		 	 string s = ""; 
		 	 int key1,key2;
		 	 bool b = false;
		      for (k = str[j].find('$',0) + 1;str[j][k] != ',' && k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		         else key1 = to_rigister[s];s = ""; k += 2;  
		     for (;str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s.find('$',0) != s.npos)
		     {
		         if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		         else key2 = to_rigister[s];
		         if (r[key1] >= r[key2]) b = true;
		     }
		     else
		     {
		     	int q = atoi(s.c_str());
		     	if (r[key1] <= q) b = true;
		     } k += 2;s = "";
			 if (b == true)
			 {
			     for (;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     	 s += ':';
                 j = label[s] - 1;
             }
             continue;
         }
		 if (str[j].find("bgez", 0) != str[j].npos)
		 {
			 string s = "";
			 int key1, key2;
			 bool b = false;
			 for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			 if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			 else key1 = to_rigister[s]; s = "";   k += 2;
			 if (r[key1] >= 0) b = true;
			 if (b == true)
			 {
				 for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				 s += ':';
				 j = label[s] - 1;
			 }
			 continue;
		 }
         if (str[j].find("bge",0) != str[j].npos)
		 {
		 	 string s = ""; 
		 	 int key1,key2;
		 	 bool b = false;
		     for (k = str[j].find('$',0) + 1;str[j][k] != ',' && k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		         else key1 = to_rigister[s];s = ""; k += 2; 
		     for (;str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s.find('$',0) != s.npos)
		     {
		     	 s.erase(s.begin());
		         if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		         else key2 = to_rigister[s];
		         if (r[key1] >= r[key2]) b = true;
		         //cout<<key1<<' '<<key2<<' '<<r[key1]<<' '<<r[key2]<<endl;
		     }
		     else
		     {
		     	int q = atoi(s.c_str());
		     	if (r[key1] >= q) b = true;
		     } k += 2;s = "";
			 if (b == true)
			 {
			     for (;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     	 s += ':';
                 j = label[s] - 1;
             }
             continue;
         }
		 if (str[j].find("bnez", 0) != str[j].npos)
		 {
			 string s = "";
			 int key1, key2;
			 bool b = false;
			 for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			 if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			 else key1 = to_rigister[s]; s = "";   k += 2;
			 if (r[key1] != 0) b = true;
			 if (b == true)
			 {
				 for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				 s += ':';
				 j = label[s] - 1;
			 }
			 continue;
		 }
		 if (str[j].find("bgtz", 0) != str[j].npos)
		 {
			 string s = "";
			 int key1, key2;
			 bool b = false;
			 for (k = str[j].find('$', 0) + 1; str[j][k] != ',' && k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			 if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
			 else key1 = to_rigister[s]; s = "";   k += 2;
			 if (r[key1] > 0) b = true;
			 if (b == true)
			 {
				 for (; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
				 s += ':';
				 j = label[s] - 1;
			 }
			 continue;
		 }
         if (str[j].find("beqz",0) != str[j].npos)
		 {
		 	 string s = ""; 
		 	 int key1,key2;
		 	 bool b = false;
		      for (k = str[j].find('$',0) + 1;str[j][k] != ',' && k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		         else key1 = to_rigister[s];s = "";   k += 2;
             if (r[key1] == 0) b = true; 
			 if (b == true)
			 {
			     for (;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     	 s += ':';
                 j = label[s] - 1;
             }
             continue;
         }
         if (str[j].find("beq",0) != str[j].npos)
		 {
		 	 string s = ""; 
		 	 int key1,key2;
		 	 bool b = false;
		      for (k = str[j].find('$',0) + 1;str[j][k] != ',' && k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		         else key1 = to_rigister[s];s = "";   k += 2;
		     for (;str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s.find('$',0) != s.npos)
		     {
		         if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		         else key2 = to_rigister[s];
		         if (r[key1] >= r[key2]) b = true;
		     }
		     else
		     {
		     	int q = atoi(s.c_str());
		     	if (r[key1] == q) b = true;
		     } k += 2;s = "";
			 if (b == true)
			 {
			     for (;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     	 s += ':';
                 j = label[s] - 1;
             }
             continue;
         }
        if (str[j].find("slt",0) != str[j].npos)
		{
		     string s = "";
			 int key1,key2,key3;
		     for (k = str[j].find("slt",0) + 5;k < str[j].size() && str[j][k] != ',';++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		         else key1 = to_rigister[s];s = "";
		     for (k = str[j].find('$',k) + 1;str[j][k] != ',' && k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		         else key2 = to_rigister[s];s = "";k += 2;   
		     for (;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     if (s.find('$',0) != s.npos)
		     {
		     	 s.erase(s.begin());
		         if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
		         else key3 = to_rigister[s];
		         if ( r[key2] < r[key3]) r[key1] = 1;else r[key1] = 0;
		     }
		     else
		     {
		     	 int q = atoi(s.c_str());
		         if ( r[key2] < q) r[key1] = 1;else r[key1] = 0;
		     }
             continue;
		 }
		if (str[j][0] == 'b')
		{
		     string s = "";
		     for (k = 2;k < str[j].size();++k) if (str[j][k] != ' ') s += str[j][k];
		     s += ':';
		    // cout<<j<<' '<<s<<endl; 
		     j = label[s] - 1;
		     continue;
		}
		if (str[j][0] == 'j')
		{
			string s = "";
			for (k = 2; k < str[j].size(); ++k) if (str[j][k] != ' ') s += str[j][k];
			s += ':';
			// cout<<j<<' '<<s<<endl; 
			j = label[s] - 1;
			continue;
		}
	}    
}











