#define _CRT_SECURE_NO_WARNINGS
#define SIZE 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>


typedef struct {
    char name[20];
    char soket[20];
    int price;
    int year;
    int yadro;
} CPU;

int writefile(const char* fname, CPU* inf, int count);
CPU* readfile(const char* fname, CPU** inf, int* count);
CPU* update(CPU* inf, const char* name, int count);
CPU* deleteCPU(CPU* inf, const char* name, int* count);
int strcasecmp_custom(const char* s1, const char* s2);
void searchCPU(const char* fname, const char* query);
CPU* bubble_sort_by_name(CPU* cpus, int count);
CPU* bubble_sort_by_price(CPU* cpus, int count);

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

    readfile(fname, &inf, &count);

    while (1) {
        system("cls");
        printf("\n�������� ��������:\n");
        printf("������� ������ (1)\n");
        printf("�������� ������ � ���� ������ (2)\n");
        printf("������� ������ �� ���� ������ (3)\n");
        printf("�������� ������ � ����� (4)\n");
        printf("����������� ������ (5)\n");
        printf("����� ���������� �� ����� ��� ������ (6)\n");
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
            printf("��������� ����������:\n");
            for (int i = 0; i < count; i++) {
                printf(" - %s\n", inf[i].name);
            }
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
            int sort_choice;
            printf("�������� ������ ����������:\n");
            printf("1. �� ����� ����������\n");
            printf("2. �� ����\n");
            printf("������� ����� ��� ������: ");
            scanf("%d", &sort_choice);

            if (sort_choice == 1) {
                bubble_sort_by_name(inf, count);
            }
            else if (sort_choice == 2) {
                bubble_sort_by_price(inf, count);
            }
            else {
                printf("������������ ����.\n");
                break;
            }

            writefile(fname, inf, count);
            printf("������ �������������.\n");
        } break;

        case 6: {
            system("cls");
            printf("��������� ����������:\n");
            for (int i = 0; i < count; i++) {
                printf(" - %s\n", inf[i].name);
            }
            char query[20];
            printf("������� ��� ���������� ��� ����� ��� ������: ");
            scanf("%19s", query);
            searchCPU(fname, query);
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
    fprintf(out, "\t���\t���\t����\t�����\t����\n");
    for (int i = 0; i < count; i++) {
        fprintf(out, "|%20s\t|%4d\t|%5d %7s\t|%2d\n|",
            inf[i].name, inf[i].year, inf[i].price, inf[i].soket, inf[i].yadro);
    }
    fclose(out);
    return 1;
}

CPU* readfile(const char* fname, CPU** inf, int* count) {
    FILE* in;
    CPU cpu;
    *count = 0;

    if ((in = fopen(fname, "rt")) == NULL) {
        printf("������ ��� �������� ����� ��� ������.\n");
        return;
    }
    char buffer[256];
    fgets(buffer, sizeof(buffer), in);
    printf("���������� ����� %s:\n", fname);
    printf("\t��������\t���\t����\t�����\t����\n");
    while (fscanf(in, "|%20s\t|%4d\t|%5d %7s\t|%2d\n|",
        cpu.name, &cpu.year, &cpu.price, cpu.soket, &cpu.yadro) == 5) {
        if (*count >= SIZE) {
            *inf = (CPU*)realloc(*inf, (*count + 1) * sizeof(CPU));
            if (*inf == NULL) {
                printf("������ ��� ���������� ������.\n");
                fclose(in);
            }
        }
        (*inf)[*count] = cpu;
        (*count)++;
        printf("%20s\t%4d\t%5d\t%7s\t%2d\n",
            cpu.name, cpu.year, cpu.price, cpu.soket, cpu.yadro);
    }
    fclose(in);
    return inf;
}


int strcasecmp_custom(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2 || tolower(*s1) == tolower(*s2))) {
        s1++;
        s2++;
    }
    return tolower(*(unsigned char*)s1) - tolower(*(unsigned char*)s2);
}

CPU* update(CPU* inf, const char* name, int count) {
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
    return inf;
}

CPU* deleteCPU(CPU* inf, const char* name, int* count) {
    for (int i = 0; i < *count; i++) {
        if (strcasecmp_custom(inf[i].name, name) == 0) {
            for (int j = i; j < *count - 1; j++) {
                inf[j] = inf[j + 1];
            }
            (*count)--;
        }
    }
    return inf;
}

void searchCPU(const char* fname, const char* query) {
    FILE* file = fopen(fname, "rt");
    if (file == NULL) {
        perror("������ �������� �����");
        return;
    }

    CPU cpu;
    int found = 0;
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);
    while (fscanf(file, "|%20s\t|%4d\t|%5d %7s\t|%2d\n|",
        cpu.name, &cpu.year, &cpu.price, cpu.soket, &cpu.yadro) == 5) {
        if (strcasecmp_custom(cpu.name, query) == 0 || strcasecmp_custom(cpu.soket, query) == 0) {
            printf("������ ���������:\n");
            printf("\t��������\t���\t����\t�����\t����\n");
            printf("|%20s\t|%4d\t|%5d %7s\t|%2d\n|",
                cpu.name, cpu.year, cpu.price, cpu.soket, cpu.yadro);
            found = 1;
        }
    }
    fclose(file);
}

CPU* bubble_sort_by_name(CPU* cpus, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(cpus[j].name, cpus[j + 1].name) > 0) {
                CPU temp = cpus[j];
                cpus[j] = cpus[j + 1];
                cpus[j + 1] = temp;
            }
        }
    }
    return cpus;
}

CPU* bubble_sort_by_price(CPU* cpus, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (cpus[j].price > cpus[j + 1].price) {
                CPU temp = cpus[j];
                cpus[j] = cpus[j + 1];
                cpus[j + 1] = temp;
            }
        }
    }
    return cpus;
}
