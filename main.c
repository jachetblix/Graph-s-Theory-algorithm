/*33296046 Artem Egorov*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Interval {
	int start, end;
	int colorID;
	int degree;
} interval;

void greedy_coloring();
void print(interval*, int);
void setDegree(interval*, int);
int getMaxDegree(interval* arr, int k);
int getMinDegree(interval* arr, int k);
int getSumDegrees(interval* arr, int k);
void printByColor(interval* arr, int k);
void sorting_intervals(interval* arr, int k);
void greedy_algorithm(interval* arr, int k);

void main() {
	greedy_coloring();
	system("pause");
}

void greedy_coloring() {
	int k, i;
	interval* arr;
	printf("Please input k\n");
	scanf("%d", &k);
	arr = (interval*)malloc(k * sizeof(interval));

	for (i = 0; i < k; i++) {
		printf("Interval %d: ", i + 1);
		scanf("%d%d", &arr[i].start, &arr[i].end);
		arr[i].degree = 0;
		arr[i].colorID = -1;
	}

	print(arr, k);
	sorting_intervals(arr, k);

	setDegree(arr, k);
	printf("G edges = %d\n", getSumDegrees(arr, k) / 2);
	printf("Maximum degree of G = %d\n", getMaxDegree(arr, k));
	printf("Minumim degree of G = %d\n", getMinDegree(arr, k));

	printf("G's Complement Edges = %d\n", (k * (k - 1)) / 2 - (getSumDegrees(arr, k) / 2));
	printf("Maximum degree of G's Complement = %d\n", k - getMinDegree(arr, k) - 1);
	printf("Minimum degree of G's Complement = %d\n", k - getMaxDegree(arr, k) - 1);

	greedy_algorithm(arr, k);

	printByColor(arr, k);
}

void print(interval* arr, int k) {
	int i;
	printf("The Intervals family is:\n");

	for (i = 0; i < k; i++) {
		printf("[%d,%d]", arr[i].start, arr[i].end);

		if (i < k - 1) {
			printf(",");
		}
	}
	printf("\n");
}

void setDegree(interval* arr, int k) {
	int i, j;

	for (i = 0; i < k; i++) {
		for (j = i + 1; j < k; j++) {

			if (!((arr[i].end < arr[j].start) || (arr[i].start > arr[j].end))) {
				arr[i].degree++;
				arr[j].degree++;
			}
		}
	}
}

int getMaxDegree(interval* arr, int k) {
	int max = 0, i;
	for (i = 0; i < k; i++) {
		if (arr[i].degree > max) {
			max = arr[i].degree;
		}
	}
	return max;
}

int getMinDegree(interval* arr, int k) {
	int min = arr[0].degree, i;
	for (i = 1; i < k; i++) {
		if (arr[i].degree < min) {
			min = arr[i].degree;
		}
	}
	return min;
}

int getSumDegrees(interval* arr, int k) {
	int sum = 0, i;

	for (i = 0; i < k; i++) {
		sum += arr[i].degree;
	}
	return sum;
}

void sorting_intervals(interval* arr, int k) {
	int j, i;

	for (i = 1; i < k; i++)
	{
		for (j = 0; j < k - i; j++)
		{
			if (arr[j].start > arr[j + 1].start)
			{
				interval temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void greedy_algorithm(interval* arr, int k) {
	int i, ch, c, color = 0;
	int* colorsArray;
	bool* isNeighbor;
	arr[0].colorID = 0;
	colorsArray = (int*)malloc(k * sizeof(int));
	for (i = 0; i < k; i++) {
		colorsArray[i] = i;
	}
	isNeighbor = (bool*)malloc(k * sizeof(bool));
	for (i = 1; i < k; i++) {
		arr[i].colorID = -1;
	}
	for (i = 0; i < k; i++) {
		isNeighbor[i] = false;
	}
	for (i = 1; i < k; i++) {
		for (c = 0; c < k; c++) {
			if (c == i)
				continue;
			else if (!((arr[c].end < arr[i].start) || (arr[c].start > arr[i].end))) {
				isNeighbor[c] = true;
			}
		}
		for (ch = 0; ch < i; ch++) {
			if (isNeighbor[ch] == true) {
				for (int j = 0; j < i; j++) {
					if (colorsArray[j] == arr[ch].colorID)
						colorsArray[j] = -1;
				}
			}
		}
		for (ch = 0; ch < k; ch++) {
			if (colorsArray[ch] != -1) {
				color = colorsArray[ch];
				break;
			}
		}
		arr[i].colorID = color;
		for (c = 0; c < k; c++) {
			isNeighbor[c] = false;
		}
		for (int n = 0; n < k; n++) {
			colorsArray[n] = n;
		}
	}
	free(colorsArray);
	free(isNeighbor);
}

void printByColor(interval* arr, int k) {
	int j, i;

	for (i = 1; i < k; i++) {
		for (j = 0; j < k - 1; j++) {
			if (arr[j].colorID > arr[j + 1].colorID) {
				interval temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}


	int max = 0;
	for (int i = 0; i < k; i++) {
		if (arr[i].colorID > max)
			max = arr[i].colorID;
	}
	printf("Optional Coloring: ");

	for (i = 0; i <= max; i++) {
		printf("{");
		for (j = 0; j < k; j++) {
			if (arr[j].colorID == i) {
				printf("[%d,%d]", arr[j].start, arr[j].end);
				if (arr[j].colorID == arr[j + 1].colorID)
					printf(",");
			}
		}
		printf("}");
		printf("= %d", i + 1);
		if (!(i == max)) {
			printf(", ");
		}
	}
	printf("\n");
}