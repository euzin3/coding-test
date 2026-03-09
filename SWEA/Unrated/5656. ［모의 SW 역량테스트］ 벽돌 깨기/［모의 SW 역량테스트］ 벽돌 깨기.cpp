#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

int N, W, H;
int map[16][16];
int ret;

int dirY[] = { -1, 1, 0, 0 };
int dirX[] = { 0, 0, -1, 1 };

struct Node {
	int y, x, power;
};

void debugging() {
	cout << "\n";
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cout << map[i][j] << " ";
		} cout << "\n";
	} cout << "\n";
}

void crack(int y, int x) {

	queue<Node> q;
	q.push({ y, x, map[y][x] });
	map[y][x] = 0;

	while (!q.empty()) {
		Node now = q.front(); q.pop();

		int power = now.power;

		for (int i = 0; i < 4; i++) {
			// 한 방향씩 처리
			for (int k = 1; k < power; k++) {
				int ny = now.y + dirY[i] * k;
				int nx = now.x + dirX[i] * k;

				if (ny < 0 || nx < 0 || ny >= H || nx >= W) break;
				if (map[ny][nx] == 0) continue;
			
				if (map[ny][nx] > 1) q.push({ ny, nx, map[ny][nx] }); // 연쇄 작용
				
				map[ny][nx] = 0; // 벽돌 깨기
			}
		}
	}
}


void drop() {
	for (int j = 0; j < W; j++) {
		int move_point = H-1;
		// 아래에서부터 처리
		for (int i = H-1; i >= 0; i--) {
			if (map[i][j] != 0) {
				map[move_point][j] = map[i][j];

				if (move_point != i) 
					map[i][j] = 0;

				move_point--;
			}
		}
	}
}

int count() {
	int cnt = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (map[i][j] != 0) cnt++;
		}
	}
	return cnt;
}

void simulation(int depth) {
	if (depth == N) {
		ret = min(ret, count());
		return;
	}

	int backup[16][16];
	memcpy(backup, map, sizeof(map));

	for (int col = 0; col < W; col++) {
		// 공 떨어드릴 위치 찾기 
		int y = -1;

		for (int i = 0; i < H; i++) {
			if (map[i][col] != 0) {
				y = i;
				break;
			}
		}

		if (y == -1) {
			simulation(depth + 1);
			continue;
		}

		crack(y, col);
		drop();
		simulation(depth + 1);
		memcpy(map, backup, sizeof(map));
	}
}


int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		// input
		cin >> N >> W >> H;
		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> map[i][j];
			}
		}

		// simulation
		ret = H * W;
		simulation(0);

		// output
		cout << "#" << tc << " " << ret << "\n";
	}
	return 0;
}