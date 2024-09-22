#include <stdio.h>
#include <locale.h>
#define _CRT_SECURE_NO_WARNINGS
int main()
{
	int n;
	int k;
	int l;
	int no;
	int ko;
	int lo;
	printf("Day month and year (now):\n");
	scanf("%d%d%d", &n, &k, &l);
	printf("Day month and year (you):\n");
	scanf("%d%d%d", &no, &ko, &lo);
	printf("Tvoy vozrast %d years %d month %d days", l - lo, k-ko, n - no);
	getchar();
}
