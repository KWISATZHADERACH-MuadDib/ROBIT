#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	double num1, num2;
	double result = 0;
	char calc;
	int i = 0;

	printf("Input Aritmetic Operation\n");
	printf("ex)     3.4 * 8.5\n");
	printf("        2.9 - 5.4\n");
	printf("        3.9 * 8.0\n");
	printf("        3.9 ^ 8\n\n");
	printf("input : ");
	scanf("%lf %c %lf", &num1, &calc, &num2);

	if (calc == '+') {
		result = num1 + num2;
		printf("%.2lf + %.2lf = %.2lf\n", num1, num2, result);
	}

	if (calc == '-') {
		result = num1 - num2;
		printf("%.2lf - %.2lf = %.2lf\n", num1, num2, result);
	}

	if (calc == '*') {
		result = num1 * num2;
		printf("%.2lf * %.2lf = %.2lf\n", num1, num2, result);
	}

	if (calc == '/') {
		result = num1 / num2;
		printf("%.2lf / %.2lf = %.2lf\n", num1, num2, result);
	}
	if (calc == '^') {
		if (num2 == 0) {
			result = 1;
			printf("%.2lf ^ %.2lf = %.2lf\n", num1, num2, result);
		}
		else {
			result = 1;
			for (i = 0; i < num2; i++) {
				result *= num1;
			}
			printf("%.2lf ^ %.2lf = %.2lf\n", num1, num2, result);
		}
	}


	return 0;
}