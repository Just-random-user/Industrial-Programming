#include <iostream>
#ifndef MY_INT_MATRIX
#define MY_INT_MATRIX

class my_int_matrix
{
public:
	int** matrix;
	int columns;
	int rows;

	my_int_matrix();
	my_int_matrix(const my_int_matrix& object);
	my_int_matrix(int** matrix, int columns, int rows);
	my_int_matrix(int columns, int rows, int fill_with);
	~my_int_matrix();
	void initialize_matrix()
	{
		matrix = new int* [columns];
		for (int i = 0; i < columns; i++)
			matrix[i] = new int[rows];
	}
	void copy(static my_int_matrix& matrix1)
	{
		for (int i = 0; i < matrix1.columns && i < columns; i++)
			for (int j = 0; j < matrix1.rows && j < rows; j++)
				matrix[i][j] = matrix1.matrix[i][j];
	}
	friend std::ostream& operator<< (std::ostream& out, const my_int_matrix& object);
};

#endif