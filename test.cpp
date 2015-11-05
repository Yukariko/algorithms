short nCm[2001][2001];
void calc_nCm(int N, int MOD)
{
	for(int i=0; i <= N; i++)
		nCm[i][0] = nCm[i][i] = 1;
	for(int i=1; i <= N; i++)
		for(int j=1; j < i; j++)
			nCm[i][j] = (nCm[i-1][j] + nCm[i-1][j-1]) % MOD;
}

long long mod_exp(long long a,long long b,long long c)
{
	a%=c;
	if(b==0)return 1;
	if(b==1)return a;
	if(b&1) return (a*mod_exp((a*a)%c,(b-1)/2,c))%c;
	return mod_exp((a*a)%c,b/2,c);
}

// 트리를 이용해 상호 배제적 집합을 구현한다.
struct DisjointSet {
	vector<int> parent, rank;

	DisjointSet(int n) : parent(n), rank(n, 1) {
		for(int i = 0; i < n; i++)
			parent[i] = i;
	}

	// u 가 속한 트리의 루트의 번호를 반환한다
	int find(int u) {
		if(u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	// u 가 속한 트리와 v 가 속한 트리를 합친다
	void merge(int u, int v) {
		u = find(u); v = find(v);
		// 이미 둘이 같은 트리에 속한 경우
		if(u == v) return;
		if(rank[u] > rank[v]) swap(u, v);
		// 이제 항상 rank[v] 가 더 크므로 u 를 v 의 자식으로 넣는다
		if(rank[u] == rank[v]) rank[v]++;
		parent[u] = v;
	}
};

const int MAX_V = 100;
int V;

vector<pair<int,int>> adj[MAX_V];

int kruskal(vector<pair<int,int>>& selected)
{
	int ret = 0;
	selected.clear();

	vector<pair<int,pair<int,int>>> edges;
	for(int u=0; u < V; u++)
	{
		for(int i=0; i < adj[u].size(); i++)
		{
			int v = adj[u][i].first, cost = adj[u][i].second;
			edges.push_back(make_pair(cost, make_pair(u,v)));
		}
	}

	sort(edges.begin(), edges.end());

	DisjointSet sets(V);

	for(int i=0; i < edges.size(); i++)
	{
		int cost = edges[i].first;
		int u = edges[i].second.first, v = edges[i].second.second;
		if(sets.find(u) == sets.find(v))
			continue;

		sets.merge(u, v);
		selected.push_back(make_pair(u, v));
		ret += cost;
	}
	return ret;
}

long long extgcd(long long a, long long b, long long* x, long long* y){
    long long d = a;
    if(b != 0){
        d = extgcd(b, a % b, y, x);
        (*y) -= (a/b) * (*x);
    }
    else{
        (*x)=1, (*y)=0;
    }
    return d;
}

const int MAX_V = 100;
const int INF = 987654321;

// 정점의 개수
int V; 
// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int,int> > adj[MAX_V];

// 음수 사이클이 있을 경우 텅 빈 배열을 반환
vector<int> bellmanFord(int src) {
	// 시작점을 제외한 모든 정점까지의 최단 거리 상한을 INF로 둔다
	vector<int> upper(V, INF);
	upper[src] = 0;
	bool updated;
	// V번 순회한다
	for(int iter = 0; iter < V; ++iter) {
		updated = false;
		for(int here = 0; here < V; ++here)
			for(int i = 0; i < adj[here].size(); i++)  {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				// (here, there) 간선을 따라 완화를 시도한다
				if(upper[there] > upper[here] + cost) {
					// 성공
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		// 모든 간선에 대해 완화가 실패할 경우 곧장 종료한다
		if(!updated) break;
	}
	// V번째 순회에서도 완화가 성공했다면 음수 사이클이 있다
	if(updated) upper.clear();
	return upper;
}