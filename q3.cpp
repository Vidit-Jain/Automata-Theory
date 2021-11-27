#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
#define ff first
#define ss second
#define file_read(x,y) freopen(x, "r", stdin); \
						freopen(y, "w", stdout);
int n, k, a;
vvi adj; 
map<int, int> m;
int same(int a, int b) {
	for (int i = 0; i < 26; i++) {
		if (adj[a][i] == -1 && adj[b][i] == -1) continue;
		if (adj[a][i] == -1 || adj[b][i] == -1) return false;
		if (m[adj[a][i]] != m[adj[b][i]]) return false;
	}
	return true;
}
void equivalence(int num) {
	map<int, int> next;
	int count = -1;
	for (int i = 0; i < n; i++) {
		if (next.find(i) == next.end()) {
			count++;	
			next[i] = count;
			for (int j = i + 1; j < n; j++) {
				if (next.find(j) != next.end()) continue;				
				if (m[i] == m[j] && same(i, j)) next[j] = count;
			}
		}
	}
	m = next;
	if (num == count) return;
	equivalence(count);
}
int main(){
	cin >> n >> k >> a;
	vi accept(a);
	for (auto& s : accept) cin >> s;
	adj.assign(n, vi(26, -1));
	for (int i = 0; i < k; i++) {
		int a, b;
		char c;
		cin >> a >> c >> b;
		adj[a][c - 'a'] = b;
	}
	for (int i = 0; i < n; i++) m[i] = 0;
	for (auto& s : accept) m[s] = 1;

	equivalence(1);	
	set<int> minimised_accept;
	for (auto& s : accept) {
		minimised_accept.insert(m[s]);
	}
	int largest = 0;
	set<pair<ii,char>> transitions;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 26; j++) {
			if (adj[i][j] == -1) continue;
			transitions.insert({{m[i], m[adj[i][j]]}, j + 'a'});
			largest = max(largest, m[i]);
		}
	}
	cout << largest + 1 << " " << transitions.size() << " " << minimised_accept.size() << "\n";
	for (auto &s : minimised_accept) cout << s << " ";
	cout << "\n";
	for (auto &s : transitions) cout << s.ff.ff << " " << s.ss << " " << s.ff.ss << "\n";
}
