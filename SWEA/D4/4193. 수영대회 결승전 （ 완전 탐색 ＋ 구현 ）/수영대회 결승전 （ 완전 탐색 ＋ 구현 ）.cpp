#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;

int N;
int map[16][16];
bool visited[16][16][3];
int A, B; // 시작 위치
int C, D; // 도착 위치

int ydir[] = { -1, 1, 0, 0 };
int xdir[] = { 0, 0, -1, 1 };

struct Node {
	int y, x, time; // 현재 시간
};

int bfs() {
	queue<Node> q;
	visited[A][B][0] = true;
	q.push({ A, B, 0 });

	while (!q.empty()) {
		Node now = q.front(); q.pop();

		if (now.y == C && now.x == D) return now.time;
		int nextTime = now.time + 1;

		for (int i = 0; i < 4; i++) {
			int ny = now.y + ydir[i];
			int nx = now.x + xdir[i];

			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if (map[ny][nx] == 1) continue;

			// 소용돌이
			if (map[ny][nx] == 2 && now.time % 3 != 2) {
				// 1초 기다림
				if (!visited[now.y][now.x][nextTime % 3]) {
					visited[now.y][now.x][nextTime % 3] = true;
					q.push({ now.y, now.x, nextTime });
				}
				continue;
			}
			if (visited[ny][nx][nextTime % 3]) continue;

			visited[ny][nx][nextTime % 3] = true;
			q.push({ ny, nx, nextTime });
		}
	}
	return -1;
}


int main() {
	int T; 
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		// input
		cin >> N;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}
		cin >> A >> B >> C >> D;

		// simulation
		memset(visited, false, sizeof(visited));
		int ret = bfs();

		// output
		cout << "#" << tc << " " << ret << "\n";
	}
	return 0;
}