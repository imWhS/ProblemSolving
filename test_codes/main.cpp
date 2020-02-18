#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

int N;
int arr[103][2];
bool visited[103];

bool cal(int x1, int y1, int x2, int y2)
{
	return ((abs(x1 - x2) + abs(y1 - y2)) <= 1000 ? true : false);
}

void dfs(int n)
{
	visited[n] = true;

	for (int i = 1; i < N + 2; i++)
	{
		if (!visited[i] && cal(arr[n][0], arr[n][1], arr[i][0], arr[i][1])) dfs(i);
	}
}
int main()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		cin >> N;
		memset(visited, false, sizeof(visited));
		for (int i = 0; i < N + 2; i++) { cin >> arr[i][0] >> arr[i][1]; }
		dfs(0);
		cout << (visited[N + 1] ? "happy" : "sad") << endl;
	}
	return 0;
}
