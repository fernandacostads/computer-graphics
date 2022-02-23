#include "Matrix.hpp"

Matrix::Matrix(unsigned pRows, unsigned pColumns, double initial){
    rows = pRows;
    columns = pColumns;
    matrix.resize(pRows);
    for (auto & i : matrix){
        i.resize(pColumns, initial);
    }
    if(rows > 1 && columns > 1) {
        for (unsigned l = 0; l < rows; ++l) {
            for (unsigned m = 0; m < columns; ++m) {
                if (l == m) {
                    matrix[l][m] = 1.0;
                } else {
                    matrix[l][m] = 0.0;
                }
            }
        }
    }
}

Matrix Matrix::operator+(Matrix &aux) {
    Matrix sum(columns, rows, 0.0);
    unsigned i,j;
    for (i = 0; i < rows; i++){
        for (j = 0; j < columns; j++){
            sum(i,j) = this->matrix[i][j] + aux(i,j);
        }
    }
    return sum;
}

Matrix Matrix::operator-(Matrix & aux){
    Matrix dif(rows, columns, 0.0);
    unsigned i,j;
    for (i = 0; i < rows; i++){
        for (j = 0; j < columns; j++){
            dif(i,j) = this->matrix[i][j] - aux(i,j);
        }
    }
    return dif;
}

Matrix Matrix::operator*(Matrix & B){
    Matrix multip(rows,B.getCols(),0.0);
    if(columns == B.getRows()){
        unsigned i,j,k;
        double temp = 0.0;
        for (i = 0; i < rows; i++){
            for (j = 0; j < B.getCols(); j++){
                temp = 0.0;
                for (k = 0; k < columns; k++){
                    temp += matrix[i][k] * B(k,j);
                }
                multip(i,j) = temp;
            }
        }
        return multip;
    }
    else{
        return multip;
    }
}

double& Matrix::operator()(const unsigned &rowNo, const unsigned & colNo){
    return this->matrix[rowNo][colNo];
}

unsigned Matrix::getRows() const
{
    return this->rows;
}

// returns col #
unsigned Matrix::getCols() const
{
    return this->columns;
}

// Take any given matrices transpose and returns another matrix
Matrix Matrix::transpose(){
    Matrix transpose(columns,rows,0.0);
    for (unsigned i = 0; i < columns; i++){
        for (unsigned j = 0; j < rows; j++) {
            transpose(i,j) = this->matrix[j][i];
        }
    }
    return transpose;
}

void Matrix::print_() const{
    cout << "Matrix: " << endl;
    for (unsigned i = 0; i < rows; i++) {
        for (unsigned j = 0; j < columns; j++) {
            cout << "[" << matrix[i][j] << "] ";
        }
        cout << endl;
    }
}

Matrix Matrix::operator/(Matrix &aux) {
    return (aux.transpose() * *this);
}