#include<vector>
#include<string>
class Polynom
{
    private:
    std::vector<unsigned char> coefficients;// под индексом i стоит коэффициент при x^i
    public:
    Polynom();
    Polynom(std::string);
    static void div(const Polynom& u, const Polynom& v, Polynom& q, Polynom& r);
    Polynom operator/ (Polynom&);
    Polynom operator% (Polynom&);
    size_t deg() const;
    size_t deg(size_t new_deg, unsigned char c);
    void clear();
    unsigned char& operator[] (size_t i);
    const unsigned char& operator[] (size_t i) const;
    void operator()(unsigned char);
};