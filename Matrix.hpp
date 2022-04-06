#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <string.h>
#define null NULL
using namespace std;

namespace zich
{
};
// namespace zich
// {
class Matrix
{
    int rows;
    int columns;
    vector<vector<double>> matrix;

public:
    Matrix(vector<double> &vec_mat, int rows, int cols);

    Matrix(Matrix &mat);

    Matrix();

    void setEmpty(int rows, int cols);

    static void input_check(int rows, int cols, vector<double> &vec_mat)
    {
        if (rows <= 0)
        {
            std::__throw_invalid_argument("The number of rows have to be a positive integer");
        }
        if (cols <= 0)
        {
            cout << cols;
            std::__throw_invalid_argument("The number of columns have to be a positive integer");
        }
        unsigned int components = (unsigned int)(rows * cols);
        if (components != (int)vec_mat.size())
        {
            std::__throw_invalid_argument("Cannot create a matrix since the number of components in the input is not equal to rows X columns");
        }
    }

    bool matrixBoundsComparison(Matrix &mat) const
    {
        if (this->rows != mat.getRows())
        {
            return false;
        }
        if (this->columns != mat.getColumns())
        {
            return false;
        }
        return true;
    }

    bool OrderCheck(int rows, int cols)
    {
        return (this->rows == rows) && (this->columns == cols);
    }

    int getRows()
    {
        return this->rows;
    }

    int getColumns()
    {
        return this->columns;
    }

    double getComponent(unsigned int row, unsigned int col)
    {
        if (row < 0 || row > this->rows)
        {
            std::__throw_invalid_argument("The row doesn't exist");
        }
        if (col < 0 || col > this->columns)
        {
            std::__throw_invalid_argument("The row doesn't exist");
        }
        return matrix.at((unsigned int)row).at((unsigned int)col);
    }

    void setComponent(unsigned int row, unsigned int col, double component)
    {
        if (row < 0 || row > this->rows)
        {
            std::__throw_invalid_argument("The row doesn't exist");
        }
        if (col < 0 || col > this->columns)
        {
            std::__throw_invalid_argument("The row doesn't exist");
        }
        matrix.at((unsigned int)row)[(unsigned int)col] = component;
    }

    static vector<string> splitToRows(string &input)
    {
        unsigned int start = 0;
        unsigned int end = input.length();
        vector<string> vec;
        string token;
        while (input.find(", ", start) != string::npos)
        {
            end = input.find(", ", start);
            token = input.substr(start, end-start);
            vec.push_back(token);
            // input=input.substr(end);
            start = end+2;
        }
        token=input.substr(start);
        vec.push_back(token);
        return vec;
    }

    static vector<double> splitRowToVector(string &input)
    {
        vector<double> row;
        unsigned int start = 0;
        unsigned int end = 0;
        char delim = ' ';
        double num;
        while (input.find(delim, start) != string::npos)
        {
            end = input.find(delim, start);
            num = std::stod(input.substr(start, end-start));
            row.push_back(num);
            start=end+1;
        }
        num = std::stod(input.substr(start));
        row.push_back(num);
        return row;
    }

    Matrix &operator-();

    /**
     * @brief Unary plus operator.
     * Set all of the values to their absolute(unsigned) values.
     */

    Matrix &operator+();

    /**
     * @brief Addition operator
     * This function add the values of the input and this matrix and return a copy of the result
     * @param mat The inout matrix
     * @return Matrix& A reference of the result matrix
     */

    Matrix operator+(Matrix &mat);

    Matrix operator-(Matrix &mat);

    Matrix operator-=(Matrix &mat);

    /**
     * @brief += operator
     * This operator takes another matrix and add its values to this matrix
     * @param mat The input matrix
     */

    Matrix operator+=(Matrix &mat);

    Matrix &operator++();

    Matrix &operator--();

    Matrix operator++(int scale);

    Matrix operator--(int scale);

    /**
     * @brief Multiplication Operator
     * This operator take a double scale and multiply the components of the matrix by it and return a copy of the matrix
     * @param scale The scale
     * @return Matrix& a copy of the result
     */

    Matrix operator*(double scale);

    Matrix &operator*=(int scale);

    Matrix &operator*=(double scale);

    /**
     * @brief Multiplication Operator
     * This operator take a double scale and multiply the components of the matrix by it and return a copy of the matrix
     * @param scale The scale
     * @return Matrix& a copy of the result
     */

    Matrix operator*(int scale);

    friend Matrix operator*(int scale, Matrix &mat);

    friend Matrix operator*(double scale, Matrix &mat);

    friend Matrix operator*(Matrix &mat1, Matrix &mat2);

    double sum()
    {
        double sum = 0;
        for (unsigned int i = 0; i < rows; i++)
        {
            for (unsigned int j = 0; j < columns; j++)
            {
                sum += this->matrix[i][j];
            }
        }
        return sum;
    }

    double sum() const
    {
        double sum = 0;
        for (unsigned int i = 0; i < rows; i++)
        {
            for (unsigned int j = 0; j < columns; j++)
            {
                sum += this->matrix[i][j];
            }
        }
        return sum;
    }

    bool operator==(Matrix &mat);

    bool operator!=(Matrix &mat);

    bool operator<(Matrix &mat);

    bool operator<=(Matrix &mat);

    bool operator>(Matrix &mat);

    bool operator>=(Matrix &mat);

    friend ostream &operator<<(ostream &output, Matrix mat);

    friend istream &operator>>(istream &is, Matrix &mat);

    bool unsignedHandler()
    {
        return rows > 0 && columns > 0;
    }
};
// };