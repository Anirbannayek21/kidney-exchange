#include<bits/stdc++.h>
using namespace std;

struct Parameter{
	int id;
	char type;
	int age;
	string bloodType;
	vector<string>antigents;
	Parameter(int v,char c,int AGE,string s,vector<string>anti)
	{
		id=v;
		type=c;
		age=AGE;
		bloodType=s;	
		antigents=anti;
	}	
};

unordered_map<string,vector<string>>give;
unordered_map<string,vector<string>>take;

void dfs(int node,unordered_map<int,set<pair<int,int>,greater<pair<int,int>> > >m,vector<int>&vis,int des,bool &flag,vector<int>&res)
{
	vis[node]=1;
//	cout<<node<<endl;
	res.push_back(node);
	if(node==des){
		flag=false;
		return;
	}
	for(auto child:m[node])
	{
		if(flag==false)break;
		int children = child.second;
//		cout<<"Child: "<<children<<endl;
		if(!vis[children])
		{
			dfs(children,m,vis,des,flag,res);
		}
//		else{
//			cout<<"Cycle Between: "<<node<<" "<<children<<endl;
//		}
	}
	if(flag==true){
		vis[node]=0;
		res.pop_back();
	}
}
int countMatchAntigen(vector<string>v1,vector<string>v2)
{
	int count=0;
	for(string st:v1)
	{
		if(find(v2.begin(),v2.end(),st)!=v2.end())
		{
			count++;
		}
	}
	return (count*100)/11;
}

int takePar(string s1,string s2)
{
	if(find(take[s1].begin(),take[s1].end(),s2)!=take[s1].end()){
		return 100;
	}
	else return 0;
}

int givePar(string s1,string s2)
{
	if(find(give[s1].begin(),give[s1].end(),s2)!=give[s1].end()){
		return 100;
	}
	else return 0;
}
int ageCompatibility(int age)
{
	if(age>=18 && age<=35){
		return 62;
	}
	else if(age>=35 && age<=49){
		return 59;
	}
	else{
		return 50;
	}
}
int main()
{
	give["a"]={"a","ab"};
    give["b"]={"b","ab"};
	give["ab"]={"ab"};
	give["o"]={"a","b","o","ab"};

	take["a"]={"a","o"};
	take["b"]={"b","o"};
	take["ab"]={"a","b","o","ab"};
	take["o"]={"o"};
	
	vector<pair<Parameter,Parameter>>node;
	
	unordered_map<int,set<pair<int,int>,greater<pair<int,int>> > >m;
	
	node.push_back({Parameter(1,'P',58,"a",{"-A", "-B", "-C" }),Parameter(1,'D',52,"ab",{"-B", "-C", "-Bw4", "-Bw6",  })});
	node.push_back({Parameter(2,'P',32,"a",{ "-DR", "-DR51","-DR52","-DR53","-DQB" }),Parameter(2,'D',53,"o",{"-A", "-DR", "-DR53","-DQB" })});
	node.push_back({Parameter(3,'P',52,"a",{"-A", "-B", "-Bw4", "-DR", "-DR51","-DR52",}),Parameter(3,'D',28,"b",{"-A","-DR52","-DR53","-DQB" })});
	
	node.push_back({Parameter(4,'P',23,"b",{"-A", "-Bw4", "-Bw6","-DQB" }),Parameter(4,'D',39,"a",{"-B", "-C", "-Bw4", "-Bw6","-DR53","-DQB" })});
	node.push_back({Parameter(5,'P',59,"b",{"-A", "-B", "-C","-DQB" }),Parameter(5,'D',25,"o",{"-Bw4", "-Bw6", "-DR", "-DR51","-DR52","-DR53","-DQB" })});
	node.push_back({Parameter(6,'P',70,"b",{"-A", "-B", "-C", "-Bw4", "-Bw6", }),Parameter(6,'D',55,"ab",{ "-DR", "-DR51","-DR52","-DR53","-DQB" })});
	
	node.push_back({Parameter(7,'P',28,"ab",{"-A", "-B", "-C", "-Bw4", "-Bw6", "-DR"}),Parameter(7,'D',27,"o",{"-A", "-B", "-C", "-Bw4", "-Bw6","-DR52","-DR53","-DQB" })});
	node.push_back({Parameter(8,'P',50,"ab",{"-A", "-Bw4", "-Bw6", "-DR", "-DR51","-DR52","-DR53" }),Parameter(8,'D',29,"a",{"-A", "-B", "-C", "-Bw4", "-Bw6", "-DR" })});
	node.push_back({Parameter(9,'P',27,"ab",{"-A", "-B", "-C", "-Bw4", "-Bw6", "-DR", "-DR51","-DR52","-DR53","-DQB" }),Parameter(9,'D',52,"b",{"-A", "-B", "-C", "-Bw4", "-Bw6", "-DR51","-DR52","-DR53","-DQB" })});
	
	node.push_back({Parameter(10,'P',33,"o",{"-A", "-B", "-C", "-Bw4", "-Bw6", "-DR", "-DR51","-DR52","-DR53","-DQB" }),Parameter(10,'D',33,"ab",{"-A", "-B", "-C", "-Bw4", "-Bw6", "-DR", "-DR51","-DR52","-DR53","-DQB" })});
	node.push_back({Parameter(11,'P',55,"o",{"-A", "-B", "-C", "-Bw4", "-Bw6","-DR53","-DQB" }),Parameter(11,'D',55,"a",{"-A", "-B", "-C", "-DR51","-DR52","-DR53","-DQB" })});
	node.push_back({Parameter(12,'P',25,"o",{"-A", "-B", "-C", "-Bw4", "-Bw6", "-DR", "-DR51","-DR52","-DR53","-DQB" }),Parameter(12,'D',40,"b",{"-A", "-B", "-C", "-Bw4", "-Bw6", "-DR", "-DR51","-DR52","-DR53","-DQB" })});
	
	
	for(int i=0;i<node.size();i++)
	{
		for(int j=0;j<node.size();j++){
			if(i!=j){
//				int takeParcentage = takePar(node[i].first.bloodType,node[j].second.bloodType);
			
				int giveParcentageBlood = givePar(node[i].second.bloodType,node[j].first.bloodType);
				int antigenCount = countMatchAntigen(node[i].second.antigents,node[j].first.antigents);
				int ageCom = ageCompatibility(node[j].second.age);
				
				int avg = (giveParcentageBlood+antigenCount+ageCom)/3;
//				int avg = (takeParcentage+giveParcentage)/2;	
				
				if(avg>=50){
					m[node[i].first.id].insert({avg,node[j].first.id});
//					m[node[j].first.id].insert({avg,node[i].first.id});
				}
			}
		}
	}
	
	for(auto a:m)
	{
		cout<<"{"<<a.first<<",D"<<"}"<<" => ";
		for(auto S:a.second){
			cout<<"{ "<<S.second<<",P,"<<S.first<<" }"<<",";
		}
		cout<<endl;
	}
	
	cout<<endl;
	
	cout<<"possible cycle:-"<<endl;
	
	for(int i=1;i<=12;i++)
	{	
		vector<int>vis(1000007,0);
		cout<<"starting with "<<i<<" :-"<<endl;
		for(auto p:m[i])
		{	
			if(!vis[i] && !vis[p.second])
			{
				vector<int>res;
				bool flag = true;
				dfs(p.second,m,vis,i,flag,res);
				if(flag==false)
				{
					for(int f:res)
					{
						cout<<f<<" ";
					}	
					cout<<endl;
				}
			}
		}
		for(auto a:m)
		{
//		pair<int,int>p = *(a.second.begin());
//		cout<<a.first<<"->"<<p.second<<endl;
			for(auto p:a.second)
			{	
				if(!vis[a.first] && !vis[p.second])
				{
					vector<int>res;
					bool flag = true;
					dfs(p.second,m,vis,a.first,flag,res);
					if(flag==false)
					{
						for(int i:res)
						{
							cout<<i<<" ";
						}	
						cout<<endl;
					}
				}
			}
		}
		for(int i=1;i<=12;i++)
		{
			if(!vis[i]){
				cout<<i<<endl;
			}
		}
	}
//	
//	for(int i=1;i<=12;i++)
//	{
//		if(!vis[i])
//		{
//			dfs(i,m,vis);
//		}
//		cout<<endl;
//	}
	
	return 0;
}
