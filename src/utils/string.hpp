#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
#include <cstring>

// template <typename PrefixType>
inline bool StartsWith(std::string str, std::string substr) { 
    // return strncmp(str.c_str(), substr.c_str(), substr.size());
    if (strncmp(str.c_str(), substr.c_str(), substr.size()) == 0) { 
        return true; 
    } else { 
        return false; 
    } 
}

inline char atoc(int asciicode) {
    
}

#endif