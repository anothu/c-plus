#include <iostream>
using namespace std;
int main() {
	char a[20] = { 0 }, b[20] = { 0 }; 
	int status[20][20] = { 0 }, num; 
	char c[40] = { 0 }; 
	int m = 0, n = 0;
	cin >> a >> b;
	for (int i = 0; a[i] != '\0'; i++)m++;  
	for (int i = 0; b[i] != '\0'; i++)n++;
	int L[20][20], p, q;
	for (int i = 1; i <= m; i++)
		status[0][i] = 3;
	for (int i = 1; i <= m; i++)
		status[i][0] = 2;
	for (int i = 0; i <= m; i++)
		L[i][0] = i;
	for (int i = 0; i <= n; i++)
		L[0][i] = i;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) {
			if (a[i - 1] == b[j - 1]) {
				L[i][j] = L[i - 1][j - 1] + 1;
				status[i][j] = 1; 
			}
			else {
				p = L[i][j - 1] + 1;
				q = L[i - 1][j] + 1;

				L[i][j] = p > q ? q : p;
				if (p > q)
					status[i][j] = 2; 
				else
					status[i][j] = 3; 
			}
		}
	num = L[m][n] - 1;
	for (int i = m, j = n; i >= 0 && j >= 0;) {
		if (status[i][j] == 1) {
			c[num--] = a[i - 1];
			i--;
			j--;
		}
		else if (status[i][j] == 2) {
			c[num--] = a[i - 1];
			i--;
		}
		else if (status[i][j] == 3) {
			c[num--] = b[j - 1];
			j--;
		}
		else
			break;
	}
	cout << c;
}