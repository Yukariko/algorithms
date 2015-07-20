#include <algorithm>

using namespace std;

struct edge {
	int x,y,w;
};

class kruskal {
public:

	kruskal(edge *e, int n, int m)
	{	
		sort(e, e + m, cmp);

		jump = new int[n+1];
		r = new int[n+1]{};

		for(int i=1;i<=n;i++)
			jump[i]=i;

		res = 0;
		for(int i=0;i<m;i++)
		{
			int x=e[i].x,y=e[i].y;
			if(find(x)!=find(y))
			{
				merge(x,y);
				res+=e[i].w;
			}
		}
	}

	long long calc()
	{
		return res;
	}

	int find(int n)
	{
		if(n==jump[n])return n;
		return jump[n]=find(jump[n]);
	}

	void merge(int x, int y)
	{
		x=find(x);
		y=find(y);
		if(r[x]<r[y])jump[x]=y;
		else
		{
			jump[y]=x;
			if(r[x]==r[y])r[x]++;
		}
	}

	static bool cmp(const edge &a,const edge &b)
	{
		return a.w < b.w;
	}

private:
	int *jump;
	int *r;
	long long res;
};

int main(){}