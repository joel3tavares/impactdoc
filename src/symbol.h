#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <vector>

struct Symbol {
    std::string name;
    int startLine;
    int endLine;

    std::vector<std::string> comments;

    Symbol(
        std::string name,
        int startLine,
        std::vector<std::string> comments
    ) : name(name), startLine(startLine), comments(comments) {};
};

inline bool operator<(const Symbol& l, const Symbol& r)
{
    return l.name < r.name;
}

#endif