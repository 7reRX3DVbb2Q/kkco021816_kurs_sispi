#include"crc.h"
#include<cstdlib>
#include<iostream>
#include <stdexcept>
#include<ctime>
#include<iomanip>
using namespace std;

void print(uint8_t* point, size_t size, uint8_t radix, size_t n);
void print(char* point, size_t size);

int main()
{
    CRC crc;
    string input;
    std::vector<uint8_t> byte_polynom;
    string str_polynom;
    size_t deg, n, s, tmp, tmp2, k;
    Polynom suffix, info, code, coder, decode, e;
    vector<uint8_t> result;
    Polynom result2;
    vector<char> decode_text;
    srand(time(NULL));
    get_polynom:
    cout<<(x(33)|x(32)|x(30)|x(29)|x(28)|x(27)|x(26)|x(23)|x(22)|x(20)|x(15)|x(14)|x(13)|x(11)|x(9)|x(8)|x(6)|x(5)|x(2)|x(1)|x(0))<<endl;
    try
    {
        cout<<endl<<"Использовать образующий полином по умолчанию (0), или ввести свой? (1)"<<endl;
        cin>>input;
        if(input == "1")
        {
            cout<<endl<<"Введите n (длинну кодового слова после кодирования):"<<endl;
            cin>>n;
            cout<<endl<<"Введите s (максимальное число ошибок, которое может исправить код):"<<endl;
            cin>>s;
            cout<<endl<<"В каком формате счтывать образующий полином? (0) - последовательность байт(чисел от 0 до 255) или строка нулей и единиц(1)"<<endl;
            cin>>input;
            if(input == "1")
            {
                cout<<endl<<"Введите двоичную последовательность (пробелы игнорируются):"<<endl;
                do
                {
                    getline(cin, str_polynom);
                } while (str_polynom.length() == 0);
                
                crc.make_new_code(Polynom(str_polynom), n, s);
            }
            else
            {
                cout<<endl<<"Введите степень образующего полинома (не менее 1):"<<endl;
                do
                {
                    cin>>deg;
                    if(deg<1)
                    {
                        cout<<endl<<"Степень меньше единицы, введите степень не менее 1:"<<endl;
                    }
                } while (deg < 1);
                if (deg < 64)
                {
                    cout<<endl<<"Введите число, двоичное представление которого совпадает с коэффициентами полинома"<<endl;
                    cin>>tmp;
                    crc.make_new_code(Polynom(tmp), n, s);
                }
                else
                {
                tmp = (deg - 1)/8 + 1;
                byte_polynom.resize(tmp);
                cout<<endl<<"Введите"<< tmp << " чисел от 0 до 255:"<<endl;
                for (size_t i = 0; i < byte_polynom.size(); i++)
                {
                    do
                    {
                        cout<<endl<<"Число № "<< i+1<< " :"<<endl;
                        cin>>byte_polynom[i];
                        if(byte_polynom[i] > 255)
                        {
                            cout<<endl<<"Число не входит в диапазон, введите число от 0 до 255:"<<endl;
                        }
                    } while (byte_polynom[i] > 255);
                }
                crc.make_new_code(Polynom(&byte_polynom[0], byte_polynom.size()), n, s);
                }
                
            }
            
        }
    }
    catch(exception e)
    {
        cout<<endl<<e.what()<<endl;
        goto get_polynom;
    }
    k = crc.get_k();
    do
    {
        cout<<endl<<"Введите кодируемую информацию:"<<endl;
        do
        {
            getline(cin, input);
        } while (input.length() == 0);
        
        suffix = Polynom((uint8_t* const)input.c_str(), input.length());
        suffix.mul_pow_x(tmp = (suffix.size()%k == 0)? 0 : k - suffix.size()%k);
        suffix.shift_right(tmp);
        result2.clear();
        for (size_t offset = 0 ; offset < suffix.size(); offset += k)
        {
            info = suffix.cut(suffix.size() - k - offset, suffix.size() - 1 - offset);
                cout<<endl<<"Кодируемые биты:"<<endl;
                info.convert<uint8_t>(result);
                print(&result[0], result.size(), 2, crc.get_k());
                cout<<endl;
                print(&result[0], result.size(), 16, crc.get_k());
                cout<<endl;
            crc.code(info, code);
                cout<<endl<<"Кодовое слово полученное с помощью операций над многочленами в двоичном и шестнадцатеричном виде:"<<endl;
                code.convert<uint8_t>(result);
                print(&result[0], result.size(), 2, crc.get_n());
                cout<<endl;
                print(&result[0], result.size(), 16, crc.get_n());
                cout<<endl;
            crc.coder(info, coder);
                cout<<endl<<"Кодовое слово полученное с помощью матрицы:"<<endl;
                coder.convert<uint8_t>(result);
                print(&result[0], result.size(), 2, crc.get_n());
                cout<<endl;
                print(&result[0], result.size(), 16, crc.get_n());
                cout<<endl;
            if(code == coder)
            {
                cout<<endl<<"##################################################################"<<endl;
                cout<<endl<<"#### Кодовые слова, полученные 2 разными способами, совпадают ####"<<endl;
                cout<<endl<<"##################################################################"<<endl;
            }
            else
            {
                cout<<endl<<"!!!#####################################################################"<<endl;
                cout<<endl<<"!!!#### Кодовые слова, полученные 2 разными способами, НЕ совпадают ####"<<endl;
                cout<<endl<<"!!!#####################################################################"<<endl;
            }
            
            e = Polynom(0);
            e.resize(crc.get_n());
            for (size_t i = 0; i < crc.get_s(); i++)
            {
                e((size_t)rand()%crc.get_n()) = 1;
            }
            e.find_first_not_null_coefficient();
                cout<<endl<<"Вектор ошибок:"<<endl;
                e.convert<uint8_t>(result);
                print(&result[0], result.size(), 2, crc.get_n());
                cout<<endl;
                print(&result[0], result.size(), 16, crc.get_n());
                cout<<endl;
            code += e;
                cout<<endl<<"Искаженное ошибками кодовое слово:"<<endl;
                code.convert<uint8_t>(result);
                print(&result[0], result.size(), 2, crc.get_n());
                cout<<endl;
                print(&result[0], result.size(), 16, crc.get_n());
                cout<<endl;
            crc.decode(code, decode);
                cout<<endl<<"Декодированное слово:"<<endl;
                decode.convert<uint8_t>(result);
                print(&result[0], result.size(), 2, crc.get_k());
                cout<<endl;
                print(&result[0], result.size(), 16, crc.get_k());
                cout<<endl;
            if(info == decode)
            {
                cout<<endl<<"###################################################"<<endl;
                cout<<endl<<"#### Отправленное и полученное слово совпадают ####"<<endl;
                cout<<endl<<"###################################################"<<endl;
            }
            else
            {
                cout<<endl<<"!!!######################################################"<<endl;
                cout<<endl<<"!!!#### Отправленное и полученное слово НЕ совпадают ####"<<endl;
                cout<<endl<<"!!!######################################################"<<endl;
            }
            result2.mul_pow_x(crc.get_k());
            result2 += decode;
        }
        cout<<endl<<"Декодированное сообщение:"<<endl;
        result2.convert<char>(decode_text);
        tmp = (decode_text[0] == 0)? 1 : 0;
        cout<<endl;
        print(&decode_text[tmp], decode_text.size() - tmp);
        cout<<endl;
        
    } while (cin.eof() == false);
    
    return 0;
}

void print(uint8_t* point, size_t size, uint8_t radix,  size_t n)
{
    size_t offset = size*8 - n;
    size_t i = (offset + 1)/8;
    for (; i < size; i++)
    {
        if (radix == 2)
        {
            for (size_t j = ((offset + 1)/8 == i)? offset%8: 0, k = 1<<(7 - j); j < 8; j++, k>>=1)
            {
                if ((point[i]&k) > 0)
                {
                    cout<<1;
                }
                else
                {
                    cout<<0;
                }
                
            }
            
        }
        else
        {
            cout<<setbase(radix)<<(size_t)point[i];
        }
        cout<<" ";
    }
    
}

void print(char* point, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout<<point[i];
    }
    
}