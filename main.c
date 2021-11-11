#define _CRTDBG_MAP_ALLOC

#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <inttypes.h>

void array_int_fill(int64_t* array, size_t size);
int64_t* array_int_read(size_t* size);
int64_t* array_int_min(int64_t* array, size_t size);
int64_t** marray_read(size_t* rows, size_t** sizes);
void marray_print(int64_t** marray, size_t* sizes, size_t rows);
int64_t* int64_ptr_min(int64_t* x, int64_t* y);
int64_t* marray_int_min(int64_t** marray, size_t* sizes, size_t rows);
void marray_normalize(int64_t** marray, size_t sizes[], size_t rows, int64_t m);
void marray_free(int64_t** marray, size_t rows);
void perform();

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	perform();
}

void array_int_fill(int64_t* array, size_t size) {
	for (size_t i = 0; i < size; i++) {
		scanf_s("%" SCNd64, array + i);
	}
}

int64_t* array_int_read(size_t* size) {
	scanf_s("%zu", size);
	int64_t* mass = (int64_t*)malloc((*size) * sizeof(int64_t));
	for (size_t i = 0; i < *size; i++) {
		scanf_s("%" SCNd64, mass + i);
	}
	return mass;
}

int64_t* array_int_min(int64_t* array, size_t size) {
	int64_t min = 0;
	int64_t* min_address = NULL;
	if (size != 0) {
		min = *array;
		min_address = array;
		for (size_t i = 1; i < size; i++) {
			if (array[i] < min) {
				min = array[i];
				min_address = array + i;
			}
		}
	}
	return min_address;
}

int64_t* int64_ptr_min(int64_t* x, int64_t* y) {
	int64_t* result = x;
	if ((x == NULL) || (y == NULL)) {
		if (x == NULL) result = y;
		else if (y == NULL) result = x;
	}
	else {
		if ((*x) > (*y)) result = y;
		else result = x;
	}
	if ((x == NULL) && (y == NULL)) result = NULL;
	return result;
}


int64_t* marray_int_min(int64_t** marray, size_t* sizes, size_t rows) {
	int64_t* min = NULL;
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < sizes[i]; j++) {
			min = int64_ptr_min(min, marray[i] + j);
		}
	}
	return min;
}

void marray_normalize(int64_t** marray, size_t sizes[], size_t rows, int64_t m) {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < sizes[i]; j++) {
			marray[i][j] -= m;
		}
	}
}

int64_t** marray_read(size_t* rows, size_t** sizes) {
	scanf_s("%zu", rows);
	int64_t** arr = (int64_t**)malloc((*rows) * sizeof(int64_t*));
	*sizes = (size_t*)malloc((*rows) * sizeof(size_t));

	for (size_t i = 0; i < *rows; i++) {
		scanf_s("%zu", &((*sizes)[i]));
		arr[i] = (int64_t*)malloc(((*sizes)[i]) * sizeof(int64_t));
		for (size_t j = 0; j < (*sizes)[i]; j++) {
			scanf_s("%" PRId64, &arr[i][j]);
		}

	}
	return arr;
}

void marray_print(int64_t** marray, size_t* sizes, size_t rows) {
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < sizes[i]; j++) {
			printf("%" PRId64, marray[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}

void marray_free(int64_t** marray, size_t rows) {
	for (size_t i = 0; i < rows; i++) {
		free(*(marray + i));
	}
	free(marray);
}

void perform() {
	size_t* sizes = NULL;
	size_t rows = 0;
	int64_t* minimum = (int64_t*)malloc(sizeof(int64_t));
	int64_t** arr = marray_read(&rows, &sizes);
	minimum = marray_int_min(arr, sizes, rows);
	marray_normalize(arr, sizes, rows, *minimum);
	marray_print(arr, sizes, rows);
	marray_free(arr, rows);
	free(sizes);
	free(minimum);
}

/*Данные
3
2 124 11
4 12 45 1 15
3 51235 125 222
*/