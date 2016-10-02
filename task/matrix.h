struct matrixClass
{
	int column;
	int row;
	int *__restrict matrix;

};
struct arg_struct {
	struct matrixClass m1;
	struct matrixClass m2;
	int slice;
};

void matrixClass_allocate(struct matrixClass, int, int, int);
void matrixClass_show(struct matrixClass);
void matrixClass_init(struct matrixClass);
void *mult_matrix(void *);