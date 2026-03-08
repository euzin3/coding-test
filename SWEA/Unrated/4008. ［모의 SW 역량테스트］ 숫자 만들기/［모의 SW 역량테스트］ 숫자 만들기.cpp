#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int N;
int num[13];
int oper[4];	// +, -, *, /
int expr[13];	// N - 1개 (연산자 순서 기록) 
int min_val;
int max_val;

void func(int now) {

	if (now >= N - 1) {
		// calc
		int val = num[0];
		for (int i = 0; i < N - 1; i++) {
			if (expr[i] == 0) val += num[i + 1];
			else if (expr[i] == 1) val -= num[i + 1];
			else if (expr[i] == 2) val *= num[i + 1];
			else if (expr[i] == 3) val /= num[i + 1];
		}

		min_val = min(val, min_val);
		max_val = max(val, max_val);
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (oper[i] > 0) {
			expr[now] = i;
			oper[i]--;
			func(now + 1);
			expr[now] = 0;
			oper[i]++;
		}
	}
}

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		// init
		min_val = 200000000;
		max_val = -200000000;
		memset(oper, 0, sizeof(oper));
		memset(num, 0, sizeof(num));

		// input
		cin >> N;
		for (int i = 0; i < 4; i++)
			cin >> oper[i];

		for (int i = 0; i < N; i++) 
			cin >> num[i];
		
		// solution
		func(0);
		int ans = max_val - min_val;

		// output
		cout << "#" << tc << " " << ans << "\n";
	}
	return 0;
}