//g++  5.4.0

#include <iostream>
#include <memory>
#include <type_traits>



template<typename T>
class Nullable
{
    public:
    Nullable<T>& operator=(std::nullptr_t n)
    {
        this->reset();
        return *this;
    }
    Nullable<T>& operator=(T n)
    {
        this->element = n;
        return *this;
    }
    bool hasValue()
    {
        return value;
    }
    
    T& getValueOrDefault(T& def)
    {
        return (value ? element : def);
    }
    
    T& getValueOrDefault()
    {
        return element;
    }
    
    explicit operator T&()
    {
        return element;
    }
    
    operator bool()
    {
        return value;
    }
    
    T& operator*()
    {
        return element;
    }
    
    void reset()
    {
        element = {};
        value = false;
    }
    
    private:
    T element;
    bool value = false;
    
};

template



template<typename T>
T& coalesce(T& a, T& b)
{
    return (!std::is_convertible<std::nullptr_t,T>::value || a
            ? a : b);
}

int main()
{
    int a = 6;
    int b = 6;
    Nullable<int> n;
    n = a;
    n.reset();
    std::shared_ptr<int> testa; // std::make_shared<int>(a);
    std::shared_ptr<int> testb = std::make_shared<int>(b);
    std::cout << (int) n;
}
