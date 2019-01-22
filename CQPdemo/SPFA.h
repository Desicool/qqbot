#pragma once
#include <queue>
using namespace std;
class SPFA
{
	struct edge {
		int v, w, nxt;
	}G[10005], G2[10005];
	int tot, pre[10005], t2, p2[10005];
	void add(int u, int v, int w) {
		G[tot].v = v;
		G[tot].w = w;
		G[tot].nxt = pre[u];
		pre[u] = tot++;
		G2[t2].v = u;
		G2[t2].w = w;
		G2[t2].nxt = p2[v];
		p2[v] = t2++;
	}
	struct node {
		int v, d;
		node() {}
		node(int v, int d) : v(v), d(d) {}
		bool operator < (const node &b) const {
			if (d != b.d) {
				return d > b.d;
			}
			else {
				return v > b.v;
			}
		}
	};
	int n, m, k, dist[10005], s, e, T;
	bool vis[10005];
	void spfa(int s);
public:
	SPFA();
	SPFA(int s, int e);
	~SPFA();
};

