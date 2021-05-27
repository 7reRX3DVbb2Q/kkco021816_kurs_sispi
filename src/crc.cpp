#include"Polynom.h"

int main()
{
    Polynom u("1000110"), v("1011"), q, r;
    Polynom::div(u, v, q, r);
    return 0;
}