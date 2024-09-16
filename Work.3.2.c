#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#define D 2.54
#define K 2.32166
#define C 2.7076
// Çàäàíèå 2
int main()
{
	setlocale(LC_ALL, "RUS");
	int dym;
	printf("How many?");
	scanf("%d", &dym);
	float result = D * dym;
	printf("%.1f cm\n", result);
	float resultS = K * dym;
	printf("%.1f cm\n", resultS);
	float resultSt = C * dym;
	printf("%.1f cm\n", resultSt);
	getchar();
}
