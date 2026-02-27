#include <iostream>
#include <cstring>
using namespace std;

int N;
char map[301][301];
int visited[301][301];
int click = 0;

int ydir[8] = { -1,-1,-1,0,1,1,1,0 };
int xdir[8] = { -1,0,1,1,1,0,-1,-1 };

// 주변 지뢰 개수 세기
int count(int y, int x) {
	int cnt = 0;

	for (int i = 0; i < 8; i++) {
		int ny = y + ydir[i];
		int nx = x + xdir[i];

		if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
		if (map[ny][nx] == '*') cnt += 1;
	}
	return cnt;
}

// 0 영역 확장 
void dfs(int y, int x) {
	visited[y][x] = 1;

	if (count(y, x) != 0) return;

	for (int i = 0; i < 8; i++) {
		int ny = y + ydir[i];
		int nx = x + xdir[i];

		if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
		if (visited[ny][nx]) continue;
		if (map[ny][nx] == '*') continue;

		dfs(ny, nx);
	}
	
}


int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> map[i];
		}
		
		memset(visited, 0, sizeof(visited));
		click = 0;
		// 0 영역부터 처리
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] == '.' && !visited[i][j]) {
					if (count(i, j) == 0) {
						click++;
						dfs(i, j);
					}
				}
			}
		}
		// 남은 숫자 칸 처리
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] == '.' && !visited[i][j]) {
					click++;
				}
			}
		}
		cout << "#" << tc << " " << click << "\n";
	}
	return 0;
}