#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

char num[7];
int N;
int len;
int answer;
bool visited[11][1000000];

void Change_num(int idx1, int idx2) {
    char temp = num[idx1];
    num[idx1] = num[idx2];
    num[idx2] = temp;
}

void dfs(int depth) {

    int current = atoi(num);

    if (depth == N) {
        answer = max(answer, current);
        return;
    }

    if (visited[depth][current]) return;
    visited[depth][current] = true;

    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            Change_num(i, j);
            dfs(depth + 1);
            Change_num(i, j); 
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {

        cin >> num >> N;
        len = strlen(num);

        memset(visited, false, sizeof(visited));
        answer = 0;
        dfs(0);

        cout << "#" << tc << " " << answer << "\n";
    }
    return 0;
}