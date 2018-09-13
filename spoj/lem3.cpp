#include <bits/stdc++.h>
using namespace std;
 
int n, mincost, tmp, sbit;
vector<vector<int>> cp;
vector<int> cpmin;
vector<bool> is_came;
 
void back(int k, int prev) {
	if (k == n) {
		mincost = min(mincost, tmp);
		return;
	}
	for (int i = 0; i < n; ++i) {
		if (!is_came[i]) {
			is_came[i] = true;
			if (prev != -1) {
				tmp += cp[prev][i];
				sbit ^= (1 << prev);
			} 
			if (tmp + (n - k - 1) * cpmin[sbit] < mincost) {
				back(k + 1, i);
			}
			if (prev != -1) {
				tmp -= cp[prev][i];
				sbit ^= (1 << prev);
			}
			is_came[i] = false;
		}
	}
}
 
int main() {
	cin >> n;
	cp.resize(n, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			cin >> cp[i][j];
	}
	cpmin.resize(1 << n, (int)1e5);
	for (int i = (1 << n) - 1; i; --i) {
		vector<bool> b(n);
		int x = i;
		for (int j = 0; j < n; ++j) {
			b[j] = x & 1;
			x >>= 1;
		}
		for (int x = 0; x < n; ++x) if (b[x]) {
			for (int y = 0; y < n; ++y) if (b[y] && y != x) {
				cpmin[i] = min(cpmin[i], cp[x][y]);			
			}
		}
	}
	is_came.resize(n, false);
	mincost = (int) 1e9;
	tmp = 0;
	sbit = (1 << n) - 1;
	back(0, -1);
	cout << mincost;
	return 0;
} 
