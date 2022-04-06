#include "Matrix.hpp"
#include <string>
// using namespace zich;

Matrix::Matrix(vector<double> &vec_mat, int rows, int cols)
{

    input_check(rows, cols, vec_mat);
    this->rows = rows;
    this->columns = cols;
    for (unsigned int i = 0; i < rows; i++)
    {
        vector<double> row;
        for (unsigned int j = 0; j < columns; j++)
        {
            unsigned int component_index = i * (unsigned int)columns + j;
            row.push_back(vec_mat[component_index]);
        }
        matrix.push_back(row);
    }
}

Matrix::Matrix(Matrix &mat)
{
    this->rows = mat.rows;
    this->columns = mat.columns;
    for (unsigned int i = 0; i < rows; i++)
    {
        vector<double> row;
        for (unsigned int j = 0; j < columns; j++)
        {
            row.push_back(mat.matrix[i][j]);
        }
        this->matrix.push_back(row);
    }
}

Matrix::Matrix()
{
    this->rows = 0;
    this->columns = 0;
}

void Matrix::setEmpty(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
    {
        std::__throw_invalid_argument("row or column argument is invalid");
    }
    this->columns = cols;
    this->rows = rows;
    for (unsigned int i = 0; i < (unsigned int)rows; i++)
    {
        vector<double> row;
        for (unsigned int j = 0; j < columns; j++)
        {
            row.push_back(0);
        }
        this->matrix.push_back(row);
    }
}

Matrix &Matrix::operator-()
{
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            matrix[i][j] = -(matrix[i][j]);
        }
    }
    return *this;
}

Matrix &Matrix::operator+()
{
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            matrix[i][j] = abs(matrix[i][j]);
        }
    }
    return *this;
}

Matrix Matrix::operator+(Matrix &mat)
{
    bool flag = matrixBoundsComparison(mat);
    if (!flag)
    {
        std::__throw_invalid_argument("Cannot use + operator on matrix from different sizes");
    }
    Matrix ret = Matrix();
    ret.setEmpty(rows, columns);
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            ret.matrix[i][j] = mat.matrix[i][j] + this->matrix[i][j];
        }
    }
    return ret;
}

Matrix Matrix::operator-(Matrix &mat)
{
    bool flag = matrixBoundsComparison(mat);
    if (!flag)
    {
        std::__throw_invalid_argument("Cannot use + operator on matrix from different sizes");
    }
    Matrix ret = Matrix();
    ret.setEmpty(rows, columns);
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            ret.matrix[i][j] = this->matrix[i][j] - mat.matrix[i][j];
        }
    }
    return ret;
}

Matrix Matrix::operator+=(Matrix &mat)
{
    bool flag = matrixBoundsComparison(mat);
    if (!flag)
    {
        std::__throw_invalid_argument("Cannot use + operator on matrix from different sizes");
    }
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            this->matrix[i][j] += mat.matrix[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator-=(Matrix &mat){
    bool flag = matrixBoundsComparison(mat);
    if (!flag)
    {
        std::__throw_invalid_argument("Cannot use + operator on matrix from different sizes");
    }
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            this->matrix[i][j] -= mat.matrix[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator*(double scale)
{
    Matrix ret;
    ret.setEmpty(rows, columns);
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            ret.matrix[i][j] += scale * matrix[i][j];
        }
    }
    return ret;
}

Matrix &Matrix::operator*=(int scale)
{
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            this->matrix[i][j] *= scale;
        }
    }
    return *this;
}

Matrix Matrix::operator*(int scale)
{
    Matrix ret;
    ret.setEmpty(rows, columns);
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            ret.matrix[i][j] += scale * matrix[i][j];
        }
    }
    return ret;
}

Matrix &Matrix::operator*=(double scale)
{
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            this->matrix[i][j] *= scale;
        }
    }
    return *this;
}

Matrix operator*(Matrix &mat1, Matrix &mat2)
{
    if (mat1.getColumns() != mat2.getRows())
    {
        std::__throw_invalid_argument("Cannot multiply the matrixes since the coulumns of the first isn't equals the second's row number.");
    }
    Matrix ret = Matrix();
    ret.setEmpty(mat1.getRows(), mat2.getColumns());
    for (unsigned int i = 0; i < mat1.getRows(); i++)
    {
        for (unsigned int j = 0; j < mat2.getColumns(); j++)
        {
            for (unsigned int k = 0; k < mat1.getColumns(); k++)
            {
                ret.matrix[i][j] += mat1.matrix[i][k] * mat2.matrix[k][j];
            }
        }
    }
    return ret;
}

Matrix &Matrix::operator++()
{
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            this->matrix[i][j] += 1;
        }
    }
    return *this;
}

Matrix &Matrix::operator--()
{
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            this->matrix[i][j] -= 1;
        }
    }
    return *this;
}

Matrix Matrix::operator++(int scale)
{
    Matrix next=Matrix(*this);
    next.setEmpty(this->rows, this->columns);
    for (unsigned int i = 0; i < rows; i++)
    {
        {
            for (unsigned int j = 0; j < columns; j++)
            {
                this->matrix[i][j] += scale;
            }
        }
    }
    return next;
}

Matrix Matrix::operator--(int scale)
{
    Matrix next= Matrix(*this);
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            this->matrix[i][j] -= 1;
        }
    }
    return next;
}

bool Matrix::operator==(Matrix &mat)
    {
        if (!OrderCheck(mat.rows, mat.columns))
        {
            std::__throw_invalid_argument("The matrixes are not from the same order");
        }
        for (unsigned int i = 0; i < rows; i++)
        {
            for (unsigned int j = 0; j < columns; j++)
            {
                if (this->matrix[i][j] != mat.matrix[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

bool Matrix::operator!=(Matrix &mat)
    {
        if (!OrderCheck(mat.rows, mat.columns))
        {
            std::__throw_invalid_argument("The matrixes are not from the same order");
        }
        for (unsigned int i = 0; i < rows; i++)
        {
            for (unsigned int j = 0; j < columns; j++)
            {
                if (this->matrix[i][j] == mat.matrix[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

bool Matrix::operator<(Matrix &mat)
    {
        return this->sum() < mat.sum();
    }

bool Matrix::operator<=(Matrix &mat)
    {
        return this->sum() <= mat.sum();
    }

bool Matrix::operator>(Matrix &mat)
    {
        return this->sum() > mat.sum();
    }

bool Matrix::operator>=(Matrix &mat)
    {
        return this->sum() >= mat.sum();
    }

Matrix operator*(int scale, Matrix &mat)
{
    Matrix ret;
    ret.setEmpty(mat.getRows(), mat.getColumns());
    for (unsigned int i = 0; i < mat.getRows(); i++)
    {
        for (unsigned int j = 0; j < mat.getColumns(); j++)
        {
            ret.setComponent(i, j, (scale * mat.getComponent(i, j)));
        }
    }
    return ret;
}

Matrix operator*(double scale, Matrix &mat)
{
    Matrix ret;
    ret.setEmpty(mat.getRows(), mat.getColumns());
    for (unsigned int i = 0; i < mat.getRows(); i++)
    {
        for (unsigned int j = 0; j < mat.getColumns(); j++)
        {
            ret.setComponent(i, j, (scale * mat.getComponent(i, j)));
        }
    }
    return ret;
}

ostream &operator<<(ostream &output, Matrix mat)
{
    string str;
    for (unsigned int i = 0; i < mat.getRows(); i++)
    {
        str += "[   ";
        for (unsigned j = 0; j < mat.getColumns(); j++)
        {
            double number = mat.getComponent(i, j);
            str += to_string(number);
            str += "   ";
        }
        str += "]\n\n";
    }
    output << str;
    return output;
}

istream &operator>>(istream &is, Matrix &mat)
{
    int rows = -1;
    int cols = -1;
    double n = 0;
    // cout << "Enter the number of rows:" << endl;
    // is >> rows;
    // if (rows <= 0)
    // {
    //     std::__throw_invalid_argument("The number of rows have to be positive");
    // }
    // cout << "Enter the number of columns:" << endl;
    // is >> cols;
    // if (cols <= 0)
    // {
    //     std::__throw_invalid_argument("The number of rows have to be positive");
    // }
    // cout << "Enter " << rows * cols << " numeric components" << endl;
    // vector<double> vec_mat;
    // for (int i = 0; i < rows * cols; i++)
    // {
    //     is >> n;
    //     vec_mat.push_back(n);
    // }
    // mat = Matrix(vec_mat, rows, cols);
    // return is;
    string input;
    getline(is, input);
    vector<string> string_rows = Matrix::splitToRows(input);
    rows=(int)string_rows.size();
    string str=string_rows[0];
    vector<double> first_row=Matrix::splitRowToVector(str);
    cols=(int)first_row.size();
    vector<vector<double>> vec_mat;
    vec_mat.push_back(first_row);
    vector<double> vec_row;
    for(int i=1; i<(int)string_rows.size();i++){
        vec_row=Matrix::splitRowToVector(string_rows[(unsigned int)i]);
        if(cols!=(int)vec_row.size()){
            std::__throw_invalid_argument("The number of components in the rows have to be equal");
        }
        vec_mat.push_back(vec_row);
    }
    mat.rows=rows;
    mat.columns=cols;
    mat.matrix=vec_mat;
    return is;
}