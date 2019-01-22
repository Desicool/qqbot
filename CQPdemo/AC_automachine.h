#pragma once
#include <queue>
using namespace std;
class AC_automachine
{
	struct Trie {
		int next[500010][26], fail[500010], end[500010];
		int root, L;
		int newnode() {
			for (int i = 0;i < 26;i++) 
				next[L][i] = -1; end[L++] = 0;
			return L-1;
		}
		void init() 
		{ 
			L = 0;
			root = newnode(); 
		}
		void insert(char buf[]);
		void build();
		int query(char buf[]);
	}trie;
public:
	AC_automachine();
	~AC_automachine();
};

