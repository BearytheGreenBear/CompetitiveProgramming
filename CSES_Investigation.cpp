// CSES Problem Set
// Investigation
// https://cses.fi/problemset/task/1202
 
#include <bits/stdc++.h>
using namespace std;
 
#define f first
#define s second

const long long MOD = 1e9+7;

int N, M;
long long minCost[100001];
long long toNode[100001];
int maxDepth[100001];
int minDepth[100001];
vector<pair<long long, int>> adjList[100001];
 
void dijsktras() {
	toNode[1] = 1;
	for (int i = 2; i <= N; i++) {
		minCost[i] = LLONG_MAX;
		minDepth[i] = INT_MAX;
	}
	priority_queue<pair<long long, pair<int, int>>> q;
	vector<bool> seen(N+1);
	q.push({0, {1, -1}});
	while (!q.empty()) {
		pair<long long, pair<int, int>> node = q.top();
		q.pop();
		if (seen[node.s.f]) {
			if (-node.f == minCost[node.s.f]) {
				toNode[node.s.f] = (toNode[node.s.f]+toNode[node.s.s]) % MOD;
				minDepth[node.s.f] = min(minDepth[node.s.f], minDepth[node.s.s]+1);
				maxDepth[node.s.f] = max(maxDepth[node.s.f], maxDepth[node.s.s]+1);
			}
			continue;
		}
		seen[node.s.f] = true;
		if (node.s.s != -1) {
			toNode[node.s.f] = (toNode[node.s.f]+toNode[node.s.s]) % MOD;
			minDepth[node.s.f] = min(minDepth[node.s.f], minDepth[node.s.s]+1);
			maxDepth[node.s.f] = max(maxDepth[node.s.f], maxDepth[node.s.s]+1);
		}
		for (auto edge: adjList[node.s.f]) {
			long long cost = -node.f + edge.f;
			if (cost < minCost[edge.s]) {
				minCost[edge.s] = cost;
			}
			q.push({-cost, {edge.s, node.s.f}});
		}
	}
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> N >> M;
	for (int i = 1; i <= M; i++) {
		int u, v;
		long long c;
		cin >> u >> v >> c;
		adjList[u].push_back({c, v});
	}
	dijsktras();
	cout << minCost[N] << " " << (toNode[N] % MOD) << " " << minDepth[N] << " " << maxDepth[N] << "\n";
}