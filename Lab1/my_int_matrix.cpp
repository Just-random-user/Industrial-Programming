#include "my_int_matrix.h"
#include <iostream>

my_int_matrix::my_int_matrix()
{
	matrix = nullptr;
	columns = 0;
	rows = 0;
}

my_int_matrix::my_int_matrix(const my_int_matrix& object)
{
	this->columns = object.columns;
	this->rows = object.rows;
	this->initialize_matrix();
	for (int i = 0; i < columns; i++)
		for (int j = 0; j < rows; j++)
			matrix[i][j] = object.matrix[i][j];
}

my_int_matrix::my_int_matrix(int** matrix, int columns, int rows)
{
	this->matrix = matrix;
	this->columns = columns;
	this->rows = rows;
}

my_int_matrix::my_int_matrix(int columns, int rows, int fill_with)
{
	this->columns = columns;
	this->rows = rows;
	this->initialize_matrix();
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
			matrix[i][j] = fill_with;
	}
}

my_int_matrix::~my_int_matrix()
{
	for (int i = 0; i < columns; i++)
		delete[] matrix[i];
	delete[] matrix;
}

std::ostream& operator<< (std::ostream& out, const my_int_matrix& object)
{
	for (int i = 0; i < object.columns; i++)
	{
		for (int j = 0; j < object.rows; j++)
			out << object.matrix[i][j] << " ";
		out << std::endl;
	}
	return out;
}