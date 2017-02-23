#ifndef _DEF_LOGGER_H_
#define _DEF_LOGGER_H_

#define DEBUG 1

#include <iostream>

#ifdef DEBUG
	#define LOG std::cout
#else
	#define LOG ;
#endif

#endif //_DEF_LOGGER_H_
