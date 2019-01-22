#include "stdafx.h"
#include "SPFA.h"


SPFA::SPFA()
{
}
void SPFA::spfa(int s) {
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
SPFA::SPFA(int s, int e)
{

}
SPFA::~SPFA()
{
}
