#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>
#include <iostream>

// http://stackoverflow.com/a/18369732
// http://stackoverflow.com/a/20170989
template <class T>
std::string
type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
           (
#ifndef _MSC_VER
                abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                           nullptr, nullptr),
#else
                nullptr,
#endif
                std::free
           );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
} 



//wiki/ANSI_escape_code#graphics
//http://stackoverflow.com/a/14175929
//http://stackoverflow.com/a/2616912

template<typename T>
void er(T i){
    std::cerr << "\033[1;31m" << i << "\033[0m\n";
} 

template<typename T>
void eb(T i){
    std::cerr << "\033[1;7;31;5m" << i << "\033[0m\n";
}

template<typename T>
void et(T i){
    std::cerr << "\033[1;7;5m" << i << "\033[0m\n";
}

template<typename T>
void ftype(T&& i){
    std::cout << "\033[1;33m" << type_name<decltype(i)>() << "\033[0m\n";
}

template<typename T>
void ftype(T&& i, T&& j){
    std::cout << "\033[1;33m" << type_name<decltype(i)>() << "\033[0m" 
              << " :: " << "\033[1;7;33m" << j << "\033[0m\n";
}