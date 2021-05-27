#include"crc.h"

void CRC::code(const Polynom& Q, Polynom& result){
    Polynom Q2 = Q;
    result.clear();
    Q2.mul_pow_x(polynom.deg());
    result = Q2 + Q2%polynom;
}

void CRC::decode(const Polynom& Q, Polynom& result){
    Polynom rem = Q%polynom;
    Polynom Q2;
    result.clear();
    if(rem.weight() <= t_n)
    {
        result = Q + rem;
    }
    else
    {
        Q2 = Q;
        Q2.cyclic_left_shift(1);
    }
}

CRC::CRC()
{
    polynom = Polynom(0b1101);
    t_n = 1;
}
CRC::CRC(const Polynom& src)
{
    polynom = src;
}