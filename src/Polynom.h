#ifndef _Polynom
#define _Polynom 1
#include<vector>
#include<string>
#include<cinttypes>
#include<iostream>

class Polynom
{
    private:
    std::vector<unsigned char> coefficients;//коэффициент при x^0 стоит в конце вектора, при x^1 предпоследний и т.д.
    size_t first_not_null_coefficient;  // В векторе необязательно чтобы старший коэффициент многочлена находился под индексом 0,
                                        // и данная переменная хранит индекс самого старшего ненулевого коэффицциента
                                        // Если многочлен равен нулю (все коэффициенты нулевые), то first_not_null_coefficient равен
                                        // размеру вектора + 1
    public:
    Polynom();
    Polynom(std::string);
    Polynom(uint64_t);
    Polynom(uint8_t* const point, size_t size);
    static void div(Polynom u, Polynom v, Polynom& q, Polynom& r);// Деление многочленов. u = vq + r
    static void sum(Polynom& a, Polynom b, Polynom c);//Сложение многочленов. a = b + c
    void mul_pow_x(size_t n);//Умножение многочлена на x в степени n, this = this * x^n
    void del_nulls_in_begin();  //удаляет все нулевые коэффициенты в начале вектора, пока не встретит ненулевой коэффициент.  
                                //Если все коэффициенты были нулевыми, то после выполнение процедуры останеться только 1 нулевой коэффициент
                                //(вектор coefficients будет равным содержать только один нулевой элемент) и поле first_not_null_coefficient примет значение 1
    Polynom operator/ (const Polynom&) const;//Делит многочлены и возвращает частное
    Polynom operator% (const Polynom&) const;//Делит многочлены и возвращает остаток
    Polynom operator+ (const Polynom&) const;//Суммирует многочлены и возвращает результат
    Polynom operator- (const Polynom&) const;//Вычитает многочлены и возвращает результат
    void operator+= (const Polynom&);
    void operator-= (const Polynom&);
    bool operator== (const Polynom&);//Проверка многочленов на равенство
    size_t deg() const;//Возвращает степень многочлена
    void clear();//Удаляет все коэффициенты и устанавливает first_not_null_coefficient равным нулю
    unsigned char& operator[] (size_t i);//Возвращает коэффициент при степени i
    const unsigned char& operator[] (size_t i) const;//Возвращает коэффициент при степени i
    unsigned char& operator() (size_t i);//Возвращает кожффициент пож индексом вектора i
    const unsigned char& operator() (size_t i) const;//Возвращает кожффициент пож индексом вектора i
    size_t weight() const;//Возвращает вес многочлена (количество единиц)
    void cyclic_left_shift(size_t n);//Циклический сдвиг влево
    void cyclic_right_shift(size_t n);//Циклический сдвиг вправо
    void shift_left(size_t n);//Сдвиг влево
    void shift_right(size_t n);//Сдвиг вправо
    Polynom cut(size_t deg_min, size_t deg_max) const;//Возвращает коэффициенты при степенях от deg_min до deg_max
    size_t size();//Возвращает размер вектора coefficients
    void find_first_not_null_coefficient();//Ищет первый ненулевой старший коэффициент
    size_t resize(size_t);  //Изменяет размер вектора coefficients. Если нового размера не достаточно для хранения многочлена,
                            // то вектор будет иметь минимальный рамер необходиый для хранения многочлена данной степени 
    void reverse();//Переворачиавет вектор коэффициентов (в итоге получится сопряженный многочлен)
    bool is_null() const;//Возвращает является многочлен нулевым
    template<typename T>
    void convert(std::vector<T>& output) const//Преобразует многочлен в двоичную последовательность
    {
        output.clear();
        if(coefficients.size() > 0)
        {
            output.resize( ((coefficients.size() - 1)/(sizeof(T)*8)) + 1, 0);
            for (long long i = output.size() - 1; i >= 0; i--)
            {
                for (size_t j = 0; j < sizeof(T)*8 && (output.size() - 1 - i)*sizeof(T)*8 + j < coefficients.size(); j++)
                {
                    output[i] |= (T)operator[]((output.size() - 1 - i)*sizeof(T)*8 + j) << j;
                }
                
            }
        }
        
        else{
            output.resize(1, 0);
        }
    }

    template<typename T>
    void set_polynom(T* const point, size_t size)//Преобразует двоичную последовательность в многочлен
    {
        T i = 1<<((sizeof(T)*8) - 1);
        size_t j;
        coefficients.clear();
        first_not_null_coefficient = 0;
        for (j = 0; j < size; j++, i = 1<<((sizeof(T)*8) - 1))
        {
            while (i != 0 && (point[j]&i) == 0)
            {
                i>>=1;
                coefficients.push_back(0);
                first_not_null_coefficient++;
            }
            if(i != 0)
            {
                break;
            }
        }
        for(; j < size; j++, i = 1<<((sizeof(T)*8) - 1))
        {
            while (i != 0)
            {
                coefficients.push_back((point[j]&i) > 0);
                i>>=1;
            }
        }
    }
};

// Ниже был написан функционал ассоциативного дерева, где в качестве ключа используется многочлен, 
// а в качестве значения произволный тип данных. Но он перестал использоваться.
//
// template<class T>
// struct Node
// {
//     unsigned char coefficient;
//     T data;
//     Node *left, * right;
//     Node()
//     {
//         coefficient = 0;
//         data = 0;
//         left = nullptr;
//         right = nullptr;
//     }
//    
//     Node(unsigned char c, T value)
//     {
//         coefficient = c;
//         data = value;
//         left = nullptr;
//         right = nullptr;
//     }
// };
//
// template<class T>
// class Ptree
// {
//     private:
//     Node<T> root;
//    
//     public:
//     ~Ptree()
//     {
//         clear(&root);
//     }
//
//     void add(const Polynom& polynom, T value)
//     {
//         Node<T> *point = &root, *parent;
//         size_t i;
//         for (i = 0; i <= polynom.deg() && point != nullptr; i++)
//         {
//             parent = point;
//             if(polynom[i] == 0)
//             {
//                 point = parent->left;
//             }
//             else
//             {
//                 point = parent->right;
//             }
//       
//         }
//         if(point == nullptr)
//         {
//             point = parent;
//         }
//      
//         for (i -= 1; i <= polynom.deg(); i++)
//         {
//             if (polynom[i] == 0)
//             {
//                 point->left = new Node<T>(0, 0);
//                 point = point->left;
//             }
//             else
//             {
//                 point->right = new Node<T>(1, 0);
//                 point = point->right;
//             }
//         }
//         point->data = value;
//     }
//
//     T& operator[](const Polynom& polynom)
//     {
//         Node<T> *point = &root, *parent;
//         size_t i;
//         for (i = 0; i <= polynom.deg() && point != nullptr; i++)
//         {
//             parent = point;
//             if(polynom[i] == 0)
//             {
//                 point = parent->left;
//             }
//             else
//             {
//                 point = parent->right;
//             }
//         }
//         return point->data;
//     }
// 
//     void clear(Node<T>* point)
//     {
//         if(point != nullptr)
//         {
//             clear(point->left);
//             point->left = nullptr;
//             clear(point->right);
//             point->right = nullptr;
//             if(point != &root)
//             {
//                 delete point;
//             }
//         }
//     }
// 
//     void remove(const Polynom& polynom)
//     {
//         Node<T> *point = &root, *parent = &root;
//         for (size_t i = 0; i <= polynom.deg() && point->left != nullptr && point->right != nullptr; i++)
//         {
//             parent = point;
//             if(polynom[i] == 0)
//             {
//                 point = parent->left;
//             }
//             else
//             {
//                 point = parent->right;
//             }
//         }
//         clear(point);
//     }
//
//     void operator=(const Ptree&)
//     {
//         std::cout<<std::endl<<"Копирование дерева не реализовано"<<std::endl;
//     }
// };

#endif