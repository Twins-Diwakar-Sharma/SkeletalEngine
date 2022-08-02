#ifndef H_DE_KEEDA_H
#define H_DE_KEEDA_H

#include <istream>

#define KEEDA_LOG 1 

#if KEEDA_LOG == 1
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x) 
#endif

#endif