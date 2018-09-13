#include <bits/stdc++.h>
using namespace std;

#define iii pair<int, pair<int, int>> // v, t, c
int main() {
	int n;
	cin >> n;
	vector<int> fuel_station(n);
	for (int i = 0; i < n; ++i) {
		cin >> fuel_station[i];
	}
	int m;
	cin >> m;
	vector<vector<iii>> e(n);
	for (int i = 0; i < m; ++i) {
		int u, v, t, c;
		cin >> u >> v >> t >> c; 
		--u;
		--v;
		e[u].push_back({v, {t, c}});
		e[v].push_back({u, {t, c}});
	}
	vector<int> min_t(n, (int) 1e9);
	auto cmp = [&](pair<int, int> i, pair<int, int> j) {
		return i.first > j.first;
	};
	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
	min_t[n - 1] = 0; 
	q.push({0, n - 1});
	while (!q.empty()) {
		int t = q.top().first;
		int u = q.top().second;
		q.pop();
		for (auto v: e[u]) {
			if (min_t[v.first] > t + v.second.first) {
				min_t[v.first] = t + v.second.first;
				q.push({min_t[v.first], v.first});
			}
		}
	}
	auto good = [&](int inital_c) {
		queue<iii> qu;
		qu.push({0, {0, inital_c}});
		while (!qu.empty()) {
			int u = qu.front().first;
			if (u == n - 1) {
				return true;
			} 
			int t = qu.front().second.first;
			int c = qu.front().second.second;
			qu.pop();
			for (auto v: e[u]) {
				int tmp_t = t + v.second.first + min_t[v.first];
				int tmp_c = c - v.second.second;
				if (tmp_t <= min_t[0] && tmp_c >= 0) {
					if (fuel_station[v.first]) {
						tmp_c =inital_c; 
					}
					qu.push({v.first, {tmp_t - min_t[v.first], tmp_c}});
				}
			}
		}
		return false; 
	};
	int top = 1, bot = (int) 1e9, mid, ans = -1;
	while (top <= bot) {
		mid = (top + bot) >> 1;
		if (good(mid)) {
			ans = mid;
			bot = mid - 1;
		} else {
			top = mid + 1;
		}
	} 
	cout << ans;
	return 0;
}
