#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pi(x) printf("%d ", x)
#define pll(x) printf("%lld", x)
#define plls(x) printf("%lld ", x)
#define endl() printf("\n")
#define mp make_pair
#define pb push_back
#define fr first
#define se second
#define M 1000000007

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

vector<string> label(2);
vector<vector<string>> secret(2),secretf(2),integrity(2),declassification(2);
set<int> floatIndex;
vector<string> add;
string toAdd1,toAdd2;

vector<string> separate(string s)
{
	vector<string> ans;
	string a;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]==',')
		{
			ans.push_back(a);
			a.clear();
		}
		else
		{
			a.push_back(s[i]);
		}
	}
	if(a.length())
	{
		ans.push_back(a);
	}
	return ans;
}

vector<string> separateDot(string s)
{
	vector<string> ans;
	string a;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='.')
		{
			ans.push_back(a);
			a.clear();
		}
		else
		{
			a.push_back(s[i]);
		}
	}
	ans.push_back(a);
	return ans;
}

string separateDash(string s)
{
	string a;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='-')
		{
			a.clear();
		}
		else
		{
			a.push_back(s[i]);
		}
	}
	return a;
}

vector<string> separateDashVector(string s)
{
	vector<string> ans;
	string a;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]=='-')
		{
			ans.push_back(a);
			a.clear();
		}
		else
		{
			a.push_back(s[i]);
		}
	}
	ans.push_back(a);
	return ans;
}

void segregate(int x)
{
	int i,cnt=0;
	string a,b,c,d,s;
	for(i=0;i<label[x].length();i++)
	{
		if(label[x][i]==' ')
		{
			continue;
		}
		else if(label[x][i]=='{')
		{
			s.clear();
			continue;
		}
		else if(label[x][i]=='}')
		{
			if(cnt==0)
			{
				a=s;
			}
			else if(cnt==1)
			{
				b=s;
			}
			else if(cnt==2)
			{
				c=s;
			}
			else
			{
				d=s;
			}
			cnt++;
		}
		else
		{
			s.push_back(label[x][i]);
		}
	}
	// cout << a << endl;
	// cout << b << endl;
	// cout << c << endl;
	// cout << d << endl;
	if(label[x][1]=='C')
	{
		secret[x]=separate(a);
		integrity[x]=separate(b);
		declassification[x]=separate(c);
	}
	else
	{
		secret[x]=separate(a);
		secretf[x]=separate(b);
		integrity[x]=separate(c);
		declassification[x]=separate(d);
	}
}

bool comp(string a, string b)
{
	if(a==b)
	{
		toAdd1=a;
		toAdd2=b;
		return true;
	}
	vector<string> x=separateDot(a),y=separateDot(b);
	if(x.size()==1)
	{
		if(y.size()==1)
		{
			if(x[0]=="*" || y[0]=="*")
			{
				if(x[0]=="*")
				{
					x[0]=y[0];
				}
				else if(y[0]=="*")
				{
					y[0]=x[0];
				}
				toAdd1=x[0];
				toAdd2=y[0];
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	if(y.size()==1)
	{
		return false;
	}
	if(x[0]==y[0])
	{
		if(x[1]=="*" || y[1]=="*")
		{
			if(x[1]=="*" && y[1]=="*")
			{
				
			}
			else if(x[1]=="*")
			{
				x[1]=y[1];
			}
			else
			{
				y[1]=x[1];
			}
			toAdd1=x[0]+'.'+x[1];
			toAdd2=y[0]+'.'+y[1];
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(x[1]==y[1])
		{
			if(x[0]=="*" || y[0]=="*")
			{
				if(x[0]=="*" && y[0]=="*")
				{

				}
				else if(x[0]=="*")
				{
					x[0]=y[0];
				}
				else
				{
					y[0]=x[0];
				}
				toAdd1=x[0]+'.'+x[1];
				toAdd2=y[0]+'.'+y[1];
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if((x[0]=="*" || y[0]=="*") && (x[1]=="*" || y[1]=="*"))
			{
				if(x[0]=="*")
				{
					x[0]=y[0];
				}
				else
				{
					y[0]=x[0];
				}
				if(x[1]=="*")
				{
					x[1]=y[1];
				}
				else
				{
					y[1]=x[1];
				}
				toAdd1=x[0]+'.'+x[1];
				toAdd2=y[0]+'.'+y[1];
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool compd(string a, string b)
{
	if(b[0]=='+')
	{
		b.erase(b.begin());
		return comp(a,b);
	}
	else if(b[0]=='-')
	{

	}
	else if(b[0]=='#')
	{

	}
	else
	{
		string s=separateDash(b);
		return comp(a,s);
	}
	return true;
}

bool canRemove(string s)
{
	int i,j;
	for(i=0;i<declassification[0].size();i++)
	{
		if(declassification[0][i][0]=='-')
		{
			string a=declassification[0][i];
			a.erase(a.begin());
			return comp(s,a);
		}
	}
	return false;
}

bool canReclassify(string s)
{
	int i,j;
	for(i=0;i<declassification[0].size();i++)
	{
		if(declassification[0][i][0]=='+' || declassification[0][i][0]=='-' || declassification[0][i][0]=='#')
		{
			continue;
		}
		else
		{
			vector<string> x=separateDashVector(declassification[0][i]);
			if(comp(s,x[0]))
			{
				for(j=0;j<secret[1].size();j++)
				{
					if(comp(x[1],secret[1][j]))
					{
						return true; 
					}
				}
				for(j=0;j<secretf[1].size();j++)
				{
					if(comp(x[1],secretf[1][j]))
					{
						floatIndex.insert(j);
						add.push_back(toAdd2);
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool isSecrecyOkay()
{
	bool ok=true;
	int i,j;
	vector<int> z;
	for(i=0;i<secret[0].size();i++)
	{
		bool done=false;
		for(j=0;j<secret[1].size();j++)
		{
			if(comp(secret[0][i],secret[1][j]))
			{
				done=true;
				break;
			}
		}
		if(done)
		{
			continue;
		}
		for(j=0;j<secretf[1].size();j++)
		{
			if(comp(secret[0][i],secretf[1][j]))
			{
				floatIndex.insert(j);
				add.push_back(toAdd2);
				done=true;
				break;
			}
		}
		if(done)
		{
			continue;
		}
		if(canRemove(secret[0][i]))
		{
			done=true;
			continue;
		}
		if(canReclassify(secret[0][i]))
		{
			done=true;
			continue;
		}
		if(!done)
		{
			return false;
		}
	}
	return true;
}

bool isIntegrityOkay()
{
	bool ok=true;
	int i,j;
	for(i=0;i<integrity[1].size();i++)
	{
		bool done=false;
		for(j=0;j<integrity[0].size();j++)
		{
			if(comp(integrity[1][i],integrity[0][j]))
			{
				done=true;
				break;
			}
		}
		if(done)
		{
			continue;
		}
		for(j=0;j<declassification[0].size();j++)
		{
			if(compd(integrity[1][i],declassification[0][j]))
			{
				done=true;
				break;
			}
		}
		if(!done)
		{
			return false;
		}
	}
	return true;
}

int main() 
{
    fastIO();
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    getline(cin,label[0]);
    getline(cin,label[1]);
    segregate(0);
    segregate(1);
    bool ok1=isSecrecyOkay();
    bool ok2=isIntegrityOkay();
    if(ok1 && ok2)
    {
    	cout << "Enable data flow" << endl;
    	cout << label[0] << endl;
    	if(label[1][1]=='C')
    	{
    		cout << label[1] << endl;
    	}
    	else
    	{
    		string ans;
    		bool ok=true;
    		ans.append("(F({");
    		for(int i=0;i<secret[1].size();i++)
    		{
    			ans.append(secret[1][i]);
    			ans.push_back(',');
    		}
    		for(int i=0;i<add.size();i++)
    		{
    			ans.append(add[i]);
    			ans.push_back(',');
    		}
    		ans.pop_back();
    		ans.append("}, {");
    		for(int i=0;i<secretf[1].size();i++)
    		{
    			if(floatIndex.find(i)==floatIndex.end())
    			{
    				ok=false;
    				ans.append(secretf[1][i]);
    				ans.push_back(',');
    			}
    		}
    		if(!ok)
    		{
    			ans.pop_back();
    			ok=true;
    		}
    		ans.append("}), {");
    		for(int i=0;i<integrity[1].size();i++)
    		{
    			ok=false;
    			ans.append(integrity[1][i]);
    			ans.push_back(',');
    		}
    		if(!ok)
    		{
    			ans.pop_back();
    			ok=true;
    		}
    		ans.append("}, {");
    		for(int i=0;i<declassification[1].size();i++)
    		{
    			ok=false;
    			ans.append(declassification[1][i]);
    			ans.push_back(',');
    		}
    		if(!ok)
    		{
    			ans.pop_back();
    			ok=true;
    		}
    		ans.append("})");
    		cout << ans << endl;
    	}
    }
    else
    {
    	cout << "Restrict data flow" << endl;
    }
    return 0;
}
