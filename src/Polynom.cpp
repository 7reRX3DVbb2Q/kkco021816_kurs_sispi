#include"Polynom.h"
#include <stdexcept>
#include <algorithm>
size_t Polynom::deg() const
{   
    long long i;
    if (coefficients.size() == 0)
    {
        throw std::runtime_error("Полином не инициализирован");
    }
    else if(is_null())
    {
        return 0;
    }
    
    return coefficients.size() - first_not_null_coefficient - 1;
}

unsigned char& Polynom::operator[] (size_t i)
{
    if(i >= coefficients.size())
    {
        throw std::length_error("Выход за границы вектора");
    }
    else
    {
        return coefficients[coefficients.size() - 1 - i];
    }
}

const unsigned char& Polynom::operator[] (size_t i) const
{
    if(i >= coefficients.size())
    {
        throw std::length_error("Выход за границы вектора");
    }
    else
    {
        return coefficients[coefficients.size() - 1 - i];
    }
}

unsigned char& Polynom::operator() (size_t i)
{
    if(i >= coefficients.size())
    {
        throw std::length_error("Выход за границы вектора");
    }
    return coefficients[i];
}

const unsigned char& Polynom::operator() (size_t i) const
{
    if(i >= coefficients.size())
    {
        throw std::length_error("Выход за границы вектора");
    }
    return coefficients[i];
}

void Polynom::clear()
{
    coefficients.clear();
    first_not_null_coefficient = 0;
}

void Polynom::mul_pow_x(size_t n)
{
    if(is_null())
    {
        first_not_null_coefficient += n;
    }
    coefficients.resize(coefficients.size() + n, 0);
}

void Polynom::del_nulls_in_begin()
{
    if(coefficients.size() > 0)
    {
        while (coefficients.size() > 0 && coefficients.front() == 0)
        {
            coefficients.erase(coefficients.begin(), coefficients.begin() + 1);
        }
        if (coefficients.size() == 0)
        {
            coefficients.push_back(0);
            first_not_null_coefficient = 1;
        }
        else
        {
            first_not_null_coefficient = 0;
        }
    }
}

void Polynom::div(Polynom u, Polynom v, Polynom& q, Polynom& r)
{
    // u.del_nulls_in_begin();
    // v.del_nulls_in_begin();
    r = u;
    q.clear();
    if( v.coefficients.size() > 0 && v.first_not_null_coefficient >= v.coefficients.size())
    {
        throw std::logic_error("Деление на 0");
    }
    if(u.deg() >= v.deg())
    {
        for (long long k = 0; k <= u.deg() - v.deg(); k++ )
        {
            q.coefficients.push_back(r[r.deg()]);
            if(r[r.deg()] == 1)
            {
                for (size_t j = r.deg() - v.deg(), i = 0; i <= v.deg(); j++, i++)
                {
                    r[j] ^= q[k]*v[i];
                }
            }
            r.first_not_null_coefficient++;
        }
        r.find_first_not_null_coefficient();
        q.first_not_null_coefficient = 0;
        // r.del_nulls_in_begin();
        // if(r.first_not_null_coefficient == r.coefficients.size())
        // {
        //     r.coefficients.push_back(0);
        //     r.first_not_null_coefficient = 1;
        // }
    }
    else
    {
        q.coefficients.push_back(0);
        q.first_not_null_coefficient = 1;
    }
    
}

void Polynom::sum(Polynom& a, Polynom b, Polynom c)
{
    const Polynom* max;
    const Polynom* min;
    // b.del_nulls_in_begin();
    // c.del_nulls_in_begin();
    if(c.deg() > b.deg())
    {
        max = &c;
        min = &b;
    }
    else
    {
        max = &b;
        min = &c;
    }
    
    a = *max;
    for (size_t i = 0; i <= min->deg(); i++)
    {
        a[i] ^= min->operator[](i);
    }
    a.find_first_not_null_coefficient();
}

Polynom Polynom:: operator/ (const Polynom& v) const
{
    Polynom q, r;
    div(*this, v, q, r);
    return q;
}

Polynom Polynom:: operator% (const Polynom& v) const
{
    Polynom q, r;
    div(*this, v, q, r);
    return r;
}

Polynom Polynom:: operator+ (const Polynom& v) const
{
    Polynom cp;
    sum(cp, *this, v);
    return cp;
}

Polynom Polynom::operator- (const Polynom& v) const
{
    return operator+(v);
}

void Polynom::operator+=(const Polynom& v)
{
    sum(*this, *this, v);
}

void Polynom::operator-=(const Polynom& v)
{
    sum(*this, *this, v);
}

Polynom::Polynom()
{
    coefficients.push_back(0);
    first_not_null_coefficient = 1;
}

Polynom::Polynom(std::string str)
{   
    size_t i;
    bool _is_null = true;
    
    first_not_null_coefficient = 0;

    for (i = 0; i < str.length(); i++)
    {
        if(str[i] == '1')
        {
            coefficients.push_back(1);
        }
        else if(str[i] == '0')
        {
            coefficients.push_back(0);
        }
        if(_is_null)
        {
            if(str[i] =='0')
            {
                first_not_null_coefficient++;
            }
            else if (str[i] =='1')
            {
                _is_null = false;
            }           
        }
    }
    
}

Polynom::Polynom(uint64_t number)
{
    uint64_t i = (uint64_t)1<<(sizeof(number)*8 - 1);
    while (i != 0 && (number&i) == 0)
    {
        i>>=1;
    }
    if(i == 0)
    {
        coefficients.push_back(0);
        first_not_null_coefficient = 1;
    }
    else
    {
        while (i != 0)
        {
            coefficients.push_back((number&i) > 0);
            i>>=1;
        }
        first_not_null_coefficient = 0;
    }
}

Polynom::Polynom(uint8_t* const point, size_t size)
{
    set_polynom<uint8_t>(point, size);
}

size_t Polynom::weight() const
{
    size_t weight = 0;
    if (coefficients.size() != 0 && is_null())
    {
        return 0;
    }
    
    for (size_t i = 0; i < coefficients.size(); i++)
    {
        if(coefficients[i] == 1)
        {
            weight++;
        }
    }
    return weight;
}

void Polynom::find_first_not_null_coefficient()
{
    size_t i;
    for (i = 0; i < coefficients.size() && coefficients[i] == 0; i++)
    {}
    first_not_null_coefficient = i;
}

void Polynom::cyclic_left_shift(size_t n)
{
    size_t N = n%coefficients.size();
    coefficients.insert(coefficients.end(), coefficients.begin(), coefficients.begin() + N);
    coefficients.erase(coefficients.begin(), coefficients.begin() + N);
    find_first_not_null_coefficient();
}

void Polynom::cyclic_right_shift(size_t n)
{
    size_t N = n%coefficients.size();
    std::vector<unsigned char> tmp(coefficients.end() - n, coefficients.end());
    coefficients.insert(coefficients.begin(), tmp.begin(), tmp.end());
    coefficients.erase(coefficients.end() - N, coefficients.end());
    find_first_not_null_coefficient();
}

void Polynom::shift_left(size_t n)
{
    size_t N = std::min(n, coefficients.size());
    coefficients.erase(coefficients.begin(), coefficients.begin() + N);
    coefficients.insert(coefficients.end(), N, 0);
    find_first_not_null_coefficient();
}

void Polynom::shift_right(size_t n)
{
    size_t N = std::min(n, coefficients.size());
    coefficients.erase(coefficients.end() - N, coefficients.end());
    coefficients.insert(coefficients.begin(), N, 0);
    first_not_null_coefficient += n;
    if(is_null())
    {
        first_not_null_coefficient = coefficients.size();
    }
}

Polynom Polynom::cut(size_t deg_min, size_t deg_max) const
{
    Polynom ret;
    ret.clear();
    std::copy(coefficients.end() - deg_max - 1, coefficients.end() - deg_min, std::back_inserter(ret.coefficients));
    ret.find_first_not_null_coefficient();
    return ret;
}

size_t Polynom::size()
{
    return coefficients.size();
}

size_t Polynom::resize(size_t new_size)
{
    size_t offset;
    if(new_size < coefficients.size())
    {
        offset = coefficients.size() - new_size;
        if(deg() + 1 < new_size)
        {
            coefficients.erase(coefficients.begin(), coefficients.begin() + offset);
            first_not_null_coefficient -= offset;
        }
        else
        {
            del_nulls_in_begin();
        }
    }
    else if (new_size > coefficients.size())
    {
        offset = new_size - coefficients.size();
        coefficients.insert(coefficients.begin(), offset, 0);
        first_not_null_coefficient += offset;
    }
    
    return coefficients.size();
}

void Polynom::reverse()
{
    del_nulls_in_begin();
    std::reverse(coefficients.begin(), coefficients.end());
}

bool Polynom::is_null() const
{
    return first_not_null_coefficient >= coefficients.size();
}

bool Polynom::operator== (const Polynom& right)
{
    bool ret = false;
    size_t i;
    if(deg() == right.deg())
    {
        for (i = 0; i <= deg() && operator[](i) == right[i]; i++)
        {}
        if(i == deg() + 1)
        {
            ret = true;
        }
    }
    return ret;
}