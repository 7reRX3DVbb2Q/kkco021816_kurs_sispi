#include<vector>
#include<string>
#include<cinttypes>
class Polynom
{
    private:
    std::vector<unsigned char> coefficients;//коэффициент при x^0 стоит в конце вектора, при x^1 предпоследний и т.д.
    size_t index_senior_coefficient;
    void search_senior_coefficient();
    public:
    Polynom();
    Polynom(std::string);
    Polynom(uint64_t);
    static void div(const Polynom& u, const Polynom& v, Polynom& q, Polynom& r);
    static void sum(Polynom& a, const Polynom& b, const Polynom& c);
    void mul_pow_x(size_t n);
    void del_nulls_in_begin();
    static void mul(Polynom& a, const Polynom& b, const Polynom& c);
    Polynom operator/ (const Polynom&) const;
    Polynom operator% (const Polynom&) const;
    Polynom operator+ (const Polynom&) const;
    Polynom operator- (const Polynom&) const;
    size_t deg() const;
    void clear();
    unsigned char& operator[] (size_t i);
    const unsigned char& operator[] (size_t i) const;
    void operator()(unsigned char);
    size_t weight() const;
    void cyclic_left_shift(size_t n);
    void cyclic_right_shift(size_t n);
    void shift_left(size_t n);
    void shift_right(size_t n);
};