/*
 * Vector.c
 *
 *  Created on: 07 May 2016
 *      Author: KaaN
 */

#include "Vector.h"

void vector_init(Vector *v) {
	v->size = 10;
	v->data = malloc(sizeof(void*) * v->size);
	memset(v->data, '\0', sizeof(void*) * v->size);
	v->count = 0;
}

int vector_count(Vector *v) {
	return v->count;
}

void vector_push(Vector *v, u8 e) {
	if (v->size == 0) {
		v->size = 10;
		v->data = malloc(sizeof(void*) * v->size);
		memset(v->data, '\0', sizeof(void*) * v->size);
	}

	if (v->size == v->count) {
		v->size *= 2;
		v->data = realloc(v->data, sizeof(void*) * v->size);
	}

	v->data[v->count] = e;
	v->count++;
}

void vector_set(Vector *v, int index, u8 e) {
	if (index >= v->count) {
		return;
	}

	v->data[index] = e;
}

u8* vector_getElement(Vector *v, int index) {
	if (index >= v->count) {
		return NULL;
	}

	return &(v->data[index]);
}

void vector_delete(Vector *v, int index) {
	if (index >= v->count) {
		return;
	}
	int i, j;
	for (i = index + 1, j = index; i < v->count; i++) {
		v->data[j] = v->data[i];
		j++;
	}
	v->count--;
}

void vector_free(Vector *v) {
	free(v->data);
}
void vector_destruct(Vector *v) {
	free(v);
}
void vector_appendArray(Vector* v, u8* buffer, int size) {
	int x = 0;
	for (x = 0; x < size; x++) {
		u8 c = *(&(buffer[x]));
		vector_push(v, c);
	}
}
void vector_append(Vector* dest, Vector* src) {
	int x = 0;
	for (x = 0; x < src->count; x++) {
		u8 c = src->data[x];
		vector_push(dest, c);
	}
}

void printVector(Vector * v) {
	//xil_printf("Vector : \r\n");
	int i;

	for (i = 0; i < vector_count(v); i++) {
		//xil_printf("v[%d]: %c\n", i, *(vector_getElement(v, i)));
	}
}
void printVectorWithName(Vector * v, char* vName) {
	xil_printf("%s\r\n",vName);
	int i;

	for (i = 0; i < vector_count(v); i++) {
		xil_printf("v[%d]: %d\n", i, *(vector_getElement(v, i)));
	}
}
u8 vector_equals(Vector * v1, Vector * v2) {
	u8 result = TRUE;
	if (v1->count != v2->count) {
		result = FALSE;
	} else {
		int i;
		for (i = 0; i < v1->count; i++) {
			if (*vector_getElement(v1, i) != *vector_getElement(v2, i)) {
				result = FALSE;
				break;
			}
		}
	}
	return result;
}

Vector* vector_split(Vector * v, int index) {
	Vector* childVector = malloc(sizeof(Vector));
	vector_init(childVector);
	int i;
	for (i = v->count - index; i < v->count; i++) {
		vector_push(childVector, *vector_getElement(v, i));
	}
	return childVector;
}
