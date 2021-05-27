#include"crc.h"
#include<cstdlib>
using namespace std;
int main()
{
    CRC crc;
    char number[255];
    vector<Polynom> results;
    Polynom q, r;
    Polynom::div(Polynom("1000110"), Polynom("1011"), q, r);
    Polynom::div(Polynom("11100110"), Polynom("1010"), q, r);
    Polynom::div(Polynom("1100101"), Polynom("1001"), q, r);
    for (size_t i = 0; i < 16; i++)
    {
        results.push_back(Polynom());
        crc.code(Polynom(i), results[i]);
    }
    q = (0b111000101);
    q.cyclic_left_shift(3);
    q.cyclic_right_shift(3);
    return 0;
}