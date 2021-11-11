
//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
//#include <crtdbg.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

struct array_int {
	int64_t* data;
	size_t size;
};

struct maybe_int64 {
	int64_t value;
	bool valid;
};

struct maybe_int64 some_int64(int64_t i) {
	return (struct maybe_int64) { i, true };
}

const struct maybe_int64 none_int64 = { 0 };

size_t read_size();
void array_int_fill(int64_t* array, size_t sz);
struct array_int array_int_read();
struct maybe_int64 array_int_get(struct array_int a, size_t i);
bool array_int_set(struct array_int a, size_t i, int64_t value);
void array_int_print(struct array_int array);
struct maybe_int64 array_int_min(struct array_int array);
void array_int_free(struct array_int a);

int main() {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	struct array_int arr = array_int_read();
	printf("%" PRId64"\n", array_int_get(arr, 3).value);
	printf("%" PRId64"\n", array_int_get(arr, 1000).value);
	array_int_set(arr, 2, 45);
	array_int_print(arr);
	printf("\n");
	printf("%" PRId64 "\n", array_int_min(arr).value);
	array_int_free(arr);
}


size_t read_size() {
	size_t sz = 0;
	scanf_s("%zu", &sz);
	return sz;
}

void array_int_fill(int64_t* array, size_t sz) {
	for (size_t i = 0; i < sz; i = i + 1) {
		scanf_s("%" SCNd64, &array[i]);
	}
}

struct array_int array_int_read() {
	const size_t size = read_size();
	if (size > 0) {
		int64_t* array = (int64_t*)malloc(sizeof(int64_t) * size);
		array_int_fill(array, size);
		return (struct array_int) { .data = array, .size = size };
	}
	else return (struct array_int) { 0 };
}

struct maybe_int64 array_int_get(struct array_int a, size_t i) {
	if (a.size <= i)
		return none_int64;
	else
		return some_int64((a.data)[i]);
}

bool array_int_set(struct array_int a, size_t i, int64_t value) {
	if (a.size <= i) {
		return false;
	}
	else {
		(a.data)[i] = value;
		return true;
	}

}

void array_int_print(struct array_int array) {
	for (size_t i = 0; i < array.size; i = i + 1) {
		printf("%" PRId64 " ", array_int_get(array, i).value);
	}
}

struct maybe_int64 array_int_min(struct array_int array) {
	if (array.size == 0) return none_int64;
	struct maybe_int64 minimum = { .value = (array.data)[0], .valid = true };
	for (size_t i = 1; i < array.size; i++) {
		if ((array.data)[i] < minimum.value) minimum.value = (array.data)[i];
	}
	return minimum;
}

void array_int_free(struct array_int a) {
	if (a.size > 0) {
		free(a.data);
		a.size = 0;
	}
}