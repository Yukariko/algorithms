#include <bits/stdc++.h>

using namespace std;

int lis(const vector<int>& a)
{
	vector<pair<int,int>> b;
	for(auto &n : a)
	{
		auto lo = lower_bound(b.begin(), b.end(), make_pair(n,0));
		if(lo == b.end())
			b.push_back(make_pair(n,1));
		else if(lo->first == n)
			lo->second++;
		else
			*lo = make_pair(n, 1);
	}

	int ans = 0;
	for(auto &p : b)
		ans += p.second;
	return ans;
}

vector<int> lis(const vector<int>& a)
{
	int N = a.size();
	vector<int> b;
	vector<int> apos;
	vector<int> parent(N);
	
	fill(parent.begin(), parent.end(), -1);

	for(int i=0; i < N; i++)
	{
		int idx = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
		if(idx == b.size())
		{
			b.push_back(a[i]);
			apos.push_back(i);
			if(apos.size() > 1)
				parent[i] = apos[apos.size()-2];
		}
		else
		{
			b[idx] = a[i];
			apos[idx] = i;
			if(idx)
				parent[i] = apos[idx-1];
		}
	}

	int child = apos.back();
	for(int i=apos.size()-1; child != -1; i--)
	{
		b[i] = a[child];
		child = parent[child];
	}

	return b;
}
