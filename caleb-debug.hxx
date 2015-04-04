#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>
#include <iostream>

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
// http://stackoverflow.com/a/18369732
// http://stackoverflow.com/a/20170989


//wiki/ANSI_escape_code#graphics
//er("help!"); 
void er(const char* n){
    std::cerr << "\033[1;31m" << n << "\033[0m\n";
} //http://stackoverflow.com/a/2616912

//eb("help!"); 
void eb(const char* n){
    std::cerr << "\033[1;7;31;5m" << n << "\033[0m\n";
} //http://stackoverflow.com/a/2616912

//et("help!"); 
void et(const char* n){
    std::cerr << "\033[1;7;5m" << n << "\033[0m\n";
} //http://stackoverflow.com/a/2616912


template<typename T>
void ftype(T&& parameter)
{
    std::cout << type_name<decltype(parameter)>();
}
