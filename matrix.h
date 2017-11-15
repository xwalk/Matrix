#ifndef __MATRIX_H_
#define __MATRIX_H_

/*
 * 说明：
 * 1.内部以列向量组织
*/
#include "vect.h"

template < unsigned int row, unsigned int column >
class Matrix
{
public:
    Matrix(double d0=0);
    Matrix(Vect<row> v);
    Matrix(double arg1,double arg2,...);
    Matrix(Vect<row> arg1,Vect<row>arg2,...);

    Matrix<row,column> operator +(const Matrix<row,column>& m1)const;
    Matrix<row,column> operator -(const Matrix<row,column>& m1)const;
    template<unsigned int column2>
    Matrix<row,column2> operator *(const Matrix<column,column2>& m1)const;
    Matrix<row,column> operator *(double n)const;
    Matrix<column,row> T()const;
    bool det(double& d0)const;
    bool Inv(Matrix<row,row>& m1)const;

    template < unsigned int r, unsigned int c >
    friend class Matrix;
    template < unsigned int r, unsigned int c >
    friend Matrix<r,c> operator *(double n, const Matrix<r,c>& m1);
    template < unsigned int r, unsigned int c >
    friend std::ostream& operator<<(std::ostream& out ,const Matrix<r,c>& m1);

private:
    Vect<row> col[column];
};

template < unsigned int row, unsigned int column >
Matrix<row,column>::Matrix(double d0)
{
    for( unsigned int i=0; i<column; i++ )
    {
        col[i] = Vect<row>(d0);
    }
}

template < unsigned int row, unsigned int column >
Matrix<row,column>::Matrix(Vect<row> v)
{
    for( unsigned int i=0; i<column; i++ )
    {
        col[i] = v;
    }
}

template < unsigned int row, unsigned int column >
Matrix<row,column>::Matrix(double arg1,double arg2,...)
{
    va_list vl;
    va_start(vl,arg2);

    col[0].m_data[0] = arg1;
    col[1].m_data[0] = arg2;

    for( unsigned int i=0; i<row; i++ )
    {
        for( unsigned int j=0; j<column; j++ )
        {
            if( i==0 && (j==0 || j==1) ) continue;
            col[j].m_data[i]= va_arg(vl,double);
        }
    }
    va_end(vl);
}

template < unsigned int row, unsigned int column >
Matrix<row,column>::Matrix(Vect<row> arg1,Vect<row>arg2,...)
{
    va_list vl;
    va_start(vl,arg2);

    col[0] = arg1;
    col[1] = arg2;

    for( unsigned int i=2; i<column; i++ )
    {
        col[i]= va_arg(vl,Vect<row>);
    }
    va_end(vl);
}

template < unsigned int row, unsigned int column >
Matrix<row,column> Matrix<row,column>::operator +(const Matrix<row,column>& m1)const
{
    Matrix<row,column> ret;

    for( unsigned int i=0; i<column; i++ )
    {
        ret.col[i] = col[i] + m1.col[i];
    }

    return ret;
}

template < unsigned int row, unsigned int column >
Matrix<row,column> Matrix<row,column>::operator -(const Matrix<row,column>& m1)const
{
    Matrix<row,column> ret;

    for( unsigned int i=0; i<column; i++ )
    {
        ret.col[i] = col[i] - m1.col[i];
    }

    return ret;
}

template < unsigned int row, unsigned int column >
template<unsigned int column2>
Matrix<row,column2> Matrix<row,column>::operator *(const Matrix<column,column2>& m1)const
{
    Matrix<row,column2> ret;

    for( unsigned int i=0; i<column; i++ )
    {
        for( unsigned int j=0; j<row; j++ )
        {
            for( unsigned int k=0; k<column2; k++ )
            {
                ret.col[k].m_data[j] +=
                        col[i].m_data[j] * m1.col[k].m_data[i];
            }
        }
    }

    return ret;
}

template < unsigned int row, unsigned int column >
Matrix<row,column> Matrix<row,column>::operator *(double n)const
{
    Matrix<row,column> ret;

    for( unsigned int i=0; i<column; i++ )
    {
        ret.col[i] = col[i] * n;
    }

    return ret;
}

template < unsigned int row, unsigned int column >
Matrix<column,row> Matrix<row,column>::T()const
{
    Matrix<column,row> ret;

    for( unsigned int i=0; i<row; i++ )
    {
        for( unsigned int j=0; j<column; j++ )
        {
            ret.col[i].m_data[j] = col[j].m_data[i];
        }
    }

    return ret;
}

template < unsigned int row, unsigned int column >
bool Matrix<row,column>::det(double& d0)const
{
    bool ret = false;

    if( row == column )
    {
        ret = true;
        d0 = 1;
        //
    }

    return ret;
}

template < unsigned int row, unsigned int column >
bool Matrix<row,column>::Inv(Matrix<row,row>& m1)const
{
    bool ret = false;

    double val = 0.0;
    if( det(val) )
    {
        if( !FEQ(val,0) )
        {
            //
        }
    }


    return ret;
}

template < unsigned int r, unsigned int c >
Matrix<r,c> operator *(double n, const Matrix<r,c>& m1)
{
    Matrix<r,c> ret;

    for( unsigned int i=0; i<c; i++ )
    {
        ret.col[i] = m1.col[i] * n;
    }

    return ret;
}

template < unsigned int r, unsigned int c >
std::ostream& operator<<(std::ostream& out ,const Matrix<r,c>& m1)
{

    for(unsigned int i=0; i<r; i++)
    {
        out << "| ";
        for( unsigned int j=0; j<c; j++ )
        {
            out << m1.col[j].data(i);
            if( j != c-1 )
            {
                out << " ";
            }
        }
        out << " |";
        if( i != r -1 )
        {
            out << std::endl;
        }
    }
    return out;
}

#endif // MATRIX_H
