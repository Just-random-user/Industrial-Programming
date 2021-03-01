#include <iostream>
#include <cstdlib>
#include <ctime>
#include "my_int_matrix.h"
using namespace std;

//function to initialise and fill matrix according insert type
int initialize_and_fill(my_int_matrix* matrix, int insert_type);

//function to choose inserting type via console
int choose_inserting_type();

my_int_matrix** stage1_matrix_splitting(my_int_matrix** target, my_int_matrix matrix1, my_int_matrix matrix2, int size);
my_int_matrix** stage2_intermidate_matrix_creation(my_int_matrix** target, my_int_matrix** splited_matrix, int size);
my_int_matrix** stage3_support_matrix_creation(my_int_matrix** target, my_int_matrix** interm_matrix, int size);
my_int_matrix   stage4_compile_result_matrix(my_int_matrix** suppmtr, int size);

//function to delete columns and rows with zeros from the edge of the matrix
my_int_matrix   matrix_aligning(my_int_matrix matrix, int size);

void main()
{
	srand(time(NULL));
	system("chcp 1251");
	cout << "Вас приветствует программа" << endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";

	my_int_matrix matrix1 = my_int_matrix();
	my_int_matrix matrix2 = my_int_matrix();

	int inserting_type = choose_inserting_type();

	initialize_and_fill(&matrix1, inserting_type);
	initialize_and_fill(&matrix2, inserting_type);

	//finding digit whitch is close to max(m1.col, m1.row, m2.col, m2.row) from right and is power of two
	int size_to_pow_2 = 2;
	while (size_to_pow_2 <= matrix1.columns || size_to_pow_2 <= matrix2.columns || size_to_pow_2 <= matrix1.rows || size_to_pow_2 <= matrix2.rows)
		size_to_pow_2 *= 2;

	my_int_matrix matr1_copy = my_int_matrix(size_to_pow_2, size_to_pow_2, 0);
	my_int_matrix matr2_copy = my_int_matrix(size_to_pow_2, size_to_pow_2, 0);

	matr1_copy.copy(matrix1);
	matr2_copy.copy(matrix2);

	cout << "Приведённые матрицы\n";
	cout << "\nМатрица 1\n\n" << matr1_copy;
	cout << "\nМатрица 2\n\n" << matr2_copy;

	//memory allocation
	my_int_matrix** submatr = new my_int_matrix * [8];
	my_int_matrix** interm_matrix = new my_int_matrix * [7];
	my_int_matrix** suppmtr = new my_int_matrix * [4];
	for (int i = 0; i < 8; i++)
	{
		submatr[i] = new my_int_matrix(size_to_pow_2 / 2, size_to_pow_2 / 2, 0);
		if (i < 7)
			interm_matrix[i] = new my_int_matrix(size_to_pow_2 / 2, size_to_pow_2 / 2, 0);
		if (i < 4)
			suppmtr[i] = new my_int_matrix(size_to_pow_2 / 2, size_to_pow_2 / 2, 0);
	}

	//main calculations
	stage1_matrix_splitting(submatr, matr1_copy, matr2_copy, size_to_pow_2);
	stage2_intermidate_matrix_creation(interm_matrix, submatr, size_to_pow_2);
	stage3_support_matrix_creation(suppmtr, interm_matrix, size_to_pow_2);

	my_int_matrix result_matrix_unaligned = stage4_compile_result_matrix(suppmtr, size_to_pow_2);
	my_int_matrix result_matrix = matrix_aligning(result_matrix_unaligned, size_to_pow_2);

	cout << "\nРезультирующая матрица\n\n" << result_matrix;
	system("pause");

	for (int i = 0; i < 8; i++)
	{
		if (i < 4)
			delete suppmtr[i];

		if (i < 7)
			delete interm_matrix[i];

		delete submatr[i];
	}
	delete[] suppmtr, interm_matrix, submatr;
}

int choose_inserting_type()
{
	int inserting_type = 1;
	do
	{
		cout << "Выберите способ заполнения матриц" << endl
			<< "1 - Вручную" << endl
			<< "2 - Случайным образом" << endl;
		cin >> inserting_type;
	} while (inserting_type != 1 && inserting_type != 2);
	return inserting_type;
}

int initialize_and_fill(my_int_matrix* matrix, int inserting_type)
{
	do
	{
		cout << "Введите размеры матрицы\n";
		cin >> matrix->columns >> matrix->rows;
	} while (matrix->columns <= 0 || matrix->rows <= 0);

	matrix->initialize_matrix();

	switch (inserting_type)
	{
	case 1:
		cout << endl << "Введите матрицу" << endl;
		for (int i = 0; i < matrix->columns; i++)
			for (int j = 0; j < matrix->rows; j++)
				cin >> matrix->matrix[i][j];
		break;

	case 2:
		for (int i = 0; i < matrix->columns; i++)
			for (int j = 0; j < matrix->rows; j++)
				matrix->matrix[i][j] = rand() % 10;
		break;
	}
	cout << endl << "Проверка" << endl << *matrix;
	return 0;
}

my_int_matrix** stage1_matrix_splitting(my_int_matrix** submatr, my_int_matrix matrix1, my_int_matrix matrix2, int size)
{
	for (int i = 0; i < size / 2; i++)
	{
		for (int j = 0; j < size / 2; j++)
		{
			submatr[0]->matrix[i][j] = matrix1.matrix[i][j];
			submatr[4]->matrix[i][j] = matrix2.matrix[i][j];
			submatr[1]->matrix[i][j] = matrix1.matrix[i][j + size / 2];
			submatr[5]->matrix[i][j] = matrix2.matrix[i][j + size / 2];
			submatr[2]->matrix[i][j] = matrix1.matrix[i + size / 2][j];
			submatr[6]->matrix[i][j] = matrix2.matrix[i + size / 2][j];
			submatr[3]->matrix[i][j] = matrix1.matrix[i + size / 2][j + size / 2];
			submatr[7]->matrix[i][j] = matrix2.matrix[i + size / 2][j + size / 2];
		}
	}
	return submatr;
}

my_int_matrix** stage2_intermidate_matrix_creation(my_int_matrix** interm_matrix, my_int_matrix** splitted_matrix, int size)
{
	my_int_matrix** matr = splitted_matrix; //simple 'renaming'

	for (int i = 0; i < size / 2; i++)
	{
		for (int j = 0; j < size / 2; j++)
		{
			for (int z = 0; z < size / 2; z++)
			{
				interm_matrix[0]->matrix[i][j] += (matr[0]->matrix[i][z] + matr[3]->matrix[i][z])
					* (matr[4]->matrix[z][j] + matr[7]->matrix[z][j]);

				interm_matrix[1]->matrix[i][j] += matr[4]->matrix[z][j]
					* (matr[2]->matrix[i][z] + matr[3]->matrix[i][z]);

				interm_matrix[2]->matrix[i][j] += matr[0]->matrix[i][z]
					* (matr[5]->matrix[z][j] - matr[7]->matrix[z][j]);

				interm_matrix[3]->matrix[i][j] += matr[3]->matrix[i][z]
					* (matr[6]->matrix[z][j] - matr[4]->matrix[z][j]);

				interm_matrix[4]->matrix[i][j] += matr[7]->matrix[z][j]
					* (matr[0]->matrix[i][z] + matr[1]->matrix[i][z]);

				interm_matrix[5]->matrix[i][j] += (matr[2]->matrix[i][z] - matr[0]->matrix[i][z])
					* (matr[4]->matrix[z][j] + matr[5]->matrix[z][j]);

				interm_matrix[6]->matrix[i][j] += (matr[1]->matrix[i][z] - matr[3]->matrix[i][z])
					* (matr[6]->matrix[z][j] + matr[7]->matrix[z][j]);
			}
		}
	}
	return interm_matrix;
}

my_int_matrix** stage3_support_matrix_creation(my_int_matrix** suppmtr, my_int_matrix** interm_matrix, int size)
{
	for (int i = 0; i < size / 2; i++)
	{
		for (int j = 0; j < size / 2; j++)
		{
			suppmtr[0]->matrix[i][j] = interm_matrix[0]->matrix[i][j] + interm_matrix[3]->matrix[i][j]
				- interm_matrix[4]->matrix[i][j] + interm_matrix[6]->matrix[i][j];

			suppmtr[1]->matrix[i][j] = interm_matrix[2]->matrix[i][j] + interm_matrix[4]->matrix[i][j];

			suppmtr[2]->matrix[i][j] = interm_matrix[1]->matrix[i][j] + interm_matrix[3]->matrix[i][j];

			suppmtr[3]->matrix[i][j] = interm_matrix[0]->matrix[i][j] - interm_matrix[1]->matrix[i][j]
				+ interm_matrix[2]->matrix[i][j] + interm_matrix[5]->matrix[i][j];
		}
	}
	return suppmtr;
}

my_int_matrix stage4_compile_result_matrix(my_int_matrix** suppmtr, int size)
{
	my_int_matrix result_matrix_unaligned = my_int_matrix(size, size, 0);
	for (int i = 0; i < size / 2; i++)
	{
		for (int j = 0; j < size / 2; j++)
		{
			result_matrix_unaligned.matrix[i][j] = suppmtr[0]->matrix[i][j];
			result_matrix_unaligned.matrix[i][j + size / 2] = suppmtr[1]->matrix[i][j];
			result_matrix_unaligned.matrix[i + size / 2][j] = suppmtr[2]->matrix[i][j];
			result_matrix_unaligned.matrix[i + size / 2][j + size / 2] = suppmtr[3]->matrix[i][j];
		}
	}
	return result_matrix_unaligned;
}

my_int_matrix matrix_aligning(my_int_matrix matrix_unaligned, int size)
{
	int res_matr_col = 100, res_matr_row = 100;
	bool has_elements_in_the_line = false;

	for (int i = 0; i < size; i++)
	{
		has_elements_in_the_line = false;
		for (int j = 0; j < size; j++)
		{
			if (matrix_unaligned.matrix[i][j] != 0)
			{
				has_elements_in_the_line = true;
				res_matr_col = 100;
				break;
			}
		}
		if (!has_elements_in_the_line && i < res_matr_col)
		{
			res_matr_col = i;
		}
	}

	for (int i = 0; i < size; i++)
	{
		has_elements_in_the_line = false;
		for (int j = 0; j < size; j++)
		{
			if (matrix_unaligned.matrix[j][i] != 0)
			{
				has_elements_in_the_line = true;
				res_matr_row = 100;
				break;
			}
		}
		if (!has_elements_in_the_line && i < res_matr_row)
		{
			res_matr_row = i;
		}
	}
	my_int_matrix result_matrix = my_int_matrix(res_matr_col, res_matr_row, 0);
	for (int i = 0; i < res_matr_col; i++)
		for (int j = 0; j < res_matr_row; j++)
			result_matrix.matrix[i][j] = matrix_unaligned.matrix[i][j];

	return result_matrix;
}
