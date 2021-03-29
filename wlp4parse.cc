#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class MY {
public:
	int begin;
	int end;
	string IPT;
	string OPE;
	MY(int a, int b, string c, string d);
};

MY::MY(int a, int b, string c, string d) {
	this->begin = a;
	this->end = b;
	this->IPT = c;
	this->OPE = d;
}

class tree {
public:
	vector<string> a;
	vector<tree* > b;
	tree(vector <string> c, vector<tree* > d);
	void printtree();
	~tree() {
		for (vector<tree*>::iterator it = b.begin(); it != b.end(); it++) {  // delete all subtrees
			delete(*it);
		}
	}
};

void des(vector<tree* > b) {
	for (vector<tree*>::iterator it = b.begin(); it != b.end(); it++) {  // delete all subtrees
		delete(*it);
	}
}
void tree::printtree() {
	int leng = this->a.size();
	for (int i = 0; i < leng; i++) {
		cout << this->a[i] << " ";
	}
	cout << endl;
	int len = this->b.size();
	for (int i = 0; i < len; i++) {
		this->b[i]->printtree();
	}
}
tree::tree(vector <string> c, vector<tree* > d) {
	a = c;
	b = d;
}

void getmy(map<int, vector<string>>& M, vector<MY>& T, stack<int>& I)
{
	ifstream in("my.txt");
	int skip;
	string temp;
	//
	in >> skip;

	skip++;
	while (skip--) {
		getline(in, temp);
	}
	//
	in >> skip;
	skip++;
	while (skip--) {
		getline(in, temp);
	}
	in >> temp;
	int mylength;
	in >> mylength;
	string temp3;
	getline(in, temp);
	int index = mylength;
	while (mylength--)
	{
		vector<string> temp2;
		getline(in, temp);
		istringstream myget(temp);
		while (myget >> temp3) {
			temp2.push_back(temp3);
		}
		M[index - mylength - 1] = temp2;
	}

	in >> skip >> mylength;
	while (mylength--)
	{
		int a;
		int b;
		string c;
		string d;

		in >> a;
		in >> c;
		in >> d;
		in >> b;
		MY temp4(a, b, c, d);
		T.push_back(temp4);
	}

	I.push(0);
}

int checkreduce(MY& samp, int c, string a, string b, int Mode)
{
	if (Mode == 1) {
		return (samp.IPT == a && samp.begin == c && samp.OPE == b);
	}
	else {
		return (samp.IPT == a && samp.begin == c);
	}
}

int main()
{
	vector<tree* > d;
	vector<tree* > e;
	int tokennum = 0;
	map<int, vector<string>> rule;
	vector<MY> vecmy;
	stack<int> vecth;
	stack<tree*> vecsym;
	string start = "start";
	getmy(rule, vecmy, vecth);
	int getnum = 0;
	int nex = 0;
	int tem = 0;
	int len = 0;
	int red = 0;
	string input;
	string type;
	vector<string> vecstate;
	vector<vector<string>> answer;
	vector<string> thisrec;
	input = "BOF";
	type = "BOF";
	nex = 0;
	len = vecmy.size();
	tem = vecmy.size();
	while (len--) {
		if (checkreduce(vecmy[tem - len - 1], vecth.top(), input, "", 0)) {
			nex = vecmy[tem - len - 1].end;
		}
	}
	if (nex == 0)
	{
		des(e);
		cerr << "ERROR at " << 1 + tokennum << endl;
		return 0;
	}
	thisrec.push_back(input);
	thisrec.push_back(type);
	answer.push_back(thisrec);
	e.push_back(new tree(thisrec, d));
	thisrec.clear();
	vecth.push(nex);
	vecstate.push_back(input);

	while (cin >> input) {
		vector<string> thisrec;
		cin >> type;

		thisrec.clear();
		for (vector<MY>::iterator it = vecmy.begin(); it != vecmy.end(); ++it)
		{
			if (checkreduce(*it, vecth.top(), input, "reduce", 1)) {
				red = 1;
			}
		}
		while (red)
		{

			len = vecmy.size();
			tem = vecmy.size();
			while (len--) {
				if (checkreduce(vecmy[tem - len - 1], vecth.top(), input, "reduce", 1)) {
					getnum = vecmy[tem - len - 1].end;
				}
			}
			int leng = e.size();

			for (vector<string>::iterator it = rule[getnum].begin(); it != rule[getnum].end(); ++it) {
				thisrec.push_back(*it);

			}

			len = rule[getnum].size() - 1;


			for (int i = 0; i < len; i++) {
				int length = e.size();

				tree* node = e[length - len + i];
				d.push_back(node);
				e.erase(e.begin() + length - len + i);
			}

			tree* mom = new tree(thisrec, d);
			d.clear();
			e.push_back(mom);
			thisrec.clear();
			len = rule[getnum].size() - 1;
			tem = len;
			while (len--) {
				vecth.pop();
			}
			while (tem--) {
				vecstate.pop_back();
			}
			vecstate.push_back(rule[getnum][0]);
			len = vecmy.size();
			tem = vecmy.size();
			while (len--)
				if (checkreduce(vecmy[tem - len - 1], vecth.top(), rule[getnum][0], "", 0))
					nex = vecmy[tem - len - 1].end;
			vecth.push(nex);
			nex = 0;
			red = 0;
			getnum = 0;

			for (vector<MY>::iterator it = vecmy.begin(); it != vecmy.end(); ++it)
			{
				if (checkreduce(*it, vecth.top(), input, "reduce", 1)) {
					red = 1;
				}
			}
		}
		thisrec.push_back(input);
		thisrec.push_back(type);
		answer.push_back(thisrec);
		e.push_back(new tree(thisrec, d));
		thisrec.clear();
		nex = 0;
		len = vecmy.size();
		tem = vecmy.size();
		while (len--) {
			if (checkreduce(vecmy[tem - len - 1], vecth.top(), input, "", 0)) {
				nex = vecmy[tem - len - 1].end;
			}
		}
		if (nex == 0)
		{
			des(e);
			cerr << "ERROR at " << 1 + tokennum << endl;
			return 0;
		}

		vecth.push(nex);
		vecstate.push_back(input);
		tokennum++;
	}

	input = "EOF";
	type = "EOF";
	d.clear();
	thisrec.clear();

	for (vector<MY>::iterator it = vecmy.begin(); it != vecmy.end(); ++it)
	{
		if (checkreduce(*it, vecth.top(), input, "reduce", 1)) {
			red = 1;
		}
	}
	while (red)
	{

		len = vecmy.size();
		tem = vecmy.size();
		while (len--) {
			if (checkreduce(vecmy[tem - len - 1], vecth.top(), input, "reduce", 1)) {
				getnum = vecmy[tem - len - 1].end;
			}
		}
		int leng = e.size();

		for (vector<string>::iterator it = rule[getnum].begin(); it != rule[getnum].end(); ++it) {
			thisrec.push_back(*it);

		}

		len = rule[getnum].size() - 1;


		for (int i = 0; i < len; i++) {
			int length = e.size();
			tree* node = e[leng - len + i];
			d.push_back(node);



		}
		for (int i = 0; i < len; i++) {
			e.pop_back();
		}
		tree* mom = new tree(thisrec, d);
		d.clear();
		e.push_back(mom);
		thisrec.clear();
		len = rule[getnum].size() - 1;
		tem = len;
		while (len--) {
			vecth.pop();
		}
		while (tem--) {
			vecstate.pop_back();
		}
		vecstate.push_back(rule[getnum][0]);
		len = vecmy.size();
		tem = vecmy.size();
		while (len--)
			if (checkreduce(vecmy[tem - len - 1], vecth.top(), rule[getnum][0], "", 0))
				nex = vecmy[tem - len - 1].end;
		vecth.push(nex);
		nex = 0;
		red = 0;
		getnum = 0;

		for (vector<MY>::iterator it = vecmy.begin(); it != vecmy.end(); ++it)
		{
			if (checkreduce(*it, vecth.top(), input, "reduce", 1)) {
				red = 1;
			}
		}
	}
	nex = 0;
	len = vecmy.size();
	tem = vecmy.size();
	while (len--) {
		if (checkreduce(vecmy[tem - len - 1], vecth.top(), input, "", 0)) {
			nex = vecmy[tem - len - 1].end;
		}
	}
	if (nex == 0)
	{
		des(e);
		cerr << "ERROR at " << 1 + tokennum << endl;
		return 0;
	}
	thisrec.push_back(input);
	thisrec.push_back(type);
	d.clear();
	e.push_back(new tree(thisrec, d));
	cout << "start BOF procedures EOF" << endl;
	for (int i = 0; i < e.size(); i++) {
		e[i]->printtree();
	}
	des(e);
	return 0;
}



