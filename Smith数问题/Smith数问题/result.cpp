#include<iostream>
#include<math.h>
using namespace std;
int add(int n) {
	int sum = 0;
	while (n != 0) {
		sum += n % 10;
		n = n / 10;
	}
	return sum;
}
int Smith(int n) {
	int sum = 0, x = n;
	
	for (int i = 2; i <= x;) {
		if (n%i == 0) {
			n = n / i;
			sum+= add(i);
		}
		else
			i++;
	}
	return sum;
}

int equal(int n)
{
	if (add(n) == Smith(n))
		return 1;
	else
		return 0;
}
int main() 
{
	int n, s = 0;
	int a[20] = {0};
	while (cin >> n) {
		if (n == 0)
			break;
		for (int i = n + 1;; i++)
			if (equal(i))
			{
				a[s] = i;
				s++;
				break;
			}
	}
	for (int i = 0; i<20; i++)
		if (a[i] != 0)
			cout << a[i] << endl;	
	return 0;
}