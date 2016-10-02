#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#ifndef _Main
#define _Main
#include "matrix.h"
#endif

#include "vector.h"

#include <time.h>
#include <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h> 

#define ROW_MATRIX1 1500
#define ROW_MATRIX2 1500
#define COLUMN_MATRIX1 1500
#define COLUMN_MATRIX2 1500
#define num_thread 16
#define SIZE_VECTOR 10


struct matrixClass result;
int main()

{

	clock_t t;
	int f;
	t = clock();

	pthread_t* thread;
	thread = (pthread_t*)malloc(num_thread*sizeof(pthread_t));

	srand(time(NULL));
	struct vectorClass v1;
	v1.column = SIZE_VECTOR;
	v1.vector = (int*)malloc(sizeof(int) *v1.column);
	vectorClass_init(v1);
	for (int i = 0; i < v1.column; i++)
	{

	vectorClass_allocate(v1, i, rand());
	}
	//printf("Your vector: \n");
	//vectorClass_show(v1);

	struct matrixClass m1;
	m1.column = COLUMN_MATRIX1;
	m1.row = ROW_MATRIX1;
	m1.matrix = (int*)malloc(sizeof(int) * m1.column*m1.row);
	matrixClass_init(m1);
	int val = 0;
	for (int i = 0; i < m1.row; i++)
	{
		for (int j = 0; j < m1.column; j++)
		{
			matrixClass_allocate(m1, i, j, val++);
		}
	}
	//printf("Your matrix: \n");
	//matrixClass_show(m1);

	/*		 struct matrixClass m2;
	m2.column = COLUMN_MATRIX2;
	m2.row = ROW_MATRIX2;
	m2.matrix = malloc(sizeof(int) * m2.column*m2.row);
	matrixClass_init(m2);
	val = 0;
	for (int i = 0; i < m2.row; i++)
	{
		for (int j = 0; j < m2.column; j++)
		{
			matrixClass_allocate(m2, i, j, val++);

		}
	}*/
	//printf("Your matrix: \n");
	//matrixClass_show(m2);

	result.row = ROW_MATRIX1;
	result.column = COLUMN_MATRIX1;
	result.matrix = (int*)malloc(sizeof(int) * result.column*result.row);
	for (int i = 0; i<result.row* result.column; i++)
	{
		result.matrix[i] = 0;
	}
	struct arg_struct_vm arg;
	arg.v1 = v1;
	arg.m2 = m1;

	// this for loop not entered if threadd number is specified as 1
	for (int i = 1; i < num_thread; i++)
	{
		arg.slice = i;
		// creates each thread working on its own slice of i
		if (pthread_create(&thread[i], NULL, mult_vector, (void *)&arg) != 0)
		{
			perror("Can't create thread");
			free(thread);
			exit(-1);
		}
	}
	struct arg_struct_vm arg1;
	arg1.v1 = v1;
	arg1.m2 = m1;
	arg1.slice = 0;
	mult_vector((void *)&arg1);


	for (int i = 1; i < num_thread; i++)
		pthread_join(thread[i], NULL);
	printf("done\n");
	//matrixClass_show(result);
	free(thread);
	t = clock() - t;
	printf("It took me %d clicks (%f seconds).\n", (int)t, (float)t / CLOCKS_PER_SEC);
	return 0;
}
