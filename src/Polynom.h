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
    size_t first_not_null_coefficient;
    public:
    Polynom();
    Polynom(std::string);
    Polynom(uint64_t);
    Polynom(uint8_t* const point, size_t size);
    static void div(Polynom u, Polynom v, Polynom& q, Polynom& r);
    static void sum(Polynom& a, Polynom b, Polynom c);
    void mul_pow_x(size_t n);
    void del_nulls_in_begin();
    Polynom operator/ (const Polynom&) const;
    Polynom operator% (const Polynom&) const;
    Polynom operator+ (const Polynom&) const;
    Polynom operator- (const Polynom&) const;
    void operator+= (const Polynom&);
    void operator-= (const Polynom&);
    bool operator== (const Polynom&);
    size_t deg() const;
    // size_t deg(size_t new_deg, unsigned char c);
    void clear();
    unsigned char& operator[] (size_t i);
    const unsigned char& operator[] (size_t i) const;
    unsigned char& operator() (size_t i);
    const unsigned char& operator() (size_t i) const;
    size_t weight() const;
    void cyclic_left_shift(size_t n);
    void cyclic_right_shift(size_t n);
    void shift_left(size_t n);
    void shift_right(size_t n);
    Polynom cut(size_t deg_min, size_t deg_max) const;
    size_t size();
    void find_first_not_null_coefficient();
    size_t resize(size_t);
    void reverse();
    bool is_null() const;
    template<typename T>
    void convert(std::vector<T>& output) const
    {
        output.clear();
        if(coefficients.size() > 0)
        {
            output.resize( ((coefficients.size() - 1)/(sizeof(T)*8)) + 1, 0);
            for (size_t i = output.size() - 1; i != (uint64_t)-1; i--)
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
    void set_polynom(T* const point, size_t size)
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