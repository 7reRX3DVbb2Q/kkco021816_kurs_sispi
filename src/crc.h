#ifndef _CRC
#define _CRC 1
#include"Polynom.h"
#define x(y) (unsigned long long)1<<y //для удобного построения многочленов степеней не выше 63, например многочлен x^5+x^2+1 можно записать в виде x(5)|x(2)|x(0)
class CRC
{
private:
    Polynom polynom; //Образующий многочлен
    size_t s; //Количество исправляемых ошибок
    size_t n; //Длинна кодового слова
    size_t k;  //Количество информационных битов
    std::vector<Polynom> G; //Производящая матрица
public:
    CRC();
    CRC(const Polynom&, size_t n, size_t s);
    void make_new_code(const Polynom&, size_t n, size_t s);
    void code(Polynom Q, Polynom& result);//Кодирует многочлен Q, результат записывает в result
    void decode(Polynom Q, Polynom& result);
    void coder(Polynom Q, Polynom& result);//Кодирует многочлен с помощью производящей матрицы Q, результат записывает в result
    const Polynom& get_polynom() const;
    size_t get_s() const;
    size_t get_n() const;
    size_t get_k() const;
};

// size_t log_2_floor(uint64_t);
#endif