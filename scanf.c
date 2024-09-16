#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
// Задание 1
int main()
{
	setlocale(LC_ALL, "RUS");
	int n;
	int k;
	float del;
	printf("Type:");
	scanf("%d%d", &n, &k);
	del = k % n;
	printf("sum = %d, raznost = %d, umnozhit = %d, del = %d, ostatok = %f", \
		k + n, k - n, k * n, k / n, del);
	getchar();
}