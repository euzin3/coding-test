#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M, K;
int sumArr[101][101];
int maxIdx[101][101];
struct Crowd {
    int y, x;
    int num;
    int direct;
};
vector<Crowd> crowd;
int dirY[] = { 0, -1, 1, 0, 0 };
int dirX[] = { 0, 0, 0, -1, 1 };

// move one step
void move(int i) {
    Crowd &cur = crowd[i];
    if (cur.num == 0) return;

    int ny = cur.y + dirY[cur.direct];
    int nx = cur.x + dirX[cur.direct];

    cur.y = ny;
    cur.x = nx;

    // drug zone
    if (ny == 0 || ny == N - 1 || nx == 0 || nx == N - 1) {
        cur.num /= 2;
        if (cur.direct % 2 == 1) cur.direct += 1;
        else if (cur.direct % 2 == 0) cur.direct -= 1;
    }
}


int main() {
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {
        // input
        cin >> N >> M >> K;

        crowd.clear();
        crowd.resize(K);

        for (int i = 0; i < K; i++) {
            int y, x, num, direct;
            cin >> y >> x >> num >> direct;
            crowd[i] = { y, x, num, direct };
        }

        // simulation
        for (int t = 0; t < M; t++) {
            // 1. move all
            for (int i = 0; i < K; i++)  move(i);

            // 2. init
            memset(sumArr, 0, sizeof(sumArr));
            memset(maxIdx, -1, sizeof(maxIdx));

            // 3. update positions
            for (int i = 0; i < K; i++) {
                if (crowd[i].num == 0) continue;

                int y = crowd[i].y;
                int x = crowd[i].x;

                sumArr[y][x] += crowd[i].num;

                if (maxIdx[y][x] == -1 ||
                    crowd[maxIdx[y][x]].num < crowd[i].num) {
                    maxIdx[y][x] = i;
                }
            }
            // 4. reset all nums
            for (int i = 0; i < K; i++)
                crowd[i].num = 0;

            // 5. apply merge result
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < N; x++) {
                    if (maxIdx[y][x] != -1) {
                        int idx = maxIdx[y][x];
                        crowd[idx].num = sumArr[y][x];
                    }
                }
            }
        }

        // total num
        int total = 0;
        for (int i = 0; i < K; i++) total += crowd[i].num;

        // output
        cout << "#" << tc << " " << total << "\n";
    }
    return 0;
}