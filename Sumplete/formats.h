#ifndef FORTMATS_H
#define FORTMATS_H

//Needed macros for the game.
#define MAX_NAME_SIZE 21
#define MAX_COMMAND_SIZE 11 

// Colors and formats for text.
#define ANSI_RESET            "\x1b[0m"
#define ANSI_BOLD             "\x1b[1m"
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"

//Macros for ease of use.
#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define CYAN(string)       ANSI_COLOR_CYAN       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET
#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_YELLOW(string)  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string)    ANSI_BG_COLOR_CYAN    string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET

//Usefull caracters for tables.
#define H_TAB_HOR "\u2501" // ━ (horizontal)
#define H_TAB_VER "\u2503" // ┃ (vertical)
#define H_TAB_TL  "\u250F" // ┏ (top-left)
#define H_TAB_ML  "\u2523" // ┣ (middle-left)
#define H_TAB_BL  "\u2517" // ┗ (bottom-left)
#define H_TAB_TJ  "\u2533" // ┳ (top-join)
#define H_TAB_MJ  "\u254B" // ╋ (middle-join)
#define H_TAB_BJ  "\u253B" // ┻ (bottom-join)
#define H_TAB_TR  "\u2513" // ┓ (top-right)
#define H_TAB_MR  "\u252B" // ┫ (middle-right)
#define H_TAB_BR  "\u251B" // ┛ (bottom-right)

#define TAB_HOR "\u2500" // ─ (horizontal)
#define TAB_VER "\u2502" // │ (vertical)
#define TAB_TL  "\u250C" // ┌ (top-left)
#define TAB_ML  "\u251C" // ├ (middle-left)
#define TAB_BL  "\u2514" // └ (bottom-left)
#define TAB_TJ  "\u252C" // ┬ (top-join)
#define TAB_MJ  "\u253C" // ┼ (middle-join)
#define TAB_BJ  "\u2534" // ┴ (bottom-join)
#define TAB_TR  "\u2510" // ┐ (top-right)
#define TAB_MR  "\u2524" // ┤ (middle-right)
#define TAB_BR  "\u2518" // ┘ (bottom-right)


//Error macros definition.
#define INVALID_OPTION_ERROR "OPÇÃO INVÁLIDA!"
#define INVALID_COMMAND_ERROR "COMANDO INVÁLIDO!"
#define INVALID_SIZE_ERROR "TAMANHO DE TABULEIRO INVÁLIDO!"
#define INVALID_DIFFICULT_ERROR "DIFICULDADE INVÁLIDA!"
#define BOARD_CREATION_FAIL "NÃO FOI POSSÍVEL CRIAR O TABULEIRO!"
#define INVALID_INDEXES_ERROR "INDICES INVÁLIDOS!"
#define INVALID_FILE_EXTENTION_ERROR "A EXTENÇÃO DO ARQUIVO DEVE SER .txt!"

//Prints-out the specified error message.
#define printError(error_name) printf(BOLD(RED("\n\t\t\t\t %s\n\n")), error_name)

//Success macros definition
#define FILE_SUCCESSFULLY_SAVED "ARQUIVO GRAVADO COM SUCESSO!"

//Prints-out the specified success message.
#define printSuccess(success_name) printf(BOLD(GREEN("\n\t\t\t\t %s\n\n")), success_name);

#endif //FORMATS_H