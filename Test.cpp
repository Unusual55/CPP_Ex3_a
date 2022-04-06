/**
 * @file Test.cpp
 * @author Ofri Tavor
 * @brief Test cases for the assignment
 * @date 2022-03
 */
#include <algorithm>
#include "Matrix.hpp"
#include "doctest.h"
#include <string>
#define MAX_LENGTH 100
////////////////////////////////////////////////////Constants zone////////////////////////////////////////
vector<double> invalid1 = {1, 2, 3, 4, 5, 6, 7};
int invalid1_rows = 2;
int invalid1_cols = 3;

int invalid2_rows = 4;
int invalid2_cols = 2;

vector<double> valid1 = {1, 2, 3, 4};
int valid1_rows = 2;
int valid1_cols = 2;

int valid2_rows = 1;
int valid2_cols = 4;

int valid3_rows = 4;
int valid3_cols = 1;

vector<double> empty_vector;

vector<double> zero_vec = {0, 0, 0, 0};
vector<double> one_vec={1, 1, 1, 1};

vector<double> negativector = {-1, -2, -3, -4};

////////////////////////////////////////////////////Constants zone////////////////////////////////////////


TEST_CASE("Invalid matrix building inputs")
{
    SUBCASE("Invalid row number")
    {
        CHECK_THROWS(Matrix(invalid1, -1, invalid1_cols));
        CHECK_THROWS(Matrix(invalid1, 0, invalid1_cols));
        CHECK_THROWS(Matrix(valid1, 1, valid1_cols));
        /**
         * The matrix valid1 will look like: [1 2]
         *                                   [3 4]
         * so the number of rows become invalid since 1*valid1_cols !=4
         */
    }

    SUBCASE("Invalid column number")
    {
        CHECK_THROWS(Matrix(invalid1, invalid1_rows, -1));
        CHECK_THROWS(Matrix(invalid1, invalid1_rows, 0));
        CHECK_THROWS(Matrix(valid1, valid1_rows, 1));
        /**
         * The matrix valid1 will look like: [1 2]
         *                                   [3 4]
         * so the number of columns become invalid since valid1_rows*1 !=4
         */
    }

    SUBCASE("Vector that does not match the rows and columns")
    {
        CHECK_THROWS(Matrix(invalid1, invalid1_rows, invalid1_cols));
        CHECK_THROWS(Matrix(invalid1, invalid2_rows, invalid2_cols));
        CHECK_THROWS(Matrix(invalid1, invalid1_rows, invalid1_cols));
        CHECK_THROWS(Matrix(empty_vector, 0, 0));
        CHECK_THROWS(Matrix(empty_vector, 1, 0));
        CHECK_THROWS(Matrix(empty_vector, 0, 1));
    }
}

TEST_CASE("Valid matrix building inputs")
{
    CHECK_NOTHROW(Matrix(valid1, valid1_rows, valid1_cols));
    CHECK_NOTHROW(Matrix(valid1, valid2_rows, valid2_cols));
    CHECK_NOTHROW(Matrix(valid1, valid3_rows, valid3_cols));
    CHECK_NOTHROW(Matrix(invalid1, 1, 7));
    CHECK_NOTHROW(Matrix(invalid1, 7, 1));
    Matrix mat = Matrix(valid1, valid1_rows, valid1_cols);
}

TEST_CASE("Plus tests")
{
    SUBCASE("Unary plus: Absolute value of each component in the matrix")
    {
        Matrix m1 = Matrix(negativector, 1, 4);
        Matrix m2 = Matrix(valid1, 1, 4);
        Matrix m3 = Matrix(valid1, 4, 1);
        m1 = (+m1);
        CHECK_THROWS(if (m1 == m3));
        CHECK_NOTHROW(if (m1 == m2));
        CHECK((m1 == m2) == true);
    }

    SUBCASE("Binary plus")
    {
        Matrix m1 = Matrix(negativector, 1, 4);
        Matrix m2 = Matrix(valid1, 1, 4);
        Matrix m3 = Matrix(valid1, 4, 1);
        CHECK_NOTHROW(m1 + m2);
        CHECK_NOTHROW(m2 + m1);
        CHECK_THROWS(m1 + m3);
    }

    SUBCASE("Addition +=")
    {
        Matrix m1 = Matrix(negativector, 1, 4);
        Matrix m2 = Matrix(valid1, 1, 4);
        Matrix z = Matrix(zero_vec, 2, 2);
        CHECK_NOTHROW(m1 + m2);
        Matrix m3 = m1 + m2;
        CHECK_THROWS(if(m3 == z));
    }

    SUBCASE("++1"){
        Matrix m1=Matrix(zero_vec, 1, 4);
        Matrix m2=Matrix(one_vec, 1, 4);
        CHECK_NOTHROW(++m1);
    }

    SUBCASE("i++"){
        Matrix m1=Matrix(zero_vec, 1, 4);
        Matrix m2=Matrix(one_vec, 1, 4);
        CHECK_NOTHROW(m1++);
    }
}

TEST_CASE("Minus tests")
{
    SUBCASE("Unary minus: negate each component in the matrix")
    {
        Matrix m1 = Matrix(negativector, 1, 4);
        Matrix m2 = Matrix(valid1, 1, 4);
        Matrix m3 = Matrix(valid1, 4, 1);
        Matrix m4 = Matrix(negativector, 1, 4);
        m1 = (-m1);
        CHECK_THROWS(if (m1 == m3));
        CHECK_NOTHROW(if (m1 == m2));
        CHECK((m1 == m2) == true);
        CHECK((m1==m4)==false);
    }

    SUBCASE("Binary minus")
    {
        Matrix m1 = Matrix(negativector, 1, 4);
        Matrix m2 = Matrix(valid1, 1, 4);
        Matrix m3 = Matrix(valid1, 4, 1);
        Matrix z = Matrix(zero_vec, 1, 4);
        CHECK_NOTHROW(m1 - m2);
        CHECK_NOTHROW(m2 - m1);
        CHECK_THROWS(m1 - m3);
        Matrix m5=m1-(-m2);
        CHECK((m5==z)==true);

    }

    SUBCASE("Substraction -=")
    {
        Matrix m1 = Matrix(negativector, 1, 4);
        Matrix m2 = Matrix(valid1, 1, 4);
        Matrix z = Matrix(zero_vec, 2, 2);
        CHECK_NOTHROW(m1 - m2);
        CHECK_THROWS(m1-=z);
        Matrix m3 = m1 - m2;
        CHECK_THROWS(if(m3 == z));
    }

    SUBCASE("--1"){
        Matrix m1=Matrix(zero_vec, 1, 4);
        Matrix m2=Matrix(one_vec, 1, 4);
        CHECK_NOTHROW(--m1);
    }

    SUBCASE("i--"){
        Matrix m1=Matrix(zero_vec, 1, 4);
        Matrix m2=Matrix(one_vec, 1, 4);
        CHECK_NOTHROW(m1--);
    }
}

TEST_CASE("Multiplication cases"){
    SUBCASE("Multiply by number"){
        Matrix m1= Matrix(valid1, 2, 2);
        CHECK_NOTHROW(3*m1);
        CHECK_NOTHROW(0.3*m1);
        CHECK_NOTHROW(m1*4);
        CHECK_NOTHROW(m1*2);
    }

    SUBCASE("Multiply by matrix"){
        Matrix m1= Matrix(valid1, 2, 2);
        Matrix m2=Matrix(negativector, 2, 2);
        Matrix m3=Matrix(negativector, 1, 4);
        CHECK_THROWS(m3*m2);
        CHECK_THROWS(m1*m3);
        CHECK_NOTHROW(m1*m2);
        CHECK_NOTHROW(m2*m1);
    }
}

TEST_CASE("Equasion symbols cases"){
    Matrix m1= Matrix(valid1, 2, 2);
    Matrix m2=Matrix(negativector, 2, 2);
    Matrix m3=Matrix(negativector, 1, 4);
    CHECK_THROWS(if(m1==m3));
    CHECK_THROWS(if(m1!=m3));
    CHECK_THROWS(if(m1>=m3));
    CHECK_THROWS(if(m1>m3));
    CHECK_THROWS(if(m1<=m3));
    CHECK_THROWS(if(m1<m3));
    CHECK_NOTHROW(if(m1==m2));
    CHECK_NOTHROW(if(m1!=m2));
    CHECK_NOTHROW(if(m1>=m2));
    CHECK_NOTHROW(if(m1>m2));
    CHECK_NOTHROW(if(m1<=m2));
    CHECK_NOTHROW(if(m1<m2));
    CHECK((m1==m2)==false);
    CHECK((m1!=m2)==true);
    CHECK((m1>m2)==false);
    CHECK((m1>=m2)==false);
    CHECK((m2<=m1)==true);
    CHECK((m2<m1)==true);
}