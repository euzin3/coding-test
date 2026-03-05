#include <iostream>
#include <cstring>
using namespace std;

int K;
int arr[5][8]; // 4개의 톱니바퀴 (1~4)


// 시계 방향 한 칸씩 이동 (1)
void Clockwise(int num) {
	int temp = arr[num][7];
	for (int i = 6; i >= 0; i--) {
		arr[num][i + 1] = arr[num][i];
	}
	arr[num][0] = temp;
}


// 반시계방향 한 칸씩 이동 (-1)
void Counterclockwise(int num) {
	int temp = arr[num][0];
	for (int i = 0; i <= 6; i++) {
		arr[num][i] = arr[num][i + 1];
	}
	arr[num][7] = temp;
}

void move(int num, int dir) {
	if (dir == 1) Clockwise(num);
	else if (dir == -1) Counterclockwise(num);
}


void simulation(int num, int dir) {

	int rotate[5] = { 0 }; // 각 톱니의 회전 방향 
	rotate[num] = dir;

	// 왼쪽 
	for (int i = num; i > 1; i--) {
		if (arr[i][6] != arr[i - 1][2])
			rotate[i - 1] = -rotate[i];
		else
			break;
	}

	// 오른쪽 
	for (int i = num; i < 4; i++) {
		if (arr[i][2] != arr[i + 1][6])
			rotate[i + 1] = -rotate[i];
		else
			break;
	}

	// 회전
	for (int i = 1; i <= 4; i++) {
		if (rotate[i] == 1) Clockwise(i);
		else if (rotate[i] == -1) Counterclockwise(i);
	}
}


int main() {
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> K;

		for (int i = 1; i < 5; i++) {
			for (int j = 0; j < 8; j++) {
				cin >> arr[i][j];
			}
		}

		for (int i = 0; i < K; i++) {
			int num, dir;
			cin >> num >> dir;
			simulation(num, dir);
		}

		int sum = 0;
		int point[] = { 0, 1, 2, 4, 8 };
		for (int i = 1; i < 5; i++) {
			if (arr[i][0] == 1) sum += point[i];
		}

		cout << "#" << tc << " " << sum << "\n";
	}
	return 0;
}