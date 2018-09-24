// ConsoleApplication3.cpp: определяет точку входа для консольного приложения.
// events1.2.cpp: определяет точку входа для консольного приложения.


#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <iomanip> // функция setw() - задает отступ
#include <stdio.h>
#include <string>

using namespace std;

const int CNT = 20;

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

void ClearSportAttributes(int count, SportAttribute* pSA)
{
	for (int i = 0; i < count; i++)
	{
		pSA[i].attribute = (char*)"";
		pSA[i].color = (char*)"";
		pSA[i].id = 0;
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
	return 0;
}

int LoadFromFileSportAttributes(int a, int b, int n, SportAttribute* pSA) // a - начальный элемент, b - конечный элемент, n - максимальный размер загружаемого из файла слова
{
	FILE *fp;
	char name[] = "SportAttributes.txt";
	fp = fopen(name, "r");
	if (fp == NULL) { return -1; }

	int tmp_id = 0;
	int count_load = 0;

	for (int i = 0; i < a; i++)
	{
		fscanf(fp, "%*s%*s%*d%*c"); // %s - считывает строку и сохраняет по указателю на строку, %*s - считывает строку и игнорирует её (из за *)
		// %d - считывает целое число и сохраняет по указателю на переменную int, %*d - считывает целое число и игнорирует её (из за *)
		// %c - считывает символ и сохраняет по указателю на символ, %*c - считывает символ (в данном случае символ "возврата каретки") и игнорирует его (из за *)
		if (feof(fp) != 0) { return count_load; }
	}

	for (int i = a; i <= b; i++)
	{
		char* tmp_s1 = (char*)malloc(n);
		char* tmp_s2 = (char*)malloc(n); 

		fscanf(fp, "%s%s%d", tmp_s1, tmp_s2, &tmp_id);
		fscanf(fp, "%*c"); /* удаление возврата каретки из потока ввода */
		
		if (feof(fp) != 0) 
		{
			free(tmp_s1);
			free(tmp_s2);
			return count_load;
		}

		pSA[i - a].attribute = tmp_s1;
		pSA[i - a].color = tmp_s2;
		pSA[i - a].id = tmp_id;
		++count_load;

		cout << i << " " << pSA[i - a].attribute << " " << pSA[i - a].color << " " << pSA[i - a].id << endl;
	}
	fclose(fp);
	return 0;
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
		cerr << endl << "Error. Memory no allocate!" << endl;
		system("pause");
		return -1;
	}

	cout << "Total number of sport attributes: " << CNT << endl << endl;
	
	ClearSportAttributes(CNT, pSA);
	
	//CreateSportAttributes(CNT, pSA);
	
	/*if (SaveInFileSportAttributes(0, CNT - 1, pSA) == -1)
	{
	cerr << endl << "Error. SaveInFileSportAttributes - File not open" << endl;
	system("pause");
	return -1;
	}*/

	int LoadSuccessful = LoadFromFileSportAttributes(15, CNT, 50, pSA) ;

	if (LoadSuccessful == -1)
	{
		cerr << endl << "Error. LoadFromFileSportAttributes - File not open" << endl;
		system("pause");
		return -1;
	}

	if (LoadSuccessful != 0)
	{
		cerr << endl << "Error. LoadFromFileSportAttributes - End of file" << endl;
		cerr << LoadSuccessful << "records were read" << endl;
		system("pause");
	}

	cout << endl;

	PrintSportAttributes(0, CNT - 1, pSA);

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

