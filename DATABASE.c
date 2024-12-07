#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define SIZE 2

typedef struct {
    char name[20];
    char soket[20];
    int price;
    int year;
    int yadro;
} CPU;

int writefile(const char* fname, CPU* inf, int count);
void readfile(const char* fname, CPU** inf, int* count);
int update(CPU* inf, const char* name, int count);
int deleteCPU(CPU* inf, const char* name, int* count);
int strcasecmp_custom(const char* s1, const char* s2);

int main() {
    int select;
    int size = SIZE;
    int count = 0;
    CPU* inf = (CPU*)malloc(size * sizeof(CPU));
    char fname[20] = "CPU.txt";
    setlocale(LC_ALL, "RUS");

    if (inf == NULL) {
        printf("������ ��������� ������.\n");
        return 1;
    }

    // ��������� ������ �� ����� ��� ������
    readfile(fname, &inf, &count);

    while (1) {
        system("cls");
        printf("\n�������� ��������:\n");
        printf("������� ������ (1)\n");
        printf("�������� ������ � ���� ������ (2)\n");
        printf("������� ������ �� ���� ������ (3)\n");
        printf("�������� ������ � ����� (4)\n");
        printf("����������� ������ (5)\n");
        printf("��������� ������ (0)\n");
        printf("������� ����� ��� ������� ��������: ");
        scanf("%d", &select);

        switch (select) {
        case 1: {
            system("cls");
            readfile(fname, &inf, &count);
        } break;

        case 2: {
            while (1) {
                system("cls");
                if (count >= size) {
                    char answer;
                    printf("��������� ������ ����������� (%d). ������ ��������� ����������? (y/n): ", size);
                    scanf(" %c", &answer);
                    if (answer == 'y' || answer == 'Y') {
                        size *= 2;
                        CPU* temp = (CPU*)realloc(inf, size * sizeof(CPU));
                        if (temp == NULL) {
                            printf("������ ��� ���������� ������.\n");
                            free(inf);
                            return 1;
                        }
                        inf = temp;
                    }
                    else {
                        printf("����� �� ������ ���������� ������.\n");
                        break;
                    }
                }

                printf("������� ���������� � ���������� %d:\n", count + 1);
                printf("��������� (������ ������� �� '_'): ");
                scanf("%19s", inf[count].name);
                printf("���: ");
                scanf("%d", &inf[count].year);
                printf("����: ");
                scanf("%d", &inf[count].price);
                printf("�����: ");
                scanf("%19s", inf[count].soket);
                printf("����: ");
                scanf("%d", &inf[count].yadro);
                count++;

                if (!writefile(fname, inf, count)) {
                    printf("������ ��� �������� �����.\n");
                }
                else {
                    printf("������ ������� ���������.\n");
                }

                char continueAdding;
                printf("������ �������� ��� ���� ���������? (y/n): ");
                scanf(" %c", &continueAdding);
                if (continueAdding != 'y' && continueAdding != 'Y') {
                    break;
                }
            }
        } break;

        case 3: {
            system("cls");
            char name[20];
            printf("������� ��� ����������, ������� ������ �������: ");
            scanf("%19s", name);
            if (deleteCPU(inf, name, &count)) {
                printf("��������� '%s' ������� ������.\n", name);
                writefile(fname, inf, count);
            }
            else {
                printf("��������� � ������ '%s' �� ������.\n", name);
            }
        } break;

        case 4: {
            system("cls");
            printf("��������� ����������:\n");
            for (int i = 0; i < count; i++) {
                printf(" - %s\n", inf[i].name);
            }
            char name[20];
            printf("������� ��� ���������� ��� ��������� ������: ");
            scanf("%19s", name);
            if (update(inf, name, count)) {
                printf("������ ������� ���������.\n");
            }
            else {
                printf("��������� � ������ '%s' �� ������.\n", name);
            }
        } break;

        case 5: {
            system("cls");
            printf("���������� ���� �� �����������.\n");
        } break;

        case 0: {
            free(inf);
            printf("����� �� ���������.\n");
            return 0;
        } break;

        default:
            printf("������������ �����. ����������, ���������� ��� ���.\n");
            break;
        }
        system("pause");
    }

    free(inf);
    return 0;
}

int writefile(const char* fname, CPU* inf, int count) {
    FILE* out;
    if ((out = fopen(fname, "wt")) == NULL) {
        printf("������ ��� �������� ����� ��� ������.\n");
        return 0;
    }
    for (int i = 0; i < count; i++) {
        fprintf(out, "_����_\n���: %s\n���: %4d\n����: %d\n�����: %s\n����: %d\n",
            inf[i].name, inf[i].year, inf[i].price, inf[i].soket, inf[i].yadro);
    }
    fclose(out);
    return 1;
}

void readfile(const char* fname, CPU** inf, int* count) {
    FILE* in;
    CPU cpu;
    *count = 0;

    if ((in = fopen(fname, "rt")) == NULL) {
        printf("������ ��� �������� ����� ��� ������.\n");
        return;
    }

    printf("���������� ����� %s:\n", fname);
    while (fscanf(in, "_����_\n���: %19s\n���: %d\n����: %d\n�����: %19s\n����: %d\n",
        cpu.name, &cpu.year, &cpu.price, cpu.soket, &cpu.yadro) == 5) {
        if (*count >= SIZE) {
            *inf = (CPU*)realloc(*inf, (*count + 1) * sizeof(CPU));
            if (*inf == NULL) {
                printf("������ ��� ���������� ������.\n");
                fclose(in);
                return;
            }
        }
        (*inf)[*count] = cpu;
        (*count)++;
        printf("_����_\n���: %s\n���: %d\n����: %d\n�����: %s\n����: %d\n",
            cpu.name, cpu.year, cpu.price, cpu.soket, cpu.yadro);
    }
    fclose(in);
}

int strcasecmp_custom(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2 || tolower(*s1) == tolower(*s2))) {
        s1++;
        s2++;
    }
    return tolower(*(unsigned char*)s1) - tolower(*(unsigned char*)s2);
}

int update(CPU* inf, const char* name, int count) {
    for (int i = 0; i < count; i++) {
        if (strcasecmp_custom(inf[i].name, name) == 0) {
            printf("������� ����� ������ ��� ���������� '%s':\n", inf[i].name);
            printf("����� ���: ");
            scanf("%d", &inf[i].year);
            printf("����� ����: ");
            scanf("%d", &inf[i].price);
            printf("����� �����: ");
            scanf("%19s", inf[i].soket);
            printf("����� ���������� ����: ");
            scanf("%d", &inf[i].yadro);
            writefile("CPU.txt", inf, count);
            return 1;
        }
    }
    return 0;
}

int deleteCPU(CPU* inf, const char* name, int* count) {
    for (int i = 0; i < *count; i++) {
        if (strcasecmp_custom(inf[i].name, name) == 0) {
            for (int j = i; j < *count - 1; j++) {
                inf[j] = inf[j + 1];
            }
            (*count)--; 
            return 1; 
        }
    }
    return 0;
}