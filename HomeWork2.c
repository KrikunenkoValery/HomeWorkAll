#include <locale.h>
#include <stdio.h>

void main()
{
	setlocale(LC_ALL, "RUS");
	printf("Äàíî:\n%12d\n%12d\n\t____________\nÎòâåò:\n\t%+012.7f", 2, 133, 2. / 133);
	getchar();
}
