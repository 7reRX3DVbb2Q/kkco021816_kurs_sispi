#include"Polynom.h"

#define x(y) (unsigned long long)1<<y
class CRC
{
private:
    Polynom polynom;
    size_t t_n;
    size_t n;
    size_t k;
    size_t d;
    std::vector<std::vector<unsigned char>> G;
public:
    CRC();
    CRC(const Polynom&, size_t n, size_t k, size_t t_n);
    void code(Polynom Q, Polynom& result);
    void decode(const Polynom& Q, Polynom& result);
};

size_t log_2_floor(size_t);