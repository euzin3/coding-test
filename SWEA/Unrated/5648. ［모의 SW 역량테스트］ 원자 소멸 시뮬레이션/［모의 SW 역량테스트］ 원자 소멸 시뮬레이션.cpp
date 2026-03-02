#include <iostream>
#include <vector>
using namespace std;

int N;
int map[4001][4001];
struct Atom {
	int x, y;
	int dir;
	int K;
};

int dirX[] = { 0, 0, -1, 1 };
int dirY[] = { 1, -1, 0, 0 };

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> N; // 원자 수
		vector<Atom> atom(N);

		for (int i = 0; i < N; i++) {
			int x, y, dir, K;
			cin >> x >> y >> dir >> K;
			atom[i] = { x*2 + 2000, y*2 + 2000, dir, K }; // 0.5 경우 처리
		}

		// simulation
		int sum = 0;
		int time = 0;

		while (!atom.empty() && time <= 4000) {
			time++;

			// 1. 모든 atom 이동
			for (auto& a : atom) {
				a.x += dirX[a.dir];
				a.y += dirY[a.dir];
			}

			// 2. 이동 위치 기준 map 업데이트 (count)
			for (auto& a : atom) {
				if (a.x < 0 || a.x > 4000 || a.y < 0 || a.y > 4000)
					continue;
				map[a.x][a.y]++;
			}

			// 3. 충돌 처리
			vector<Atom> next;

			for (auto& a : atom) {
				// 범위 벗어난 경우 제거
				if (a.x < 0 || a.x > 4000 || a.y < 0 || a.y > 4000)
					continue;
				
				int nx = a.x + 2000;
				int ny = a.y + 2000;

				// 충돌 발생
				if (map[a.x][a.y] >= 2)
					sum += a.K;
				else
					next.push_back(a);
			}

			// 맵 초기화
			for (auto& a : atom) {
				if (a.x < 0 || a.x > 4000 || a.y < 0 || a.y > 4000)
					continue;
				map[a.x][a.y] = 0;
			}
			atom = next;
		}
		cout << "#" << tc << " " << sum << "\n";
	}
	return 0;
}