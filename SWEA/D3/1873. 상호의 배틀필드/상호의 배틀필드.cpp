#include <iostream>
#include <string>
using namespace std;

int H, W, N;
string map[21];
string n;
int y, x;

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
char tank[4] = { '^', 'v', '<', '>' };

int getDir1(char c) {
    if (c == '^') return 0;
    if (c == 'v') return 1;
    if (c == '<') return 2;
    if (c == '>') return 3;
    return -1;
}

int getDir2(char c) {
    if (c == 'U') return 0;
    if (c == 'D') return 1;
    if (c == 'L') return 2;
    if (c == 'R') return 3;
    return -1;
}

int check(int ny, int nx) {
    if (ny < 0 || nx < 0 || ny >= H || nx >= W) return 0;
    else return 1;
}

void move(int dir) {
    map[y][x] = tank[dir];

    int ny = y + dy[dir];
    int nx = x + dx[dir];

    if (check(ny, nx) && map[ny][nx] == '.') {
        map[y][x] = '.';
        y = ny;
        x = nx;
        map[y][x] = tank[dir];
    }
}

void shoot(int dir) {
    int ny = y;
    int nx = x;

    while (1) {
        ny += dy[dir];
        nx += dx[dir];

        if (!check(ny, nx)) break;

        if (map[ny][nx] == '*') {
            map[ny][nx] = '.';
            break;
        }
        else if (map[ny][nx] == '#') {
            break;
        }
    }
}


void func(char input) {
    if (input == 'S') {
        int dir = getDir1(map[y][x]);
        shoot(dir);
    }
    else {
        int dir = getDir2(input);
        move(dir);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        // input
        cin >> H >> W;
        for (int i = 0; i < H; i++)  cin >> map[i];
        cin >> N >> n;
        
        // 전차 초기 위치
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (map[i][j] == '^' || map[i][j] == 'v' ||
                    map[i][j] == '<' || map[i][j] == '>')
                    y = i, x = j;
            }
        }

        // 입력 하나씩 처리 
        for (int i = 0; i < N; i++) func(n[i]);
       
        // output
        cout << "#" << tc << " ";
        for (int i = 0; i < H; i++)
            cout << map[i] << "\n";
    }
    return 0;
}