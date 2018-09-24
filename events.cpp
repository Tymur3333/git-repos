// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
// events1.2.cpp: определяет точку входа для консольного приложения.


#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <iomanip> // функция setw() - задает отступ
#include <stdio.h>
#include <string>

using namespace std;

const int CNT = 10;

const int MAX_ID = 4;

const char *attributes[] = { "Ball", "Dumbbel", "Rope" };
const char *colors[] = { "Blue", "Red", "Green", "Yellow" };

struct SportAttribute
{
	char *attribute;
	char *color;
	unsigned int id;
};

int myRand(int low, int high) {
	return rand() % (high - low + 1) + low;
}

void PrintSportAttributes(int a, int b, SportAttribute* pSA)
{
	for (int i = a; i <= b; ++i)
	{
		cout << i << " " << pSA[i].attribute << " " << pSA[i].color << " " << pSA[i].id << endl;
	}
}

void CreateSportAttributes(int count, SportAttribute* pSA)
{
	int numb_attributes = sizeof(attributes) / sizeof(*attributes);
	int numb_colors = sizeof(colors) / sizeof(*colors);

	for (int i = 0; i < count; i++)
	{
		pSA[i].attribute = (char*)attributes[rand() % numb_attributes];
		pSA[i].color = (char*)colors[rand() % numb_colors];
		pSA[i].id = rand() % MAX_ID;
	}
}

int SaveInFileSportAttributes(int a, int b, SportAttribute* pSA)
{
	FILE *fp;
	char name[] = "SportAttributes.txt";
	fp = fopen(name, "w");
	if (fp == NULL) { return -1; }

	for (int i = a; i <= b; i++)
	{
		fprintf(fp, "%s %s %d\n", pSA[i].attribute, pSA[i].color, pSA[i].id);
	}
	fclose(fp);
}

int LoadFromFileSportAttributes(int a, int b, SportAttribute* pSA)
{
	FILE *fp;
	char name[] = "SportAttributes.txt";
	fp = fopen(name, "r");
	if (fp == NULL) { return -1; }

	int tmp_id = 0;

	//for (int i = 0; i < a && !feof(fp); i++)
	//{
	//	const char* tmp_s1[50], tmp_s2[50];
	//	fscanf(fp, "%s%s%d", tmp_s1, tmp_s2, &tmp_id);
	//	fscanf(fp, "%*c"); /* удаление возврата каретки из потока ввода */
	//}



	for (int i = a; i <= b && !feof(fp); i++)
	{
		char tmp_s1[50];
		char tmp_s2[50];
		fscanf(fp, "%s%s%d", tmp_s1, tmp_s2, &tmp_id);
		fscanf(fp, "%*c"); /* удаление возврата каретки из потока ввода */
		const char * ptmp_s1 = &tmp_s1[0];
		const char * ptmp_s2 = &tmp_s2[0];
		strcpy(pSA[i - a].attribute, ptmp_s1);
		strcpy(pSA[i - a].color, ptmp_s2);
		pSA[i - a].id = tmp_id;

		cout << i << " " << pSA[i - a].attribute << " " << pSA[i - a].color << " " << pSA[i - a].id << endl;
	}
	fclose(fp);
}

int main()
{
	srand(time(NULL));

	SportAttribute* pSA = (SportAttribute*)malloc(sizeof(SportAttribute) * CNT);

	int numb_attributes = sizeof(attributes) / sizeof(*attributes);
	int numb_colors = sizeof(colors) / sizeof(*colors);

	unsigned int* pCount = (unsigned int*)malloc(sizeof(unsigned int)*numb_attributes*numb_colors*MAX_ID);
	memset(pCount, 0, sizeof(unsigned int)*numb_attributes*numb_colors*MAX_ID);

	// always check for error!
	if (pSA == NULL || pCount == NULL)
	{
		cerr << "Error. Memory no allocate!" << endl;
		system("pause");
		return -1;
	}

	cout << "Total number of sport attributes: " << CNT << endl << endl;

	CreateSportAttributes(CNT, pSA);

	//if (SaveInFileSportAttributes(0, CNT - 1, pSA) == -1)
	//{
	//cerr << "Error. SaveInFileSportAttributes - File not open" << endl;
	//system("pause");
	//return -1;
	//}

	if (LoadFromFileSportAttributes(0, CNT - 1, pSA) == -1)
	{
		cerr << "Error. LoadFromFileSportAttributes - File not open" << endl;
		system("pause");
		return -1;
	}

	PrintSportAttributes(0, CNT - 1, pSA);

	system("pause"); return 0;

	int n = 0;
	while (n < CNT)
	{
		bool flag = false;
		for (int i = 0; i < MAX_ID; ++i)
		{
			if (pSA[n].id != i) { continue; }
			for (int j = 0; j < numb_attributes; ++j)
			{
				for (int k = 0; k < numb_colors; ++k)
				{

					if (strcmp(pSA[n].attribute, attributes[j]) == 0 && strcmp(pSA[n].color, colors[k]) == 0)
					{
						++pCount[i*numb_attributes*numb_colors + j * numb_colors + k]; // можно сюда вместо i вписать pSA[n].id и убрать цикл for (int i = 0; i < MAX_ID; ++i), оставлено для наглядности
						flag = true;
						break;
					}

				}
				if (flag) { break; }
			}
			if (flag) { break; }
		}
		++n;
	}

	int flag_id = 0;
	int total_count = 0;
	for (int i = 0; i < numb_attributes*numb_colors*MAX_ID; ++i)
	{
		if (i / (numb_attributes * numb_colors) + 1 != flag_id)
		{
			flag_id = i / (numb_attributes * numb_colors) + 1;
			cout << endl << "id: " << flag_id << endl;
		}
		cout << setw(8) << attributes[(i % (numb_colors * numb_attributes)) / numb_colors] << ",";
		cout << setw(7) << colors[i % numb_colors] << ": ";

		cout << pCount[i] << endl;
		total_count += pCount[i];
	}

	cout << endl << "Check counters: " << total_count << endl << endl;

	free(pSA);
	system("pause");
	return 0;
}

