#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int n = 0;
	int i = 0;
	int a, b, c;
	a = 0;
	b = 1;
	c = 0;
	scanf("%d", &n);

	if (n == 1) {
		printf("%d", a);
		return 0;
	}
	if (n == 2) {
		printf("%d", b);
		return 0;
	}
	else {
		for (i = 2; i < n; i++) {
			c = a + b;
			a = b;
			b = c;
		}
	}

	printf("%d", c);
	return 0;
}
