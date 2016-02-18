#include <bits/stdc++.h>

using namespace std;

class NetworkFlow
{
public:
	struct Edge 
	{
		int target, capacity, flow;
		Edge *reverse;

		int residualCapacity() const { return capacity - flow; }

		void push(int amt)
		{
			flow += amt;
			reverse->flow -= amt;
		}
	};

	NetworkFlow(int V) : V(V)
	{
		adj.resize(V);
	}

	void addEdge(int u, int v, int capacity)
	{
		Edge *uv = new Edge(), *vu = new Edge();

		uv->target = u;
		uv->capacity = capacity;
		uv->flow = 0;
		uv->reverse = vu;

		vu->target = v;
		vu->capacity = 0;
		vu->flow = 0;
		vu->reverse = uv;

		adj[u].push_back(uv);
		adj[v].push_back(vu);
	}

	int getMaximumFlow(int source, int sink)
	{
		int totalFlow = 0;

		while(true)
		{
			vector<pair<int, Edge*>> parent(V, {-1, nullptr});

			queue<int> q;
			parent[source].first = source;
			q.push(source);

			while(!q.empty() && parent[sink].first == -1)
			{
				int here = q.front();
				q.pop();

				for(size_t i=0; i < adj[here].size(); i++)
				{
					Edge *there = adj[here][i];
					int v = there->reverse->target;

					if(there->residualCapacity() > 0 && parent[v].first == -1)
					{
						q.push(v);
						parent[v] = {here, there};
					}
				}
			}

			if(parent[sink].first == -1)
				break;

			int amount = INF;
			for(int p = sink; p != source; p = parent[p].first)
				amount = min(amount, parent[p].second->residualCapacity());

			totalFlow += amount;
			for(int p = sink; p != source; p = parent[p].first)
			{
				Edge *uv = parent[p].second;
				uv->push(amount);
			}

		}

		return totalFlow;
	}

private:
	int V;
	vector<vector<Edge *>> adj;

};

int main()
{

	return 0;
}