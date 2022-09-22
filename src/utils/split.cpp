#include "split.hpp"

#include <cstring>

std::vector<char*> SplitStr(const char *str, const char *delim) {
    std::vector<char*> arr;
    char *tok = strtok(strdup(str), delim);
    while (tok != NULL) {
        arr.push_back(tok);
        tok = strtok(NULL, delim);
    }
    return arr;
}
