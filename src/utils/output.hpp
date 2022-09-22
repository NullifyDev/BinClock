#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>

template <typename T>
void outputln(T t) { std::cout << t << std::endl; }
inline void clear() { std::system("clear"); }

#endif