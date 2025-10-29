#ifndef UTILS_H
#define UTILS_H

inline void clearTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
#endif // UTILS_H