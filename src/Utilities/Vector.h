/*
 * Vector.h
 *
 *  Created on: 07 May 2016
 *      Author: KaaN
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include "xbasic_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct vector_ {
	u8* data;
	int size;
	int count;
} Vector;

void vector_init(Vector*);
int vector_count(Vector*);
void vector_push(Vector *v, u8 e);
void vector_set(Vector *v, int index, u8 e);
u8* vector_getElement(Vector*, int);
void vector_delete(Vector*, int);
void vector_free(Vector*);
void vector_appendArray(Vector* v, u8* buffer, int size);
Vector* vector_split(Vector * v, int index);
u8 vector_equals(Vector * v1, Vector * v2);
void printVector(Vector * v);
void printVectorWithName(Vector * v, char* vName);
void vector_destruct(Vector *v);
#endif /* VECTOR_H_ */
