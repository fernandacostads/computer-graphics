#ifndef COMPUTACAOGRAFICA_MATRIX_HPP
#define COMPUTACAOGRAFICA_MATRIX_HPP

#include <vector>
#include "Vector.hpp"

class Matrix {
public:
    Matrix(unsigned, unsigned, double);
    Matrix operator+(Matrix &);
    Matrix operator-(Matrix &);
    Matrix operator*(Matrix &);
    Matrix operator/(Matrix &);
    Matrix transpose();

    double& operator()(const unsigned &, const unsigned &);
    void print_() const;
    unsigned getRows() const;
    unsigned getCols() const;

private:
    unsigned rows;
    unsigned columns;
    vector<vector<double> > matrix;
};


#endif 
