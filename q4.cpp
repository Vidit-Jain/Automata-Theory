#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
#define ff first
#define ss second
#define pb push_back
#define file_read(x,y) freopen(x, "r", stdin); \
						freopen(y, "w", stdout);
int currState = -1, currIndex = 0, n;
set<pair<ii, char>> transitions;
typedef struct nfa NFA;
struct nfa {
	int start_state = -1, end_state = -1;
	int last_start = -1, last_end = -1;
	void push(struct nfa x) {
		last_start = x.start_state;
		last_end = x.end_state;
	}
};

string str;
NFA createNFA(int type) {
	NFA currNFA;
	currNFA.start_state = ++currState;
	if (type == 1) {
		NFA a;	
		a.start_state = a.end_state = currNFA.start_state;
		currNFA.push(a);
		for (; currIndex < n; currIndex++) {
			char c = str[currIndex];
			if (c >= 'a' && c <= 'z') {
				NFA x;
				x.start_state = ++currState;
				x.end_state = ++currState;
				transitions.insert({{currNFA.last_end, x.start_state}, 'E'});
				transitions.insert({{x.start_state, x.end_state}, c});
				currNFA.push(x);
			}
			if (c == '(') {
				NFA x = createNFA(0);
				transitions.insert({{currNFA.last_end, x.start_state}, 'E'});
				currNFA.push(x);
			}
			if (c == '*') {
				transitions.insert({{currNFA.last_start, currNFA.last_end}, 'E'});
				transitions.insert({{currNFA.last_end, currNFA.last_start}, 'E'});
			}
			if (c == '+') {
				currIndex++;
				break;
			}
			if (c == ')') 
				break;
		}
		currNFA.end_state = currNFA.last_end;
		return currNFA;
	}
	else {
		currIndex++;
		currNFA.end_state = ++currState;
		while (str[currIndex] != ')') {
			currNFA.push(createNFA(1));
			transitions.insert({{currNFA.start_state, currNFA.last_start}, 'E'});
			transitions.insert({{currNFA.last_end, currNFA.end_state}, 'E'});
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
