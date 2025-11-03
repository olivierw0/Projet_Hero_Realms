#ifndef CONSOLE_COLORS_H
#define CONSOLE_COLORS_H

#include <string>

namespace ConsoleColors {
    // Codes de couleur ANSI
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";

    // Fonction utilitaire pour colorer le texte
    inline std::string colorize(const std::string& text, const std::string& color) {
        return color + text + RESET;
    }

    inline std::string colorizeOr(const std::string& text) {
        return colorize(text, YELLOW);
    }

    inline std::string colorizeDamage(const std::string& text) {
        return colorize(text, RED);
    }

    inline std::string colorizeHeal(const std::string& text) {
        return colorize(text, GREEN);
    }

    inline std::string colorizeDraw(const std::string& text) {
        return colorize(text, BLUE);
    }

    inline std::string colorizeAction(const std::string& text) {
        return colorize(text, MAGENTA);
    }
}

#endif // CONSOLE_COLORS_H