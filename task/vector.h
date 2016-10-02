#ifndef _Main
#define _Main
#include "matrix.h"
#endif
struct vectorClass
{
	int column;
	int *__restrict vector;
};


struct arg_struct_vm {
	struct vectorClass v1;
	struct matrixClass m2;
	int slice;
};


void * mult_vector(void *);
void vectorClass_allocate(struct vectorClass, int, int);
void vectorClass_show(struct vectorClass);
void vectorClass_init(struct vectorClass);