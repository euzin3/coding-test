#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

int N;
int map[101][101];

int dirY[] = { -1, 1, 0, 0 }; // 상(0) 하(1) 좌(2) 우(3)
int dirX[] = { 0, 0, -1, 1 };

// 해당 블록을 만났을 때 방향 변화
int bk[6][4] = {
	{},
	{1,3,0,2}, // 상->하, 하->우, 좌-> 상, 우 -> 좌
	{3,0,1,2},
	{2,0,3,1},
	{1,2,3,0},
	{1,0,3,2}
};

struct Coord {
	int y, x;
};
vector<Coord> wormhole[11];

/*
	블록 : 1~5
	웜홀 : 6~10 (pair) / 최대 5쌍
	블랙홀 : -1 / 최대 5개
*/

int simulation(int sy, int sx, int dir) {
	int y = sy, x = sx;
	int score = 0;

	while (1) {
		// 이동 
		y += dirY[dir];
		x += dirX[dir];
		
		// 벽 처리
		if (y < 0 || x < 0 || y >= N || x >= N) {
			dir = bk[5][dir];
			score++;
			continue;
		}

		// 종료 조건
		if (map[y][x] == -1) break;
		if (y == sy && x == sx) break;

		// 블록 처리
		if (map[y][x] >= 1 && map[y][x] <= 5) {
			int num = map[y][x];
			dir = bk[num][dir];
			score++;
		}
		// 웜홈 처리 
		if (map[y][x] >= 6 && map[y][x] <= 10) {
			int num = map[y][x];
			if (wormhole[num][0].y == y && wormhole[num][0].x == x)
				y = wormhole[num][1].y, x = wormhole[num][1].x;
			else 
				y = wormhole[num][0].y, x = wormhole[num][0].x;
		}
	}
	return score;
}

int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		// init
		for (int i = 6; i <= 10; i++)
			wormhole[i].clear();

		// input
		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
				// 웜홀 매칭
				if (map[i][j] >= 6 && map[i][j] <= 10)
					wormhole[map[i][j]].push_back({ i, j });
			}
		}

		// 모든 시작점 탐색
		int ret = -1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] == 0) {
					for (int dir = 0; dir < 4; dir++) {
						int score = simulation(i, j, dir);
						ret = max(ret, score);
					}
				}
			}
		}
		
		// output
		cout << "#" << tc << " " << ret << "\n";
	}
	return 0;
}
