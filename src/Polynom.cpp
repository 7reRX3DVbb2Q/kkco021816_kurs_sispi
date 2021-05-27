#include"Polynom.h"
#include <stdexcept>

size_t Polynom::deg() const
{   
    long long i;
    if (coefficients.size() == 0)
    {
        throw std::runtime_error("Полином не инициализирован");
    }
    for ( i = coefficients.size() - 1; i >= 0 && coefficients[i] == 0; i--)
    {}
    
    return i;
}
size_t Polynom::deg(size_t new_deg, unsigned char c)
{
    coefficients.clear();
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
void Polynom::div(const Polynom& u, const Polynom& v, Polynom& q, Polynom& r)
{
    r = u;
    
    q.clear();
    q.deg(u.deg(), 0);

    for (signed long long k = u.deg() - v.deg(); k >= 0; k--)
    {
        q[k] = r[v.deg() + k];
        for (signed long long j = v.deg() + k; j >= k; j--)
        {
            r[j] ^= q[k]*v[j-k];
        }
    }
    r.coefficients.resize(r.deg() + 1);
    q.coefficients.resize(q.deg() + 1);
}

Polynom Polynom:: operator/ (Polynom& v)
{
    Polynom q, r;
    div(*this, v, q, r);
    return q;
}
Polynom Polynom:: operator% (Polynom& v)
{
    Polynom q, r;
    div(*this, v, q, r);
    return r;
}

Polynom::Polynom()
{}

Polynom::Polynom(std::string str)
{
    for (long i = str.length() - 1; i >= 0; i--)
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
    
}