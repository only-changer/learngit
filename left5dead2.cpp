#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cstdlib>
const int N = 10000000;
using namespace std;
vector<string> str;
map<string, int> label;
map<string, int> data_label;
map<string, int> to_register;
int hazard = 0;
int mark = 0;
int i = -1, j, k = 0;
int r[32] = { 0 };
int f[34] = { 0 };
int lo = 0, hi = 0;
struct data_type
{
	int num;
	int mark = -1;
	int size;
	int current_size = 0;
	char chr;
};
data_type datar[N];
int datanum = 0;
int design(int x)
{
	if (x > 0) return x;
	//	else return (x + 4294967296);
}
void ready()
{
	to_register["zero"] = 0;
	to_register["at"] = 1;
	to_register["v0"] = 2;
	to_register["v1"] = 3;
	to_register["a0"] = 4;
	to_register["a1"] = 5;
	to_register["a2"] = 6;
	to_register["a3"] = 7;
	to_register["t0"] = 8;
	to_register["t1"] = 9;
	to_register["t2"] = 10;
	to_register["t3"] = 11;
	to_register["t4"] = 12;
	to_register["t5"] = 13;
	to_register["t6"] = 14;
	to_register["t7"] = 15;
	to_register["s0"] = 16;
	to_register["s1"] = 17;
	to_register["s2"] = 18;
	to_register["s3"] = 19;
	to_register["s4"] = 20;
	to_register["s5"] = 21;
	to_register["s6"] = 22;
	to_register["s7"] = 23;
	to_register["t8"] = 24;
	to_register["t9"] = 25;
	to_register["gp"] = 28;
	to_register["sp"] = 29;
	to_register["fp"] = 30;
	to_register["ra"] = 31;
}
string check(string s)
{
	string ss;
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == '\\')
		{
			if (s[i + 1] == '\\') ss += '\\\\';
			if (s[i + 1] == '\'') ss += '\\\'';
			if (s[i + 1] == '\"') ss += '\\\"';
			if (s[i + 1] == 'n') ss += '\n';
			if (s[i + 1] == 't') ss += '\t';
			if (s[i + 1] == '0') ss += '\0';
			if (s[i + 1] == 'r') ss += '\r';
			++i;
		}
		else ss += s[i];
	}
	return ss;
}
int maxx(int x, int y)
{
	if (x > y) return x;
	else return y;
}
int DH(int x)
{
	if (f[x] == 0) f[x] = 1;
	else
	{
		hazard = 2;
		mark = 0;
	}
	return hazard;
}
class add
{
private:
	int key1, key2, type, key3, q;
	int ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("add", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			type = 1;
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) ans = r[key2] + r[key3];
		else ans = r[key2] + q;
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		//if (type == 1) cout << key1 << ' ' << key2 << ' ' << key3 << ' ' << r[key1] << ' ' << r[key2] << ' ' << r[key3] << endl;
		r[key1] = ans;
	}
};
class addu
{
private:
	int key1, key2, type, key3, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("addu", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) ans = (unsigned) int(r[key2]) + (unsigned) int(r[key3]);
		else ans = (unsigned) int(r[key2]) + (unsigned) int(q);
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class sub
{
private:
	int key1, key2, type, key3, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("sub", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) ans = r[key2] - r[key3];
		else ans = r[key2] - q;
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class subu
{
private:
	int key1, key2, type, key3, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("subu", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			type = 1;
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) ans = (unsigned) int(r[key2]) - (unsigned) int(r[key3]);
		else ans = (unsigned) int(r[key2]) - (unsigned) int(q);
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class mul
{
private:
	int key1, key2, key3, type, q, loer, hier, ans;
	int h;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("mul", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s != "")
		{
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
				type = 1;
			}
			else
			{
				q = atoi(s.c_str());
				type = 2;
			}
		}
		else
		{
			type = 3;
			h = maxx(h, DH(32));
			h = maxx(h, DH(33));
		}
	}
	void EX()
	{
		if (type == 1) ans = r[key2] * r[key3];
		if (type == 2) ans = r[key2] * q;
		if (type == 3)
		{
			long long ss = r[key1] * r[key2];
			loer = ss & ((1LL << 32) - 1);
			hier = ss >> 32;
		}
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		if (type <= 2) r[key1] = ans;
		else
		{
			f[32] = 0;
			f[33] = 0;
			lo = loer;
			hi = hier;
		}
	}
};
class mulu
{
private:
	int key1, key2, key3, type, q, loer, hier, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("mulu", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s != "")
		{
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
				type = 1;
			}
			else
			{
				q = atoi(s.c_str());
				type = 2;
			}
		}
		else
		{
			type = 3;
			h = maxx(h, DH(32));
			h = maxx(h, DH(33));
		}
	}
	void EX()
	{
		if (type == 1) ans = (unsigned) int(r[key2]) * (unsigned) int(r[key3]);
		if (type == 2) ans = (unsigned) int(r[key2]) * (unsigned) int(q);
		if (type == 3)
		{
			long long ss = r[key1] * r[key2];
			loer = ss & ((1LL << 32) - 1);
			hier = ss >> 32;
		}
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		if (type <= 2) r[key1] = ans;
		else
		{
			lo = loer;
			hi = hier;
			f[32] = 0;
			f[33] = 0;
		}
	}
};
class divv
{
private:
	int key1, key2, key3, type, q, loer, hier, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("div", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s != "")
		{
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				type = 1;
				if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
			}
			else
			{
				q = atoi(s.c_str());
				type = 2;
			}
		}
		else
		{
			type = 3;
			h = maxx(h, DH(32));
			h = maxx(h, DH(33));
		}
	}
	void EX()
	{
		if (type == 1) ans = r[key2] / r[key3];
		if (type == 2) ans = r[key2] / q;
		if (type == 3)
		{
			loer = r[key1] / r[key2];
			hier = r[key1] % r[key2];
		}
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		if (type <= 2) r[key1] = ans;
		else
		{
			f[32] = 0;
			f[33] = 0;
			lo = loer;
			hi = hier;
		}
	}
};
class divvu
{
private:
	int key1, key2, key3, type, q, loer, hier, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("divu", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s != "")
		{
			if (s.find('$', 0) != s.npos)
			{
				s.erase(s.begin());
				if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
				else key3 = to_register[s];
				if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
				type = 1;
			}
			else
			{
				q = atoi(s.c_str());
				type = 2;
			}
		}
		else
		{
			type = 3;
			h = maxx(h, DH(32));
			h = maxx(h, DH(33));
		}
	}
	void EX()
	{
		if (type == 1) ans = (unsigned) int(r[key2]) / (unsigned) int(r[key3]);
		if (type == 2) ans = (unsigned) int(r[key2]) / (unsigned) int(q);
		if (type == 3)
		{
			loer = r[key1] / r[key2];
			hier = r[key1] % r[key2];
		}
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		if (type <= 2) r[key1] = ans;
		else
		{
			lo = loer;
			hi = hier;
			f[32] = 0;
			f[33] = 0;
		}
	}
};
class xxor
{
private:
	int key1, key2, type, key3, q, ans;
	int h;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("xor", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) ans = r[key2] ^ r[key3];
		else ans = r[key2] ^ q;
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class xxoru
{
private:
	int key1, key2, type, key3, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("xoru", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) ans = (unsigned) int(r[key2]) ^ (unsigned) int(r[key3]);
		else ans = (unsigned) int(r[key2]) ^ (unsigned) int(q);
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class neg
{
private:
	int key1, key2, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("neg", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = "";
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
	}
	void EX()
	{
		ans = (-1)*r[key2];
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		r[key1] = ans;
	}
};
class negu
{
private:
	int key1, key2, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("negu", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = "";
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
	}
	void EX()
	{
		ans = (-1)* (unsigned) int(r[key2]);
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		r[key1] = ans;
	}
};
class rem
{
private:
	int key1, key2, type, key3, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("rem", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			type = 1;
			if (key1 != key3 && key2 != key3) 	h = maxx(h, DH(key3));
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) ans = r[key2] % r[key3];
		else ans = r[key2] % q;
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class remu
{
private:
	int key1, key2, type, key3, q, ans;
	int h;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("remu", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) ans = (unsigned) int(r[key2]) % (unsigned) int(r[key3]);
		else ans = (unsigned) int(r[key2]) % (unsigned) int(q);
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class li
{
private:
	int key, p;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("li", 0) + 4; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";
		for (k = str.find(",", 0) + 1; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		p = atoi(s.c_str());
		h = maxx(h, DH(key));
	}
	void EX() {}
	void WB()
	{
		f[key] = 0;
		r[key] = p;
	}
};
class seq
{
private:
	int key1, key2, key3, type, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("seq", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) if (r[key2] == r[key3]) ans = 1; else ans = 0;
		if (type == 2) if (r[key2] == q) ans = 1; else ans = 0;
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class sge
{
private:
	int key1, key2, key3, type, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("sge", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) if (r[key2] >= r[key3]) ans = 1; else ans = 0;
		if (type == 2) if (r[key2] >= q) ans = 1; else ans = 0;
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class sgt
{
private:
	int key1, key2, key3, type, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("sgt", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) if (r[key2] > r[key3]) ans = 1; else ans = 0;
		if (type == 2) if (r[key2] > q) ans = 1; else ans = 0;
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class sle
{
private:
	int key1, key2, key3, type, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("sle", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) if (r[key2] <= r[key3]) ans = 1; else ans = 0;
		if (type == 2) if (r[key2] <= q) ans = 1; else ans = 0;
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class slt
{
private:
	int key1, key2, key3, type, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("slt", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) if (r[key2] < r[key3]) ans = 1; else ans = 0;
		if (type == 2) if (r[key2] < q) ans = 1; else ans = 0;
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class sne
{
private:
	int key1, key2, key3, type, q, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("sne", 0) + 5; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = ""; k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key3 = atoi(s.c_str());
			else key3 = to_register[s];
			if (key1 != key3 && key2 != key3) h = maxx(h, DH(key3));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		}
	}
	void EX()
	{
		if (type == 1) if (r[key2] != r[key3]) ans = 1; else ans = 0;
		if (type == 2) if (r[key2] != q) ans = 1; else ans = 0;
	}
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		if (type == 1) f[key3] = 0;
		r[key1] = ans;
	}
};
class bb
{
private:
	string s;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = 2; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
	}
	void EX() {}
	int WB()
	{
		
		return label[s];
	}
};
class beq
{
private:
	int key1, key2, type, q;
	bool b;
	int h = 0;
	string s;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";   k += 2;
		for (; str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s];
			if (key1 != key2) h = maxx(h, DH(key2));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		} k += 2; s = "";
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
	}
	void EX()
	{
		if (type == 1) b = (r[key1] == r[key2]);
		else b = (r[key1] == q);
	}
	int WB()
	{
		
		f[key1] = 0;
		if (type == 1) f[key2] = 0;
		if (b == true) return label[s]; else return 0;
	}
};
class bne
{
private:
	int key1, key2, type, q;
	int h = 0;
	bool b;
	string s;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";   k += 2;
		for (; str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s];
			if (key1 != key2) h = maxx(h, DH(key2));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		} k += 2; s = "";
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
	}
	void EX()
	{
		if (type == 1) b = (r[key1] != r[key2]);
		else b = (r[key1] != q);
	}
	int WB()
	{
		
		f[key1] = 0;
		if (type == 1) f[key2] = 0;
		if (b == true) return label[s]; else return 0;
	}
};
class bge
{
private:
	int key1, key2, type, q;
	bool b;
	int h = 0;
	string s;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";   k += 2;
		for (; str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s];
			if (key1 != key2) h = maxx(h, DH(key2));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		} k += 2; s = "";
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
	}
	void EX()
	{
		if (type == 1) b = (r[key1] >= r[key2]);
		else b = (r[key1] >= q);
	}
	int WB()
	{
	//	cout << key1 << ' ' << key2 << ' ' << r[key1] << ' ' << r[key2] << endl;
		if (r[key1] == 4)
			r[key1] = 4;
		f[key1] = 0;
		if (type == 1) f[key2] = 0;
		
		if (b == true) return label[s]; else return 0;
	}
};
class ble
{
private:
	int key1, key2, type, q;
	int h = 0;
	bool b;
	string s;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";   k += 2;
		for (; str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s];
			if (key1 != key2) h = maxx(h, DH(key2));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		} k += 2; s = "";
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
	}
	void EX()
	{
		if (type == 1) b = (r[key1] <= r[key2]);
		else b = (r[key1] <= q);
	}
	int WB()
	{
		f[key1] = 0;
		if (type == 1) f[key2] = 0;
		
		if (b == true) return label[s]; else return 0;
	}
};
class bgt
{
private:
	int key1, key2, type, q;
	bool b;
	string s;
	int h = 0;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";   k += 2;
		for (; str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s];
			if (key1 != key2) h = maxx(h, DH(key2));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		} k += 2; s = "";
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
	}
	void EX()
	{
		if (type == 1) b = (r[key1] > r[key2]);
		else b = (r[key1] > q);
	}
	int WB()
	{
		f[key1] = 0;
		if (type == 1) f[key2] = 0;
		
		if (b == true) return label[s]; else return 0;
	}
};
class blt
{
private:
	int key1, key2, type, q;
	bool b;
	int h = 0;
	string s;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";   k += 2;
		for (; str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key1));
		if (s.find('$', 0) != s.npos)
		{
			s.erase(s.begin());
			if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
			else key2 = to_register[s];
			if (key1 != key2) h = maxx(h, DH(key2));
			type = 1;
		}
		else
		{
			q = atoi(s.c_str());
			type = 2;
		} k += 2; s = "";
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
	}
	void EX()
	{
		if (type == 1) b = (r[key1] < r[key2]);
		else b = (r[key1] < q);
	}
	int WB()
	{
		f[key1] = 0;
		if (type == 1) f[key2] = 0;
		
		if (b == true) return label[s]; else return 0;
	}
};
class beqz
{
private:
	int key;
	string s;
	int h = 0;
	bool b;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";   k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		s += ':';
	}
	void EX()
	{
		b = (r[key] == 0);
	}
	int WB()
	{
		f[key] = 0;
		
		if (b == true) return label[s]; else return 0;
	}
};
class bnez
{
private:
	int key;
	bool b;
	string s;
	int h = 0;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";   k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		s += ':';
	}
	void EX()
	{
		b = (r[key] != 0);
	}
	int WB()
	{
		
		f[key] = 0;
		if (b == true) return label[s]; else return 0;
	}
};
class blez
{
private:
	int key;
	string s;
	int h = 0;
	bool b;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";   k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		s += ':';
	}
	void EX()
	{
		b = (r[key] <= 0);
	}
	int WB()
	{
		
		f[key] = 0;
		if (b == true) return label[s]; else return 0;
	}
};
class bgez
{
private:
	int key;
	bool b;
	string s;
	int h = 0;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";   k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		s += ':';
	}
	void EX()
	{
		b = (r[key] >= 0);
	}
	int WB()
	{
		f[key] = 0;
		
		if (b == true) return label[s]; else return 0;
	}
};
class bgtz
{
private:
	int key;
	string s;
	bool b;
	int h = 0;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";   k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
		h = maxx(h, DH(key));
	//	cout << key << ' ' << r[key] << endl;
	}
	void EX()
	{
		b = (r[key] > 0);
	}
	int WB()
	{
		f[key] = 0;
		
		if (b == true) return label[s]; else return 0;
	}
};
class bltz
{
private:
	int key;
	string s;
	bool b;
	int h = 0;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = str.find('$', 0) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";   k += 2;
		for (; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		s += ':';
	}
	void EX()
	{
		b = (r[key] < 0);
	}
	int WB()
	{
		f[key] = 0;
		
		if (b == true) return label[s]; else return 0;
	}
};
class jj
{
private:
	string s;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = 2; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
	}
	void EX() {}
	int WB()
	{
		
		return label[s];
	}
};
class jr
{
private:
	int key, ans;
	int h = 0;
public:
	void DP(string str)
	{
		hazard = 1; mark = 0;
		string s = "";
		for (k = str.find("jr", 0) + 4; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s];
		h = maxx(h, DH(key));
	}
	void EX() { ans = r[key]; }
	int WB()
	{
		f[key] = 0;
		
		return ans;
	}
};
class jal
{
private:
	string s;
	int j;
public:
	void DP(string str, int m)
	{
		hazard = 1; mark = 0;
		s = "";
		for (k = 4; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		s += ':';
		j = m;
	}
	void EX() {}
	int WB()
	{
		r[31] = j;
		return label[s];
	}
};
class la
{
private:
	int key, ans,type,ke,p;
	int h = 0;
	string s;
public:
	void DP(string str)
	{
		s = "";
		for (k = str.find("la", 0) + 4; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";
		for (k = str.find(",", 0) + 1; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		if (s.find("($", 0) == s.npos)
		{
			type = 1;
			s += ':';
			//ans = data_label[s];
		}
		else
		{
			string ss = "";
			for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
			p = atoi(ss.c_str()); ss = "";
			for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
			if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
			else ke = to_register[ss];
			//int t = r[ke] + p;
			type = 2;
			if (key != ke) h = maxx(h, DH(ke));
			//ans = t;
		}
	}
	void EX()
	{
		if (type == 1) ans = data_label[s];
		else ans = r[ke] + p;
	}
	void WB()
	{
		f[key] = 0;
		if (type == 2) f[ke] = 0;
		r[key] = ans;
	}
};
class lb
{
private:
	int key, ans, type, ke, p;
	int h = 0,rr;
	string s;
public:
	void DP(string str)
	{
		s = "";
		for (k = str.find("lb", 0) + 4; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";
		for (k = str.find(",", 0) + 1; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		if (s.find("($", 0) == s.npos)
		{
			type = 1;
			s += ':';
			//ans = data_label[s];
		}
		else
		{
			string ss = ""; 
			for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
			p = atoi(ss.c_str()); ss = "";
			for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
			if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
			else ke = to_register[ss];
			//int t = r[ke] + p;
			type = 2;
			if (key != ke) h = maxx(h, DH(ke));
			//ans = t;
		}
	}
	void EX()
	{
		if (type == 1) ans = data_label[s];
		else ans = r[ke] + p;
	}
	void MA()
	{
		rr = int(datar[ans].chr);
	}
	void WB()
	{
		f[key] = 0;
		if (type == 2) f[ke] = 0;
		r[key] = rr;
	}
};
class lw
{
private:
	int key, ans, type, ke, p;
	int h = 0, rr;
	string s;
public:
	void DP(string str)
	{
		s = "";
		for (k = str.find("lw", 0) + 4; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";
		for (k = str.find(",", 0) + 1; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		if (s.find("($", 0) == s.npos)
		{
			type = 1;
			s += ':';
			//ans = data_label[s];
		}
		else
		{
			string ss = ""; 
			for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
			p = atoi(ss.c_str()); ss = "";
			for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
			if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
			else ke = to_register[ss];
			//int t = r[ke] + p;
			type = 2;
			if (key != ke) h = maxx(h, DH(ke));
			//ans = t;
		}
	}
	void EX()
	{
		if (type == 1) ans = data_label[s];
		else ans = r[ke] + p;
	}
	void MA()
	{
		rr =(datar[ans].num);
	}
	void WB()
	{
		f[key] = 0;
		if (type == 2) f[ke] = 0;
		r[key] = rr;
	//	if (type == 2) cout << ke << ' ' << r[ke] << ' ' << p << ' '<<r[key]<<endl;
	}
};
class sb
{
private:
	int key, ans,type,ke,h = 0,rr,p;
	string s;
public:
	void DP(string str)
	{
		s = "";
		for (k = str.find("sb", 0) + 4; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";
		for (k = str.find(",", 0) + 1; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		if (s.find("($", 0) == s.npos)
		{
			type = 1;
			s += ':';
			//ans = data_label[s];
		}
		else
		{
			string ss = ""; 
			for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
			p = atoi(ss.c_str()); ss = "";
			for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
			if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
			else ke = to_register[ss];
			//int t = r[ke] + p;
			type = 2;
			if (key != ke) h = maxx(h, DH(ke));
			//ans = t;
		}
	}
	void EX()
	{
		if (type == 1) ans = data_label[s];
		else ans = r[ke] + p;
	}
	void MA()
	{
		datar[ans].chr = char(r[key]);
	}
	void WB() 
	{
		f[key] = 0;
		if (type == 2) f[ke] = 0;
	}
};
class sw
{
private:
	int key, ans, type, ke, h = 0, rr, p;
	string s;
public:
	void DP(string str)
	{
		s = "";
		for (k = str.find("sw", 0) + 4; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s]; s = "";
		for (k = str.find(",", 0) + 1; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		h = maxx(h, DH(key));
		if (s.find("($", 0) == s.npos)
		{
			type = 1;
			s += ':';
			//ans = data_label[s];
		}
		else
		{
			string ss = ""; 
			for (k = 0; k < s.find("($", 0); ++k) if (s[k] != ' ') ss += s[k];
			p = atoi(ss.c_str()); ss = "";
			for (k = s.find("($", 0) + 2; k < s.size() - 1; ++k) if (s[k] != ' ') ss += s[k];
			if (ss[0] >= '0' && ss[0] <= '9') ke = atoi(ss.c_str());
			else ke = to_register[ss];
			//int t = r[ke] + p;
			type = 2;
			if (key != ke) h = maxx(h, DH(ke));
			//ans = t;
		}
	}
	void EX()
	{
		if (type == 1) ans = data_label[s];
		else ans = r[ke] + p;
	}
	void MA()
	{
		datar[ans].num = r[key];
	}
	void WB()
	{
		f[key] = 0;
		if (type == 2) f[ke] = 0;
	//	if (type == 2) cout << ke << ' ' << r[ke] << ' ' << p <<' '<<key<<' '<<r[key]<< endl;
	}
};
class mov
{
private:
	int key1, key2, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("move", 0) + 6; k < str.size() && str[k] != ','; ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key1 = atoi(s.c_str());
		else key1 = to_register[s]; s = "";
		for (k = str.find('$', k) + 1; str[k] != ',' && k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key2 = atoi(s.c_str());
		else key2 = to_register[s]; s = "";
		h = maxx(h, DH(key1));
		if (key1 != key2) h = maxx(h, DH(key2));
	}
	void EX() { ans = r[key2]; }
	void WB()
	{
		f[key1] = 0;
		f[key2] = 0;
		r[key1] = ans;
	}
};
class mfhi
{
private:
	int key, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("mfhi", 0) + 6; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s];
		h = maxx(h, DH(key));
		h = maxx(h, DH(32));
	}
	void EX() { ans = hi; }
	void WB()
	{
		f[key] = 0;
		f[32] = 0;
		r[key] = ans;
	}
};
class mflo
{
private:
	int key, ans;
	int h = 0;
public:
	void DP(string str)
	{
		string s = "";
		for (k = str.find("mflo", 0) + 6; k < str.size(); ++k) if (str[k] != ' ') s += str[k];
		if (s[0] >= '0' && s[0] <= '9') key = atoi(s.c_str());
		else key = to_register[s];
		h = maxx(h, DH(key));
		h = maxx(h, DH(33));
	}
	void EX() { ans = lo; }
	void WB()
	{
		f[key] = 0;
		f[33] = 0;
		r[key] = ans;
	}
};
class syscall
{
private:
	int v0, a0;
	int h = 0;
	int abs(int x)
	{
		if (x >= 0) return x;
		else return -x;
	}
public:
	void DP() 
	{
		h = maxx(h, DH(2));
		h = maxx(h, DH(4));
	}
	void EX() {}
	void MA() {}
	int WB()
	{
		f[2] = 0;
		f[4] = 0;
		//cout << r[2] << ' ' << r[4] << endl;
		if (r[2] == 1) cout << r[4]; else
			if (r[2] == 4) {
				int j = r[4];
				while (datar[j].chr != '\0') { cout << datar[j].chr; ++j; }
			}
			else
				if (r[2] == 5) {
					//fscanf(stdin2, "%d", &r[2]);
					cin >> r[2];
				}
				else
					if (r[2] == 8)
					{
						char chr[1000];
						//fscanf(stdin2, "%s", &chr);
						cin >> chr;
						string s = chr;
						data_type d;
						d.size = s.size();
						d.mark = 5;
						datar[r[4]] = d;
						int t = r[4];
						for (int j = 0; j <= s.size(); ++j)
						{
							datar[t].chr = s[j];
							++t;
						}

					}
					else
						if (r[2] == 10) return 0; else
							if (r[2] == 17) return abs(r[4]); else
								if (r[2] == 9)
								{
									r[2] = datanum;
									datar[datanum].mark = 6;
									datar[datanum].size = r[4];
									datar[datanum].current_size = 0;
									datanum += r[4];
								}
		return -1;
	}
};
string get_name(string s)
{
	string ss;
	for (int k = 0; k < s.size() && s[k] != ' '; ++k) ss += s[k];
	return ss;
}
int main(int agrc,char* agrv[])
{
	r[29] = N;
	ready();
	FILE *stdin1 = fopen(agrv[1], "r");
//	FILE *stdin2 = fopen("array_test1-mahaojun.in", "r");
	char chr[100];
	while (fscanf(stdin1, "%[^\n]", &chr) != EOF)
	{
		++i;
		string s = chr;
		while (s[0] == '\t' || s[0] == ' ') s.erase(s.begin());
		str.push_back(s);
		if (s[s.size() - 1] == ':')
		{
			label[s] = i;

		}
		fscanf(stdin1, "\n");
	}
	for (k = 0; k < i; ++k)
	{
		if (str[k] == ".data")
		{
			while (str[k + 1] != ".text")
			{
				++k;
				if (str[k].find(".word", 0) != str[k].npos)
				{
					int j = str[k].find(".word", 0) + 6;
					string s = "";
					while (j < str[k].size())
					{
						s = "";
						for (; str[k][j] != ',' && j < str[k].size(); ++j)
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
				if (str[k].find(".half", 0) != str[k].npos)
				{
					int j = str[k].find(".half", 0) + 6;
					string s = "";
					while (j < str[k].size())
					{
						s = "";
						for (; str[k][j] != ',' && j < str[k].size(); ++j)
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
				if (str[k].find(".byte", 0) != str[k].npos)
				{
					int j = str[k].find(".byte", 0) + 6;
					string s = "";
					while (j < str[k].size())
					{
						s = "";
						for (; str[k][j] != ',' && j < str[k].size(); ++j)
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
				if (str[k].find(".asciiz", 0) != str[k].npos)
				{
					int j = str[k].find("\"", 0) + 1;
					string s = "";
					for (; j < str[k].size() - 1; ++j)
					{
						s += str[k][j];
					}
					s = check(s);
					if (s.size() == 0) continue;
					data_type d;
					d.size = s.size() + 1;
					d.mark = 5;
					datar[datanum] = d;
					for (j = 0; j <= s.size(); ++j)
					{
						datar[datanum].chr = s[j];
						++datanum;
					}
					//	cout<<s<<endl;
				}
				else
					if (str[k].find(".ascii", 0) != str[k].npos)
					{
						int j = str[k].find("\"", 0) + 1;
						string s = "";
						for (; j < str[k].size() - 1; ++j)
						{
							s += str[k][j];
						}
						s = check(s);
						if (s.size() == 0) continue;
						data_type d;
						d.size = s.size();
						d.mark = 5;
						datar[datanum] = d;
						for (j = 0; j < s.size(); ++j)
						{
							datar[datanum].chr = s[j];
							++datanum;
						}
					}
				if (str[k].find(".align", 0) != str[k].npos)
				{
					int j = str[k].find(".align", 0) + 7;
					string s = "";
					for (; j < str[k].size(); ++j)
					{
						s += str[k][j];
					}
					int p = atoi(s.c_str());
					int ans = 1;
					for (int q = 1; q <= p; ++q) ans *= 2;
					datanum = (datanum / ans + 1) * ans;
					//	cout<<ans<<endl;
				}
				if (str[k].find(".space", 0) != str[k].npos)
				{
					int j = str[k].find(".space", 0) + 7;
					string s = "";
					for (; j < str[k].size(); ++j)
					{
						s += str[k][j];
					}
					int p = atoi(s.c_str());
					datanum += p;
				}
				if (str[k][str[k].size() - 1] == ':')
				{
					data_label[str[k]] = datanum;
					//cout<<str[k]<<' '<<datanum<<endl;
				}
				//	cout<<str[k]<<' '<<datanum<<endl;
			}
		}
	}
	j = label["main:"];
	int status[5] = { 0 };
	string s[5];
	string name[5];
	add adder[5];
	addu adduer[5];
	sub suber[5];
	subu subuer[5];
	mul muler[5];
	mulu muluer[5];
	divv divver[5];
	divvu divvuer[5];
	xxor xxorer[5];
	xxoru xxoruer[5];
	neg neger[5];
	negu neguer[5];
	rem remer[5];
	remu remuer[5];
	li lier[5];
	seq seqer[5];
	sge sgeer[5];
	sgt sgter[5];
	sle sleer[5];
	slt slter[5];
	sne sneer[5];
	bb bber[5];
	beq beqer[5];
	bne bneer[5];
	bge bgeer[5];
	blt blter[5];
	ble bleer[5];
	bgt bgter[5];
	beqz beqzer[5];
	bnez bnezer[5];
	blez blezer[5];
	bgez bgezer[5];
	bgtz bgtzer[5];
	bltz bltzer[5];
	jj jjer[5];
	jr jrer[5];
	jal jaler[5];
	la laer[5];
	lb lber[5];
	lw lwer[5];
	sb sber[5];
	sw swer[5];
	mov mover[5];
	mfhi mfhier[5];
	mflo mfloer[5];
	syscall syscaller[5];
	int i = 5 ,i0 ,t0,laststone = 0;
	while (true)
	{
		--i;
		if (i < 0) i += 5;
		if (hazard != 0)
		{
			bool b = true;
			for (int ii = 0; ii <= 4; ++ii) if (status[ii] == 1) b = false;
			if (b == true)
			{
				i = 4;
				for (int ii = 0; ii <= 4; ++ii) {
					status[ii] = 0; s[ii] = ""; name[ii] = "";
				}
				for (int ii = 0; ii <= 33; ++ii) f[ii] = 0;
				if (hazard == 1)
				{
					if (laststone == 1) ++j; 
					if (j == 417)
						j = 417;
					laststone = 0;
				}
				else --j;
				while (label[str[j]] != 0)
					++j;
				hazard = 0;
			}
		}
		else
		{
			++j;

		}

		for (int k = 4; k >= 0; --k)
		{
			int t = (k + i) % 5;

			if (k == 0) 
			{ 
				if (status[t] != 0 || hazard != 0) continue;
				while (label[str[j]] != 0)
					++j;
				s[t] = str[j];
				name[t] = get_name(s[t]); 
				 status[t] = 1;
				//cout << j << '\t' << str[j] << endl;
			}
			if (k == 1)
			{
			if (status[t] <= 0) continue;
			if (hazard != 0) continue;
			if (name[t] == "add") adder[t].DP(s[t]);
			if (name[t] == "addu") adduer[t].DP(s[t]);
			if (name[t] == "sub") suber[t].DP(s[t]);
			if (name[t] == "subu") subuer[t].DP(s[t]);
			if (name[t] == "mul") muler[t].DP(s[t]);
			if (name[t] == "mulu") muluer[t].DP(s[t]);
			if (name[t] == "div") divver[t].DP(s[t]);
			if (name[t] == "divu") divvuer[t].DP(s[t]);
			if (name[t] == "xor") xxorer[t].DP(s[t]);
			if (name[t] == "xoru") xxoruer[t].DP(s[t]);
			if (name[t] == "neg") neger[t].DP(s[t]);
			if (name[t] == "negu") neguer[t].DP(s[t]);
			if (name[t] == "rem") remer[t].DP(s[t]);
			if (name[t] == "remu") remuer[t].DP(s[t]);
			if (name[t] == "li") lier[t].DP(s[t]);
			if (name[t] == "seq") seqer[t].DP(s[t]);
			if (name[t] == "sge") sgeer[t].DP(s[t]);
			if (name[t] == "sgt") sgter[t].DP(s[t]);
			if (name[t] == "sle") sleer[t].DP(s[t]);
			if (name[t] == "slt") slter[t].DP(s[t]);
			if (name[t] == "sne") sneer[t].DP(s[t]);
			if (name[t] == "b") bber[t].DP(s[t]);
			if (name[t] == "beq") beqer[t].DP(s[t]);
			if (name[t] == "bne") bneer[t].DP(s[t]);
			if (name[t] == "bge") bgeer[t].DP(s[t]);
			if (name[t] == "ble") bleer[t].DP(s[t]);
			if (name[t] == "bgt") bgter[t].DP(s[t]);
			if (name[t] == "blt") blter[t].DP(s[t]);
			if (name[t] == "beqz") beqzer[t].DP(s[t]);
			if (name[t] == "bnez") bnezer[t].DP(s[t]);
			if (name[t] == "bgez") bgezer[t].DP(s[t]);
			if (name[t] == "blez") blezer[t].DP(s[t]);
			if (name[t] == "bgtz") bgtzer[t].DP(s[t]);
			if (name[t] == "bltz") bltzer[t].DP(s[t]);
			if (name[t] == "j") jjer[t].DP(s[t]);
			if (name[t] == "jr") jrer[t].DP(s[t]);
			if (name[t] == "jal") jaler[t].DP(s[t], j - 1);
			if (name[t] == "la") laer[t].DP(s[t]);
			if (name[t] == "lb") lber[t].DP(s[t]);
			if (name[t] == "lw") lwer[t].DP(s[t]);
			if (name[t] == "sb") sber[t].DP(s[t]);
			if (name[t] == "sw") swer[t].DP(s[t]);
			if (name[t] == "move") mover[t].DP(s[t]);
			if (name[t] == "mfhi") mfhier[t].DP(s[t]);
			if (name[t] == "mflo") mfloer[t].DP(s[t]);
			if (name[t] == "syscall") syscaller[t].DP();
			if (hazard == 2)
			{
				i0 = i;
				t0 = t;
				status[t] = -1;
				status[(t + 4) % 5] = -1;
				status[(t + 3) % 5] = -1;
			}
			if (hazard == 1)
			{
				i0 = i;
				t0 = t;
				status[(t + 4) % 5] = -1;
				status[(t + 3) % 5] = -1;
			}
			}
			if (k == 2)
			{
				if (status[t] <= 0) continue;
				if (name[t] == "add") adder[t].EX();
				if (name[t] == "addu") adduer[t].EX();
				if (name[t] == "sub") suber[t].EX();
				if (name[t] == "subu") subuer[t].EX();
				if (name[t] == "mul") muler[t].EX();
				if (name[t] == "mulu") muluer[t].EX();
				if (name[t] == "div") divver[t].EX();
				if (name[t] == "divu") divvuer[t].EX();
				if (name[t] == "xor") xxorer[t].EX();
				if (name[t] == "xoru") xxoruer[t].EX();
				if (name[t] == "neg") neger[t].EX();
				if (name[t] == "negu") neguer[t].EX();
				if (name[t] == "rem") remer[t].EX();
				if (name[t] == "remu") remuer[t].EX();
				if (name[t] == "li") lier[t].EX();
				if (name[t] == "seq") seqer[t].EX();
				if (name[t] == "sge") sgeer[t].EX();
				if (name[t] == "sgt") sgter[t].EX();
				if (name[t] == "sle") sleer[t].EX();
				if (name[t] == "slt") slter[t].EX();
				if (name[t] == "sne") sneer[t].EX();
				if (name[t] == "b") bber[t].EX();
				if (name[t] == "beq") beqer[t].EX();
				if (name[t] == "bne") bneer[t].EX();
				if (name[t] == "bge") bgeer[t].EX();
				if (name[t] == "ble") bleer[t].EX();
				if (name[t] == "bgt") bgter[t].EX();
				if (name[t] == "blt") blter[t].EX();
				if (name[t] == "beqz") beqzer[t].EX();
				if (name[t] == "bnez") bnezer[t].EX();
				if (name[t] == "bgez") bgezer[t].EX();
				if (name[t] == "blez") blezer[t].EX();
				if (name[t] == "bgtz") bgtzer[t].EX();
				if (name[t] == "bltz") bltzer[t].EX();
				if (name[t] == "j") jjer[t].EX();
				if (name[t] == "jr") jrer[t].EX();
				if (name[t] == "jal") jaler[t].EX();
				if (name[t] == "la") laer[t].EX();
				if (name[t] == "lb") lber[t].EX();
				if (name[t] == "lw") lwer[t].EX();
				if (name[t] == "sb") sber[t].EX();
				if (name[t] == "sw") swer[t].EX();
				if (name[t] == "move") mover[t].EX();
				if (name[t] == "mfhi") mfhier[t].EX();
				if (name[t] == "mflo") mfloer[t].EX();
				if (name[t] == "syscall") syscaller[t].EX();
			}
			if (k == 3)
			{
				if (status[t] <= 0) continue;
				if (name[t] == "lb") lber[t].MA();
				if (name[t] == "lw") lwer[t].MA();
				if (name[t] == "sb") sber[t].MA();
				if (name[t] == "sw") swer[t].MA();
				if (name[t] == "syscall") syscaller[t].MA();
			}
			if (k == 4)
			{
				if (status[t] <= 0) continue;
				int tmp = 0, mark = 0;
				if (name[t] == "add") {adder[t].WB(); status[t] = 0;}
				if (name[t] == "addu"){ adduer[t].WB(); status[t] = 0;}
				if (name[t] == "sub"){ suber[t].WB(); status[t] = 0;}
				if (name[t] == "subu"){ subuer[t].WB(); status[t] = 0;}
				if (name[t] == "mul"){ muler[t].WB(); status[t] = 0;}
				if (name[t] == "mulu"){ muluer[t].WB(); status[t] = 0;}
				if (name[t] == "div"){ divver[t].WB(); status[t] = 0;}
				if (name[t] == "divu"){ divvuer[t].WB(); status[t] = 0;}
				if (name[t] == "xor"){ xxorer[t].WB(); status[t] = 0;}
				if (name[t] == "xoru"){ xxoruer[t].WB(); status[t] = 0;}
				if (name[t] == "neg"){ neger[t].WB(); status[t] = 0;}
				if (name[t] == "negu"){ neguer[t].WB(); status[t] = 0;}
				if (name[t] == "rem"){ remer[t].WB(); status[t] = 0;}
				if (name[t] == "remu"){ remuer[t].WB(); status[t] = 0;}
				if (name[t] == "li"){ lier[t].WB(); status[t] = 0;}
				if (name[t] == "seq"){ seqer[t].WB(); status[t] = 0;}
				if (name[t] == "sge"){ sgeer[t].WB(); status[t] = 0;}
				if (name[t] == "sgt"){ sgter[t].WB(); status[t] = 0;}
				if (name[t] == "sle"){ sleer[t].WB(); status[t] = 0;}
				if (name[t] == "slt"){ slter[t].WB(); status[t] = 0;}
				if (name[t] == "sne"){ sneer[t].WB(); status[t] = 0;}
				if (name[t] == "b"){ tmp = bber[t].WB(); status[t] = 0;}
				if (name[t] == "beq"){ tmp = beqer[t].WB(); status[t] = 0;}
				if (name[t] == "bne"){ tmp = bneer[t].WB(); status[t] = 0;}
				if (name[t] == "bge"){ tmp = bgeer[t].WB(); status[t] = 0;}
				if (name[t] == "ble"){ tmp = bleer[t].WB(); status[t] = 0;}
				if (name[t] == "bgt"){ tmp = bgter[t].WB(); status[t] = 0;}
				if (name[t] == "blt"){ tmp = blter[t].WB(); status[t] = 0;}
				if (name[t] == "beqz"){ tmp = beqzer[t].WB(); status[t] = 0;}
				if (name[t] == "bnez"){ tmp = bnezer[t].WB(); status[t] = 0;}
				if (name[t] == "bgez"){ tmp = bgezer[t].WB(); status[t] = 0;}
				if (name[t] == "blez"){ tmp = blezer[t].WB(); status[t] = 0;}
				if (name[t] == "bgtz"){ tmp = bgtzer[t].WB(); status[t] = 0;}
				if (name[t] == "bltz"){ tmp = bltzer[t].WB(); status[t] = 0;}
				if (name[t] == "j"){ tmp = jjer[t].WB(); status[t] = 0;}
				if (name[t] == "jr"){ tmp = jrer[t].WB(); status[t] = 0;}
				if (name[t] == "jal"){ tmp = jaler[t].WB(); status[t] = 0;}
				if (name[t] == "la"){ laer[t].WB(); status[t] = 0;}
				if (name[t] == "lb"){ lber[t].WB(); status[t] = 0;}
				if (name[t] == "lw"){ lwer[t].WB(); status[t] = 0;}
				if (name[t] == "sb"){ sber[t].WB(); status[t] = 0;}
				if (name[t] == "sw"){ swer[t].WB(); status[t] = 0;}
				if (name[t] == "move"){ mover[t].WB(); status[t] = 0;}
				if (name[t] == "mfhi"){ mfhier[t].WB(); status[t] = 0;}
				if (name[t] == "mflo"){ mfloer[t].WB(); status[t] = 0;}
				if (name[t] == "syscall"){ mark = syscaller[t].WB(); status[t] = 0;}
				if (tmp != 0) 
				{
					laststone = 1; j = tmp;
				}
				if (name[t] == "syscall" && mark != -1) return mark;
			}
		}
	}
}
