#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int N;
int map[17][17];
int ans;
int bundle[17]; // index : 식재료 번호 value : 1 (A) 0 (B)

int sinergy() {
	int a_sum = 0, b_sum = 0;

	for (int i = 1; i <= N - 1; i++) {
		for (int j = i + 1; j <= N; j++) {
			if (bundle[i] == 1 && bundle[j] == 1) {
				a_sum += map[i][j] + map[j][i];
			}
			if (bundle[i] == 0 && bundle[j] == 0) {
				b_sum += map[i][j] + map[j][i];
			}
		}
	}
	return abs(a_sum - b_sum);
}


// 식재료 N/2개 고르기
void select(int now, int start) {
	if (now >= N/2) {
		int diff = sinergy();
		ans = min(ans, diff);
		return;
	}
	for (int i = start; i <= N; i++) {
		bundle[i] = 1;
		select(now + 1, i + 1);
		bundle[i] = 0;
	}
}


int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> map[i][j];
			}
		}
		ans = 100000;
		memset(bundle, 0, sizeof(bundle));
		select(0, 1);

		cout << "#" << tc << " " << ans << "\n";
	}
	return 0;
}