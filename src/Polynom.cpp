#include"Polynom.h"
#include <stdexcept>

size_t Polynom::deg() const
{   
    long long i;
    if (coefficients.size() == 0)
    {
        throw std::runtime_error("Полином не инициализирован");
    }
    
    return coefficients.size() - 1;
}

size_t Polynom::deg(size_t new_deg, unsigned char c)
{
    coefficients.resize(new_deg, c);
    return coefficients.size() - 1;
}

unsigned char& Polynom::operator[] (size_t i)
{
    return coefficients[i];
}

const unsigned char& Polynom::operator[] (size_t i) const
{
    return coefficients[i];
}

void Polynom::operator()(unsigned char c)
{
    for (size_t i = 0; i < coefficients.size(); i++)
    {
        coefficients[i] = c;
    }
    
}

void Polynom::clear()
{
    coefficients.clear();
}

void Polynom::mul_pow_x(size_t n)
{
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
        }
        
    }
}

void Polynom::div(Polynom u, Polynom v, Polynom& q, Polynom& r)
{
    u.del_nulls_in_begin();
    v.del_nulls_in_begin();
    r = u;
    q.clear();
    if(v[0] == 0)
    {
        throw std::runtime_error("Деление на 0");
    }
    if(u.deg() >= v.deg())
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
        r.del_nulls_in_begin();
        if(r.coefficients.size() == 0)
        {
            r.coefficients.push_back(0);
        }
    }
    else
    {
        q.coefficients.push_back(0);
    }
    
}

void Polynom::sum(Polynom& a, Polynom b, Polynom c)
{
    const Polynom* max;
    const Polynom* min;
    b.del_nulls_in_begin();
    c.del_nulls_in_begin();
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
{}

Polynom::Polynom(std::string str)
{   
    size_t i;
    bool is_null = false;
    for (i = 0; i < str.length() && str[i] != '1'; i++)
    {
        if (str[i] == 0)
        {
            is_null = true;
        }
        
    }
    
    for (; i < str.length(); i++)
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
    if(i == str.length() && is_null)
    {
        coefficients.push_back(0);
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
    }
    while (i != 0)
    {
        coefficients.push_back((number&i) > 0);
        i>>=1;
    }
    
    
}

size_t Polynom::weight() const
{
    size_t weight = 0;
    for (size_t i = 0; i < coefficients.size(); i++)
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
}

void Polynom::cyclic_right_shift(size_t n)
{
    size_t N = n%coefficients.size();
    std::vector<unsigned char> tmp(coefficients.end() - n, coefficients.end());
    coefficients.insert(coefficients.begin(), tmp.begin(), tmp.end());
    coefficients.erase(coefficients.end() - N, coefficients.end());
}

void Polynom::shift_left(size_t n)
{
    size_t N = std::min(n, coefficients.size());
    coefficients.erase(coefficients.begin(), coefficients.begin() + N);
    coefficients.insert(coefficients.end(), N, 0);

}

void Polynom::shift_right(size_t n)
{
    size_t N = std::min(n, coefficients.size());
    coefficients.erase(coefficients.end() - N, coefficients.end());
    coefficients.insert(coefficients.begin(), N, 0);
}

Polynom Polynom::cut(size_t deg_min, size_t deg_max)
{
    Polynom ret;
    std::copy(coefficients.end() - deg_max - 1, coefficients.end() - deg_min - 1, std::back_inserter(ret.coefficients));
    return ret;
}
