/*
 * Vector.h
 *
 *  Created on: 07 May 2016
 *      Author: KaaN
 */

#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct vector_ {
	char* data;
	int size;
	int count;
} Vector;

void vector_init(Vector*);
int vector_count(Vector*);
void vector_add(Vector *v, char e);
void vector_set(Vector *v, int index, char e);
char *vector_get(Vector*, int);
void vector_delete(Vector*, int);
void vector_free(Vector*);
void vector_appendArray(Vector* v, unsigned char* buffer, int size);
void printVector(Vector * v);

#endif /* VECTOR_H_ */
