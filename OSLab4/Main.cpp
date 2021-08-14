#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define MATRIX_SIZE 5

struct Row {
	double items[MATRIX_SIZE];
	int resultPosition;
};

VOID searchThread(LPVOID param);
VOID outputThread(LPVOID param);

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Row matrix[MATRIX_SIZE];
	HANDLE hSearchThreads[MATRIX_SIZE];

	for (int i = 0; i < MATRIX_SIZE; i++) {
		hSearchThreads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)searchThread,
			&(matrix[i]), THREAD_PRIORITY_NORMAL, NULL);

		Sleep((rand() % 2000) + 800);
	}

	WaitForMultipleObjects(MATRIX_SIZE, hSearchThreads, TRUE, INFINITE);
	HANDLE hOutput = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)outputThread, 
		&matrix, THREAD_PRIORITY_NORMAL, NULL);

	WaitForSingleObject(hOutput, INFINITE);

	system("pause");
	return 0;
}

VOID searchThread(LPVOID param) {
	srand((unsigned int)time(NULL));

	Row* rowPointer = (Row*) param;

	for (int i = 0; i < MATRIX_SIZE; i++)
		rowPointer->items[i] = (double)(((rand() % 100 >> 2) + 1) * pow((rand() >> ((rand() % 8) + 1) + 1), 2)) / ((rand() * 3) + 1);

	rowPointer->resultPosition = 0;
	for (int i = 1; i < MATRIX_SIZE; i++) {
		if (rowPointer->items[i] > rowPointer->items[rowPointer->resultPosition])
			rowPointer->resultPosition = i;
	}
}

VOID outputThread(LPVOID param) {
	Row* matrix = (Row*) param;

	printf_s("Ã¿“–»÷¿:\n");
	for (int i = 0; i < MATRIX_SIZE; i++) {
		for (int j = 0; j < MATRIX_SIZE; j++)
			printf_s("%lf ", matrix[i].items[j]);

		printf_s("\n");
	}

	printf_s("\n–≈«”À‹“¿“€:\n");
	for (int i = 0; i < MATRIX_SIZE; i++)
		printf_s("Ã‡ÍÒËÏÛÏ %d-ÓÈ ÒÚÓÍË: %lf\n", i + 1, matrix[i].items[matrix[i].resultPosition]);
}