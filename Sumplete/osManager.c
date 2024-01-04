#include "osManager.h"


#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    void clear(){
        system("clear");
    }
#endif

#if defined(_WIN32) || defined(_WIN64)
    void clear(){
        system("cls");
    }
#endif