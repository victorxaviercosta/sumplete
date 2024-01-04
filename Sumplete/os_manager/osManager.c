#include "osManager.h"


#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    void clear(){
        system("clear");
    }

    void splash(char* string){
        printf(BOLD(BLUE("\t\t\e[5m%s\e[25m")), string);
    }
#endif

#if defined(_WIN32) || defined(_WIN64)
    void clear(){
        system("cls");
    }

    void splash(char* string){
        printf(BOLD(BLUE("%s")), string);
    }
#endif