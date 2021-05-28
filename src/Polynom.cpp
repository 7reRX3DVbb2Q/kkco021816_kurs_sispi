#include"Polynom.h"
#include <stdexcept>

size_t Polynom::deg() const
{   
    long long i;
    if (coefficients.size() == 0)
    {
        throw std::runtime_error("Полином не инициализирован");
    }
    
    return coefficients.size() - index_senior_coefficient - 1;
}

unsigned char& Polynom::operator[] (size_t i)
{
    return coefficients[i + index_senior_coefficient];
}

const unsigned char& Polynom::operator[] (size_t i) const
{
    return coefficients[i + index_senior_coefficient];
}

// void Polynom::operator()(unsigned char c)
// {
//     for (size_t i = 0; i < coefficients.size(); i++)
//     {
//         coefficients[i] = c;
//     }
//
// }

void Polynom::clear()
{
    coefficients.clear();
    index_senior_coefficient = 0;
}

void Polynom::mul_pow_x(size_t n)
{
    coefficients.resize(coefficients.size() + n, 0);
}

void Polynom::del_nulls_in_begin()
{
    size_t n;
    index_senior_coefficient = 0;
    for ( n = 0; n < coefficients.size() && coefficients[n] == 0; n++)
    {}
    if(n > 0)
    {
        coefficients.erase(coefficients.begin(), coefficients.begin() + n);
        if(coefficients.size() == 0)
        {
            coefficients.push_back(0);
        }
    }
}

void Polynom::div(const Polynom& u, const Polynom& V, Polynom& q, Polynom& r)
{
    Polynom v = V;
    v.del_nulls_in_begin();
    r = u;
    r.del_nulls_in_begin();
    q.clear();
    if(v.coefficients.size() == 0)
    {
        throw std::runtime_error("Деление на 0");
    }
    if(r.deg() >= v.deg())
    {
        for (long long k = 0; k <= u.deg() - v.deg(); k++ )
        {
            q.coefficients.push_back(r.coefficients[0]);
            for (size_t j = 0; j <= v.deg(); j++)
            {
                r[j] ^= q[k]*v[j];
            }
            r.coefficients.erase(r.coefficients.begin(), r.coefficients.begin() + 1);
        }
        // r.del_nulls_in_begin();
        // if(r.coefficients.size() == 0)
        // {
        //     r.coefficients.push_back(0);
        // }
        if(r.coefficients.size() < V.coefficients.size() - 1)
        {
            // r.shift_right(v.deg() - r.deg());
            r.coefficients.insert(r.coefficients.begin(), V.coefficients.size() - r.coefficients.size(), 0);
        }
        if(r.coefficients.size() + q.coefficients.size() < u.coefficients.size())
        {
            q.coefficients.insert(q.coefficients.begin(), u.coefficients.size() - r.coefficients.size() - q.coefficients.size(), 0);
            // q.shift_right(u.deg() - r.deg() - q.deg());
        }
    }
    else
    {
        q.coefficients.push_back(0);
    }
    
}

void Polynom::sum(Polynom& a, const Polynom& b, const Polynom& c)
{
    const Polynom* max;
    const Polynom* min;
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
    a.coefficients.resize(max->deg() + 1);
    #define delta (max->deg() - min->deg())
    for (size_t i = 0; i < delta; i++)
    {
        a[i] = max->coefficients[i];
    }
    
    for (size_t i = delta; i <= max->deg(); i++)
    {
        a.coefficients[i] = max->coefficients[i]^min->coefficients[i - delta];
    }
    #undef delta
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

Polynom::Polynom()
{
    index_senior_coefficient = 0;
}

Polynom::Polynom(std::string str)
{   
    size_t i;
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
    }
    
    search_senior_coefficient();
}

Polynom::Polynom(uint64_t number)
{
    uint64_t i = (uint64_t)1<<(sizeof(number)*8 - 1);
    while (i != 0)
    {
        coefficients.push_back((number&i) > 0);
        i>>=1;
    }
    
    search_senior_coefficient();
    
}

size_t Polynom::weight() const
{
    size_t weight = 0;
    for (size_t i = index_senior_coefficient; i < coefficients.size(); i++)
    {
        if(coefficients[i] == 1)
        {
            weight++;
        }
    }
    return weight;
}

void Polynom::cyclic_left_shift(size_t n)
{
    size_t N = n%coefficients.size();
    coefficients.insert(coefficients.end(), coefficients.begin(), coefficients.begin() + N);
    coefficients.erase(coefficients.begin(), coefficients.begin() + N);
    search_senior_coefficient();
}

void Polynom::cyclic_right_shift(size_t n)
{
    size_t N = n%coefficients.size();
    std::vector<unsigned char> tmp(coefficients.end() - n, coefficients.end());
    coefficients.insert(coefficients.begin(), tmp.begin(), tmp.end());
    coefficients.erase(coefficients.end() - N, coefficients.end());
    search_senior_coefficient();
}

void Polynom::shift_left(size_t n)
{
    size_t N = std::min(n, coefficients.size());
    coefficients.erase(coefficients.begin(), coefficients.begin() + N);
    coefficients.insert(coefficients.end(), N, 0);
    search_senior_coefficient();

}

void Polynom::shift_right(size_t n)
{
    size_t N = std::min(n, coefficients.size());
    coefficients.erase(coefficients.end() - N, coefficients.end());
    coefficients.insert(coefficients.begin(), N, 0);
    search_senior_coefficient();
}

void Polynom::search_senior_coefficient()
{
    size_t i;
    for (i = 0; i < coefficients.size() && coefficients[i] == 0; i++)
    {}
    if(coefficients.size() > 0)
    {
        index_senior_coefficient = (i == coefficients.size())? i - 1: i;
    }
    else
    {
        index_senior_coefficient = 0;
    }
}
