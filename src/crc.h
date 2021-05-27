#include"Polynom.h"

class CRC
{
private:
    Polynom polynom;
    size_t t_n;
public:
    CRC();
    CRC(const Polynom&);
    void code(const Polynom& Q, Polynom& result);
    void decode(const Polynom& Q, Polynom& result);
};