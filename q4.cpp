#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
#define ff first
#define ss second
#define pb push_back
#define file_read(x,y) freopen(x, "r", stdin); \
						freopen(y, "w", stdout);
int currState = -1, currIndex = 0, n;
vector<pair<ii, char>> transitions;
typedef struct nfa {
	int start_state = -1, end_state = -1;
	vector<struct nfa> nfas;
} NFA;

string str;
NFA createNFA(int type) {
	NFA currNFA;
	currNFA.start_state = ++currState;
	if (type == 1) {
		NFA a;	
		a.start_state = a.end_state = currNFA.start_state;
		currNFA.nfas.pb(a);

		for (; currIndex < n; currIndex++) {
			char c = str[currIndex];
			if (c >= 'a' && c <= 'z') {
				NFA x;
				x.start_state = ++currState;
				x.end_state = ++currState;
				NFA b = currNFA.nfas[currNFA.nfas.size() - 1];
				transitions.pb({{b.end_state, x.start_state}, 'E'});
				transitions.pb({{x.start_state, x.end_state}, c});
				currNFA.nfas.pb(x);
			}
			if (c == '(') {
				NFA x = createNFA(0);
				NFA b = currNFA.nfas[currNFA.nfas.size() - 1];
				transitions.pb({{b.end_state, x.start_state}, 'E'});
				currNFA.nfas.pb(x);
			}
			if (c == '*') {
				NFA a = currNFA.nfas[currNFA.nfas.size() - 1];
				NFA b = currNFA.nfas[currNFA.nfas.size() - 2];
				transitions.pb({{a.end_state, a.start_state}, 'E'});
			}
			if (c == '+') {
				currIndex++;
				break;
			}
			if (c == ')') 
				break;
		}
		currNFA.end_state = currNFA.nfas[currNFA.nfas.size() - 1].end_state;
		return currNFA;
	}
	else {
		currIndex++;
		currNFA.end_state = ++currState;
		while (str[currIndex] != ')') {
			currNFA.nfas.pb(createNFA(1));
		}
		for (auto& s : currNFA.nfas) {
			transitions.pb({{currNFA.start_state, s.start_state}, 'E'});
			transitions.pb({{s.end_state, currNFA.end_state}, 'E'});
		}
	}
	return currNFA;
}
int main(int argc, char* argv[]){
	if (argc != 3) {
		cout << "Wrong number of arguments\n";
		return 0;
	}
	file_read(argv[1], argv[2]);
	getline(cin, str);
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
	str = '(' + str + ')';
	n = str.size();
	NFA x = createNFA(0);
	cout << currState + 1 << " " << transitions.size() << " " << 1 << "\n";
	cout << x.end_state << "\n";
	for (auto& s : transitions) {
		cout << s.ff.ff << " " << s.ss << " " << s.ff.ss << "\n";
	}
}
