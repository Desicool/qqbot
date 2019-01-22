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
	void spfa(int s) {
		memset(dist, 0x3f, sizeof(dist));
		memset(vis, 0, sizeof(vis));
		dist[s] = 0;
		priority_queue<node> que;
		que.push(node(s, 0));
		while (!que.empty()) {
			node p = que.top();
			que.pop();
			if (vis[p.v]) {
				continue;
			}
			vis[p.v] = true;
			for (int i = p2[p.v]; ~i; i = G2[i].nxt) {
				int v = G2[i].v, w = G2[i].w;
				if (!vis[v] && p.d + w < dist[v]) {
					dist[v] = p.d + w;
					que.push(node(v, dist[v]));
				}
			}
		}
	}
public:
	SPFA();
	SPFA(int s, int e);
	~SPFA();
};

