#include <locale.h>
#include <stdio.h>

void main()
{
	setlocale(LC_ALL, "RUS");
	printf("Дано:\n%12d\n%12d\n\t____________\nОтвет:\n\t%+012.7f", 2, 133, 2. / 133);
	getchar();
}