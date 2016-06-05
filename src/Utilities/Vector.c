/*
 * Vector.c
 *
 *  Created on: 07 May 2016
 *      Author: KaaN
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Vector.h"

void vector_init(Vector *v) {
	v->data = NULL;
	v->size = 0;
	v->count = 0;
}

int vector_count(Vector *v) {
	return v->count;
}

void vector_add(Vector *v, char e) {
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

void vector_set(Vector *v, int index, char e) {
	if (index >= v->count) {
		return;
	}

	v->data[index] = e;
}

char *vector_get(Vector *v, int index) {
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

void vector_appendArray(Vector* v, unsigned char* buffer, int size){
	int x = 0;
		for (x = 0; x < size; x++) {
			char c = *(&(buffer[x]));
			vector_add(v, c);
		}
}
void printVector(Vector * v){
	xil_printf("Vector : \r\n");
	int i;

	for (i = 0; i < vector_count(v); i++) {
			xil_printf("v[%d]: %c\n",i, *(vector_get(v, i)));
		}
}
