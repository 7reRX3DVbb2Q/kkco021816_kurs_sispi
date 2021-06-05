#ifndef _CRC
#define _CRC 1
#include"Polynom.h"
#define x(y) (unsigned long long)1<<y
class CRC
{
private:
    Polynom polynom;
    size_t s;
    size_t n;
    size_t k;
    std::vector<Polynom> G;
public:
    CRC();
    CRC(const Polynom&, size_t n, size_t s);
    void make_new_code(const Polynom&, size_t n, size_t s);
    void code(Polynom Q, Polynom& result);
    void decode(Polynom Q, Polynom& result);
    void coder(Polynom Q, Polynom& result);
    const Polynom& get_polynom() const;
    size_t get_s() const;
    size_t get_n() const;
    size_t get_k() const;
};

size_t log_2_floor(uint64_t);
#endif