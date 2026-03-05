#include <iostream>
#include <vector>
#include <queue>
using namespace std;


// 위상 정렬 - Kahn algorithm
int main() {
	int N, M;
	cin >> N >> M;

	vector<vector<int>> graph(N + 1);
	vector<int> indegree(N + 1, 0); // 진입 차수

	// 그래프 생성
	for (int i = 0; i < M; i++) {
		int A, B;
		cin >> A >> B;

		graph[A].push_back(B);
		indegree[B]++;
	}

	queue<int> q;
	
	// indegree 0 노드 
	for (int i = 1; i <= N; i++) {
		if (indegree[i] == 0)
			q.push(i);
	}

	// 위상 정렬 
	while (!q.empty()) {

		int now = q.front(); q.pop();
		cout << now << " ";

		for (int next : graph[now]) {
			indegree[next]--;
			if (indegree[next] == 0)
				q.push(next);
		}
	}
	return 0;
}