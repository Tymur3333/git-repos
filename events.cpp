// ConsoleApplication26.cpp: определяет точку входа для консольного приложения.

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <iomanip> // функция setw() - задает отступ 

using namespace std;

const int CNT = 10000000;

const int MAX_ID = 4;

const char *attributes[] = { "Ball", "Dumbbel", "Rope" };
const char *colors[] = { "Blue", "Red", "Green", "Yellow" };

struct SportAttribute
{
	const char *attribute;
	const char *color;
	unsigned int id;
};

int myRand(int low, int high) {
	return rand() % (high - low + 1) + low;
}

//void PrintEvent(const Event* a)
//{
//	cout << "type: " << a->type << " format: " << a->format << " id: " << a->id << endl;
//}

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
		return -1;
	}

	cout << "Total number of sport attributes: " << CNT << endl << endl;

	for (int i = 0; i < CNT; i++) {
		pSA[i].attribute = attributes[rand() % numb_attributes];
		pSA[i].color = colors[rand() % numb_colors];
		pSA[i].id = rand() % MAX_ID;
		//PrintEvent(pEvent + i);	
	}

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

