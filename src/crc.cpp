#include"crc.h"
#include <iostream>
#include <stdexcept>

void CRC::code(Polynom Q, Polynom& result)
{
    size_t shift;
    result.clear();
    Q.mul_pow_x(polynom.deg());
    result = Q + Q%polynom;
    shift = n - result.size();
    if(shift > 0)
    {
        result.mul_pow_x(shift);
        result.shift_right(shift);
    }
}

void CRC::decode(Polynom Q, Polynom& result)
{
    Q.find_first_not_null_coefficient();
    Polynom rem = Q%polynom;
    Polynom Q2;
    size_t shift_count;
    result.clear();
    if(rem.weight() <= s)
    {
        result = Q + rem;
    }
    else
    {
        Q2 = Q;
        for ( shift_count = 0; rem.weight() > s; shift_count++)
        {
            if(shift_count > n)
            {
                throw std::runtime_error("Ошибка декодирования: при исправлении ошибок никакой сдвиг не дает нулевой остаток при делении на образующий полином");
            }
            Q2.cyclic_left_shift(1);
            rem = Q2%polynom;

        }
        result = Q2 + rem;
        result.cyclic_right_shift(shift_count);
    }
    result = result.cut(polynom.deg(), result.size() - 1);
}

void CRC::coder(Polynom Q, Polynom& result)
{
    result = Q;
    result.mul_pow_x(polynom.deg());
    result.resize(n);
    for (size_t i = 0; i < k; i++)
    {
        if(result(i) == 1)
        {
            result += G[G.size() - 1 - i];
        }
    }
    
}

CRC::CRC()
{
    make_new_code(Polynom(0b111010001), 15,  2);
}

CRC::CRC(const Polynom& src, size_t n, size_t s)
{
    make_new_code(src, n, s);
}

void CRC::make_new_code(const Polynom& src, size_t n, size_t s)
{
    size_t k = n - src.deg();
    Polynom cycle_search;
    Polynom p(1);
    #define r n - k
    if (n <= k)
    {
        std::logic_error("n <= k");
    }
    
    p.mul_pow_x(src.deg());
    G.resize(k);
    cycle_search = p%src;
    for (size_t i = 0; i < k; i++)
    {
        G[i] = p%src;
        if(i > 0 && G[i] == cycle_search)
        {
            std::runtime_error("Данный образующий полином не обеспечивает нужное количество остатков от деления");
        }
        else if (G[i].weight() < 2*s)
        {
            std::runtime_error("Вес одной из строк образующей матрицы меньше необходимого кодового расстояния, для обеспечения возможности исправления данного количества ошибок");
        }
        else
        {
            p.mul_pow_x(1);
            G[i].resize(r);
        }
    }
    polynom = src;
    this->n = n;
    this->k = k;
    this->s = s;
    #undef r
}

// size_t log_2_floor(uint64_t n)
// {
//     size_t ret= 0;
//     for (; n > 0; ret++)
//     {
//         n>>=1;
//     }
//     return ret;
// }

size_t CRC::get_s() const
{
    return s;
}

size_t CRC::get_n() const
{
    return n;
}

size_t CRC::get_k() const
{
    return k;
}

const Polynom& CRC::get_polynom() const
{
    return polynom;
}