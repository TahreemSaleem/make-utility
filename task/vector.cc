#include "vector.h"

#include <stdio.h> 
#include <stdlib.h>
#define SIZE_VECTOR 10



void vectorClass_allocate(struct vectorClass v, int position, int value)
{
	v.vector[position] = value;
}
void vectorClass_show(struct vectorClass v)
{
	for (int i = 0; i < v.column; i++)
		printf("\t\t|\t%d\t|\n", v.vector[i]);
}
void vectorClass_init(struct vectorClass v)
{
	for (int position = 0; position < v.column; position++)
	{
		v.vector[position] = 0;
	}

}

void * mult_vector(void * arguments)
{
	struct arg_struct_vm *arg = (arg_struct_vm*)arguments;
	struct vectorClass result_v;
	result_v.column = (arg->m2.row);
	result_v.vector = (int*)malloc(sizeof(int) *result_v.column);
	for (int i = 0; i<arg->v1.column; i++)
	{
		result_v.vector[i] = 0;
	}
	for (int i = 0; i < (arg->m2.row); i++)
	{
		for (int j = 0; j < arg->v1.column; j++)
		{
			result_v.vector[i] += (arg->m2.matrix[i + (j*arg->m2.column)] * arg->v1.vector[j]);
		}
	}

}