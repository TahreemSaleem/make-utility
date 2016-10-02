#include "matrix.h"
#include <stdio.h> 
#define ROW_MATRIX1 1500
#define ROW_MATRIX2 1500
#define COLUMN_MATRIX1 1500
#define COLUMN_MATRIX2 1500
#define num_thread 16

struct matrixClass result_m;
void matrixClass_allocate(struct matrixClass m, int row, int column, int value)
{
	//row major ordered
	m.matrix[row + (column * m.column)] = value;
}
void matrixClass_show(struct matrixClass m)
{
	for (int i = 0; i < m.row; i++)
	{
		printf("\t\t|\t");
		for (int j = 0; j < m.column; j++)
		{
			printf("%d\t", m.matrix[i + j*m.row]);
		}
		printf("|\n");
	}
}
void matrixClass_init(struct matrixClass m)
{

	for (int i = 0; i < m.row; i++)
	{
		for (int j = 0; j < m.column; j++)
		{
			m.matrix[i + (j * m.column)] = 0;
		}
	}

}
void * mult_matrix(void *arguments)
{
	struct arg_struct *arg = (arg_struct*)arguments;

	int from = (arg->slice * ROW_MATRIX1) / num_thread; // note that this 'slicing' works fine
	int to = ((arg->slice + 1) * ROW_MATRIX1) / num_thread; // even if SIZE is not divisible by num_thrd
	int i, j, k;

	//printf("computing slice %d (from row %d to %d)\n", arg->slice, from, to - 1);
	for (int i = from; i < to; i++)
	{
		for (int j = 0; j < arg->m2.column; j++)
		{
			for (int k = 0; k < arg->m1.column; k++)
			{
				//c[i][j] = c[i][j] + (a[i][k] * b[k][j]);
				int rposi = i + (j*arg->m1.column);
				int m1posi = i + (k*arg->m1.column);
				int m2posi = k + (j*arg->m1.column);
				result_m.matrix[rposi] += arg->m1.matrix[m2posi] * arg->m2.matrix[m1posi];
			}

		}
	}
	//printf("finished slice %d\n", arg->slice);
	return 0;
}