#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define MATRIX_SIZE 4
#define NO_ODD_NUMBERS -1

struct Row {
	int items[MATRIX_SIZE];
	int result;
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
		rowPointer->items[i] = rand() % 100;

	for (int i = 0; i < MATRIX_SIZE; i++) {
		if (rowPointer->items[i] % 2 != 0) {
			rowPointer->result = rowPointer->items[i];
			return;
		}
	}

	rowPointer->result = NO_ODD_NUMBERS;
}

VOID outputThread(LPVOID param) {
	Row* matrix = (Row*) param;

	printf_s("МАТРИЦА:\n");
	for (int i = 0; i < MATRIX_SIZE; i++) {
		printf_s("|\t");
		for (int j = 0; j < MATRIX_SIZE; j++)
			printf_s("%d\t", matrix[i].items[j]);

		printf_s("|\n");
	}

	printf_s("\nРЕЗУЛЬТАТЫ:\n");
	for (int i = 0; i < MATRIX_SIZE; i++) {
		if (matrix[i].result != NO_ODD_NUMBERS)
			printf_s("Первое нечётное число %d-ой строки: %d\n", i + 1, matrix[i].result);
		else
			printf_s("В строке №%d нет нечетных чисел.", i + 1);
	}
}