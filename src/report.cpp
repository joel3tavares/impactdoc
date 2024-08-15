#include "report.h"

#include <iostream>

void Report::generate(const Args &args, const ImpactContext &context)
{
    if (context.modifiedSymbols.empty()) {
        std::cout << "No impact information is available for parsing in the file: " << args.getFileName() << std::endl;

        return;
    }

    for (auto symbol : context.modifiedSymbols) {
        if (symbol.comments.empty()) {
            std::cout << "No impact information is available for: " << symbol.name << std::endl;

            continue;
        }

        std::cout << "========================================" << std::endl;
        std::cout << symbol.name << std::endl;
        std::cout << "========================================" << std::endl;   

        for (auto comment : symbol.comments) {
            std::cout << "=> " << comment << std::endl;
        }

        std::cout << std::endl;
    }
}