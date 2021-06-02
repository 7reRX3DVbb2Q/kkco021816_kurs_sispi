#include"crc.h"
std::vector<std::pair<size_t, Polynom>> polynom_table = //(1 стобец - n, второй - многочлен)
                                                        //Таблица порождающих многочленов из книги
                                                        //<<Кодирование информации (двоичные коды) 
                                                        //Березюк Н. Т., Андрущенко А. Г., Мощицкий С. С. и др.>>
                                                        //страница 182 
{
    std::make_pair(15,   Polynom(x(6)|x(3)|x(2)|x(1)|x(0))),
    std::make_pair(27,   Polynom(x(7)|x(4)|x(1)|x(0))),
    std::make_pair(63,   Polynom(x(8)|x(5)|x(2)|x(1)|x(0))),
    std::make_pair(121,  Polynom(x(9)|x(6)|x(1)|x(0))),
    std::make_pair(255,  Polynom(x(10)|x(7)|x(4)|x(2)|x(0))),
    std::make_pair(487,  Polynom(x(11)|x(9)|x(7)|x(6)|x(5)|x(4)|x(3)|x(2)|x(1)|x(0))),
    std::make_pair(1023, Polynom(x(12)|x(5)|x(4)|x(3)|x(0))),
    std::make_pair(1999, Polynom(x(13)|x(12)|x(11)|x(9)|x(8)|x(7)|x(6)|x(4)|x(3)|x(2)|x(0))),
    std::make_pair(19,   Polynom(x(8)|x(6)|x(4)|x(1)|x(0))),
    std::make_pair(35,   Polynom(x(9)|x(8)|x(4)|x(3)|x(0))),
    std::make_pair(82,   Polynom(x(10)|x(7)|x(5)|x(3)|x(2)|x(0))),
    std::make_pair(164,  Polynom(x(11)|x(10)|x(7)|x(5)|x(3)|x(2)|x(0))),
    std::make_pair(511,  Polynom(x(12)|x(8)|x(5)|x(3)|x(0))),
    std::make_pair(1023, Polynom(x(13)|x(12)|x(6)|x(3)|x(1)|x(0))),
    std::make_pair(1647, Polynom(x(14)|x(13)|x(10)|x(9)|x(8)|x(6)|x(5)|x(4)|x(3)|x(0))),
    std::make_pair(24,   Polynom(x(10)|x(7)|x(6)|x(5)|x(3)|x(2)|x(0))),
    std::make_pair(47,   Polynom(x(11)|x(9)|x(7)|x(5)|x(4)|x(3)|x(2)|x(1)|x(0))),
    std::make_pair(127,  Polynom(x(12)|x(11)|x(8)|x(7)|x(6)|x(3)|x(1)|x(0))),
    std::make_pair(290,  Polynom(x(13)|x(10)|x(7)|x(6)|x(5)|x(2)|x(0))),
    std::make_pair(765,  Polynom(x(14)|x(9)|x(8)|x(2)|x(0))),
    std::make_pair(31,   Polynom(x(12)|x(11)|x(9)|x(6)|x(5)|x(4)|x(3)|x(1)|x(0))),
    std::make_pair(64,   Polynom(x(13)|x(11)|x(8)|x(7)|x(6)|x(3)|x(1)|x(0))),
    std::make_pair(165,  Polynom(x(14)|x(12)|x(11)|x(10)|x(9)|x(8)|x(7)|x(5)|x(3)|x(0))),
    std::make_pair(363,  Polynom(x(15)|x(14)|x(13)|x(12)|x(8)|x(7)|x(6)|x(5)|x(4)|x(2)|x(1)|x(0))),
    std::make_pair(819,  Polynom(x(16)|x(15)|x(14)|x(13)|x(11)|x(10)|x(9)|x(7)|x(4)|x(3)|x(2)|x(0))),
    std::make_pair(31,   Polynom(x(14)|x(11)|x(9)|x(8)|x(7)|x(3)|x(0))),
    std::make_pair(99,   Polynom(x(15)|x(11)|x(10)|x(9)|x(8)|x(4)|x(3)|x(0))),
    std::make_pair(144,  Polynom(x(16)|x(15)|x(14)|x(13)|x(12)|x(11)|x(10)|x(9)|x(8)|x(7)|x(4)|x(2)|x(1)|x(0))),
    std::make_pair(50,   Polynom(x(16)|x(13)|x(11)|x(8)|x(6)|x(4)|x(3)|x(0)))
};

void CRC::code(Polynom Q, Polynom& result){
    result.clear();
    Q.mul_pow_x(polynom.deg());
    result = Q + Q%polynom;
}

void CRC::decode(const Polynom& Q, Polynom& result){
    Polynom rem = Q%polynom;
    Polynom Q2;
    size_t shift_count;
    result.clear();
    if(rem.weight() <= t_n)
    {
        result = Q + rem;
    }
    else
    {
        Q2 = Q;
        for ( shift_count = 0; rem.weight() > t_n; shift_count++)
        {
            Q2.cyclic_left_shift(1);
            rem = Q2%polynom;

        }
        result = Q2 + rem;
        result.cyclic_right_shift(shift_count);
    }
}

CRC::CRC()
{
    size_t m;
    // polynom = Polynom(0b1101);
    polynom = polynom_table[0].second;
    n = polynom_table[0].first;
    k = n - polynom.deg();
    m = log_2_floor(n + 1)/2;
    t_n = polynom.deg() / m - 1;   
}
CRC::CRC(const Polynom& src, size_t n, size_t k, size_t t_n)
{
    polynom = src;
    this->n = n;
    this->k = k;
    this->t_n = t_n;
}

size_t log_2_floor(size_t n)
{
    size_t ret= 0;
    for (; n > 0; ret++)
    {
        n>>=1;
    }
    return ret;
}