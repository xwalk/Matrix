#ifndef __VECT_H_
#define __VECT_H_

#include <stdarg.h>
#include <iostream>
#include "matrix.h"

#define Fmin 1e-6
#define FEQ(a,b) (a)-(b)<Fmin && (a)-(b)>-Fmin

/*
 * 说明：
 * 1.叉乘只支持三维向量
 * 2.使用不定参数的构造函数必须传递浮点参数（内部使用浮点解析）
*/

template< unsigned int size >
class Vect
{
public:
    Vect(double v0 = 0);
    Vect(double v[]);
    Vect(double arg1,double arg2,...);

    double data(unsigned int i)const;

    Vect<size> operator +(const Vect<size>& v1)const;
    Vect<size> operator -(const Vect<size>& v1)const;
    Vect<size> operator *(double n)const;
    Vect<3> operator *(const Vect<3>& v1)const;
    double dotProduct(const Vect<size>& v1)const;

    template < unsigned int row, unsigned int column >
    friend class Matrix;
    template< unsigned int s >
    friend Vect<s> operator *(double n,const Vect<s>& v);
    template< unsigned int s >
    friend std::ostream& operator<<(std::ostream& out ,const Vect<s>& vt);
private:
    double m_data[size];
};

template< unsigned int size >
Vect<size>::Vect(double v0)
{
    for( unsigned int i=0; i< size; i++ )
    {
       m_data[i] = v0;
    }
}

template< unsigned int size >
Vect<size>::Vect(double v[])
{
    for( unsigned int i=0; i< size; i++ )
    {
       m_data[i] = v[i];
    }
}

template< unsigned int size >
Vect<size>::Vect(double arg1,double arg2,...)
{
    va_list vl;
    va_start(vl,arg2);
    m_data[0] = arg1;
    m_data[1] = arg2;
    for( unsigned int i=2; i<size; i++ )
    {
        m_data[i]= va_arg(vl,double);
    }
    va_end(vl);
}

template< unsigned int size >
double Vect<size>::data(unsigned int i)const
{
    double ret;

    if( i<size )
    {
        ret = m_data[i];
    }

    return ret;
}

template< unsigned int size>
Vect<size> Vect<size>::operator +(const Vect<size>& v1)const
{
    Vect<size> ret;

    for( unsigned int i=0; i<size; i++ )
    {
        ret.m_data[i] = m_data[i] + v1.m_data[i];
    }

    return ret;
}

template< unsigned int size >
Vect<size> Vect<size>::operator -(const Vect<size>& v1)const
{
    Vect<size> ret;

    for( unsigned int i=0; i<size; i++ )
    {
        ret.m_data[i] = m_data[i] - v1.m_data[i];
    }

    return ret;
}

template<unsigned int size>
Vect<size> Vect<size>::operator *(double n)const
{
    Vect<size> ret;

    for( unsigned int i=0; i<size; i++ )
    {
        ret.m_data[i] = m_data[i]*n;
    }

    return ret;
}

template<unsigned int size>
Vect<3> Vect<size>::operator *(const Vect<3>& v1)const
{
    Vect<3> ret;

    ret.m_data[0] = m_data[1] * v1.m_data[2]  -  m_data[2] * v1.m_data[1];
    ret.m_data[1] = m_data[2] * v1.m_data[0]  -  m_data[0] * v1.m_data[2];
    ret.m_data[2] = m_data[0] * v1.m_data[1]  -  m_data[1] * v1.m_data[0];

    return ret;
}

template<unsigned int size>
double Vect<size>::dotProduct(const Vect<size>& v1)const
{
    double ret = 0.0;

    for( unsigned int i=0; i<size; i++ )
    {
        ret += m_data[i]*v1.m_data[i];
    }

    return ret;
}

template<unsigned int s>
Vect<s> operator *(double n,const Vect<s>& v)
{
    Vect<s> ret;

    for( unsigned int i=0; i<s; i++ )
    {
        ret.m_data[i] = v.m_data[i]*n;
    }

    return ret;
}

template< unsigned int s >
std::ostream& operator<<(std::ostream& out ,const Vect<s>& vt)
{
    out << "(";
    for(unsigned int i=0; i<s; i++)
    {
        out << vt.m_data[i];
        if( i != s-1 )
        {
            out << ",";
        }
    }
    out << ")";
    return out;
}

#endif // VECT_H


