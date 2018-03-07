#include <iostream>
#include <type_traits>
#include <limits>
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <string>
#include <algorithm>

template<typename T>
std::string name()
{
    auto name = typeid(T).name();
    switch(name[0])
    {
        case 'D':
            switch(name[1])
            {
                case 'i': return "char32_t";
                case 'n': return "std::nullptr_t";
                case 's': return "char16_t";
            }
            return "";
        case 'a': return "signed char";
        case 'b': return "bool";
        case 'c': return "char";
        case 'd': return "double";
        case 'e': return "long double";
        case 'f': return "float";
        case 'h': return "unsigned char";
        case 'i': return "int";
        case 'j': return "unsigned int";
        case 'l': return "long";
        case 'm': return "unsigned long";
        case 's': return "short";
        case 't': return "unsigned short";
        case 'v': return "void";
        case 'w': return "wchar_t";
        case 'x': return "long long";
        case 'y': return "unsigned long long";
    }
    return "";
}

std::string compS(int x)
{
    switch(x)
    {
        case 0:
        return "< ";
        case 1:
        return "==";
        case 2:
        return "> ";
        case 3:
        return "<=";
        case 4:
        return ">=";
    }
    return "";
}

template<typename T1, typename T2>
void compare()
{
    bool head = false;
    T1 lhsVals[] = {std::numeric_limits<T1>::lowest(), 0, std::numeric_limits<T1>::max(), 1, 10, (T1) -1, (T1) -10};
    T2 rhsVals[] = {std::numeric_limits<T2>::lowest(), 0, std::numeric_limits<T2>::max(), 1, 10, (T2) -1, (T2) -10};
    auto t1width = std::setw(std::max((std::string::size_type) std::numeric_limits<T1>::digits10 + 2, name<T1>().length()));
    auto t2width = std::setw(std::max((std::string::size_type) std::numeric_limits<T2>::digits10 + 2, name<T2>().length()));
    for(int i = std::is_unsigned<T1>::value; i < 7; i++)
      for(int j = std::is_unsigned<T2>::value; j < 7; j++)
        for(int k = 0; k < 5; k++)
        {
            bool out;
            bool comp;
            switch(k)
            {
                case 0:
                out = lhsVals[i] < rhsVals[j];
                comp = (long double) lhsVals[i] < (long double) rhsVals[j];
                break;
                case 1:
                out = lhsVals[i] == rhsVals[j];
                comp = (long double) lhsVals[i] == (long double) rhsVals[j];
                break;
                case 2:
                out = lhsVals[i] > rhsVals[j];
                comp = (long double) lhsVals[i] > (long double) rhsVals[j];
                break;
                case 3:
                out = lhsVals[i] <= rhsVals[j];
                comp = (long double) lhsVals[i] <= (long double) rhsVals[j];
                break;
                case 4:
                out = lhsVals[i] >= rhsVals[j];
                comp = (long double) lhsVals[i] >= (long double) rhsVals[j];
                break;
            }
            if(out != comp)
            {
                if(!head)
                {
                    std::cout << t1width << std::left << name<T1>() << "    " << t2width << name<T2>() << std::endl;
                    head = true;
                }
                /*std::cout 
                   << t1width << std::to_string(lhsVals[i])
                   << " " << compS(k) << " "
                   << t2width << std::to_string(rhsVals[j])
                   << ": " << std::setw(5) << std::boolalpha << out
                   << ": " << std::setw(5) << std::boolalpha << comp <<  std::endl;*/
            }
        }
    if(head)
      std::endl(std::cout);
}

template<typename T1, typename T2>
constexpr bool lessThan(T1 lhs, T2 rhs)
{
    if(!std::is_integral<T1>::value || !std::is_integral<T1>::value
      || std::is_unsigned<T1>::value == std::is_unsigned<T2>::value)
        return lhs < rhs;
    
    if(std::is_signed<T1>::value)
    {
        if( lhs < T1(0))
            return true;
        if((unsigned intmax_t) std::numeric_limits<T1>::max <= (unsigned intmax_t) std::numeric_limits<T2>::max)
           return (T2) lhs < rhs;
        
        return lhs < (T1) rhs;
    
    if(std::is_signed<T2>::value && lhs < T2(0))
        return false;
    
    }
    
}
        


int main()
{
compare<unsigned long long,unsigned long>();
compare<unsigned long long,unsigned int>();
compare<unsigned long long,char32_t>();
compare<unsigned long long,unsigned short>();
compare<unsigned long long,char16_t>();
compare<unsigned long long,unsigned char>();
compare<unsigned long long,bool>();
compare<unsigned long long,long long>();
compare<unsigned long long,long>();
compare<unsigned long long,int>();
compare<unsigned long long,wchar_t>();
compare<unsigned long long,short>();
compare<unsigned long long,signed char>();
compare<unsigned long long,char>();
compare<unsigned long,unsigned int>();
compare<unsigned long,char32_t>();
compare<unsigned long,unsigned short>();
compare<unsigned long,char16_t>();
compare<unsigned long,unsigned char>();
compare<unsigned long,bool>();
compare<unsigned long,long long>();
compare<unsigned long,long>();
compare<unsigned long,int>();
compare<unsigned long,wchar_t>();
compare<unsigned long,short>();
compare<unsigned long,signed char>();
compare<unsigned long,char>();
compare<unsigned int,char32_t>();
compare<unsigned int,unsigned short>();
compare<unsigned int,char16_t>();
compare<unsigned int,unsigned char>();
compare<unsigned int,bool>();
compare<unsigned int,long long>();
compare<unsigned int,long>();
compare<unsigned int,int>();
compare<unsigned int,wchar_t>();
compare<unsigned int,short>();
compare<unsigned int,signed char>();
compare<unsigned int,char>();
compare<char32_t,unsigned short>();
compare<char32_t,char16_t>();
compare<char32_t,unsigned char>();
compare<char32_t,bool>();
compare<char32_t,long long>();
compare<char32_t,long>();
compare<char32_t,int>();
compare<char32_t,wchar_t>();
compare<char32_t,short>();
compare<char32_t,signed char>();
compare<char32_t,char>();
compare<unsigned short,char16_t>();
compare<unsigned short,unsigned char>();
compare<unsigned short,bool>();
compare<unsigned short,long long>();
compare<unsigned short,long>();
compare<unsigned short,int>();
compare<unsigned short,wchar_t>();
compare<unsigned short,short>();
compare<unsigned short,signed char>();
compare<unsigned short,char>();
compare<char16_t,unsigned char>();
compare<char16_t,bool>();
compare<char16_t,long long>();
compare<char16_t,long>();
compare<char16_t,int>();
compare<char16_t,wchar_t>();
compare<char16_t,short>();
compare<char16_t,signed char>();
compare<char16_t,char>();
compare<unsigned char,bool>();
compare<unsigned char,long long>();
compare<unsigned char,long>();
compare<unsigned char,int>();
compare<unsigned char,wchar_t>();
compare<unsigned char,short>();
compare<unsigned char,signed char>();
compare<unsigned char,char>();
compare<bool,long long>();
compare<bool,long>();
compare<bool,int>();
compare<bool,wchar_t>();
compare<bool,short>();
compare<bool,signed char>();
compare<bool,char>();
compare<long long,long>();
compare<long long,int>();
compare<long long,wchar_t>();
compare<long long,short>();
compare<long long,signed char>();
compare<long long,char>();
compare<long,int>();
compare<long,wchar_t>();
compare<long,short>();
compare<long,signed char>();
compare<long,char>();
compare<int,wchar_t>();
compare<int,short>();
compare<int,signed char>();
compare<int,char>();
compare<wchar_t,short>();
compare<wchar_t,signed char>();
compare<wchar_t,char>();
compare<short,signed char>();
compare<short,char>();
compare<signed char,char>();
}
