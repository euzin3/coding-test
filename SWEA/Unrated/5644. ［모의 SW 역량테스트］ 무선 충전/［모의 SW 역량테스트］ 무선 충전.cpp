#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

vector<int> map[11][11];
int visited[11][11]; 
int userA[101];
int userB[101];
int M, A;
struct BC {
    int num;
    int y, x;
    int C; // 범위
    int P; // 성능
};
vector<BC> v(9);

struct Coord {
    int y, x;
};

int dirY[] = { 0, -1, 0, 1, 0 }; 
int dirX[] = { 0, 0, 1, 0, -1 };


// BC Range
void bfs(int y, int x, int n) {
    queue<Coord> q;
    memset(visited, 0, sizeof(visited));

    q.push({ y, x });
    visited[y][x] = 1;
    map[y][x].push_back(n);

    while (!q.empty()) {
        Coord now = q.front(); q.pop();

        for (int i = 1; i < 5; i++) {
            int ny = now.y + dirY[i];
            int nx = now.x + dirX[i];

            if (ny < 1 || nx < 1 || ny > 10 || nx > 10) continue;
            if (abs(ny-y) + abs(nx - x) > v[n].C) continue;
            if (visited[ny][nx]) continue;

            visited[ny][nx] = 1;
            map[ny][nx].push_back(n);
            q.push({ ny, nx });

        }
    }
}

// Total Performance 
int move() {
    int ay = 1, ax = 1;      // A 시작 위치
    int by = 10, bx = 10;    // B 시작 위치

    int total = 0;

    for (int t = 0; t <= M; t++) {
        int maxCharge = 0;
        
        // 3가지 중 max 값 선택
        // 1. 둘 다 BC 선택 
        for (int a : map[ay][ax]) {
            for (int b : map[by][bx]) {
                if (a == b)
                    maxCharge = max(maxCharge, v[a].P);
                else
                    maxCharge = max(maxCharge, v[a].P + v[b].P);
            }
        }

        // 2. A만 선택
        for (int a : map[ay][ax])
            maxCharge = max(maxCharge, v[a].P);

        // 3. B만 선택
        for (int b : map[by][bx])
            maxCharge = max(maxCharge, v[b].P);

        total += maxCharge;
        if (t == M) break;

        // next
        ay += dirY[userA[t]];
        ax += dirX[userA[t]];

        by += dirY[userB[t]];
        bx += dirX[userB[t]];
    }
    return total;
}

int main() {

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        cin >> M >> A;
        
        for (int i = 0; i < M; i++) cin >> userA[i];
        for (int i = 0; i < M; i++) cin >> userB[i];
        
        // BC A개 
        for (int i = 1; i <= A; i++) {
            int y, x, C, P; 
            cin >> x >> y >> C >> P;
            v[i] = { i, y, x, C, P };
        }

        // map init
        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++)
                map[i][j].clear();

        // BC range
        for (int i = 1; i <= A; i++) {
            bfs(v[i].y, v[i].x, i);
        }
        
        // Total Performance 
        int ret = move();

        cout << "#" << tc << " " << ret << "\n";
    }
    return 0;
}