#include "parser.h"
#include "report.h"

#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[])
{
    try {
        Args args(argc, argv);
        ImpactParser impactParser(args);
        ImpactContext context = impactParser.parse();
        Report::generate(args, context);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;

        return -1;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;

        return -2;
    } catch (...) {
        std::cerr << "Error: impactdoc failed." << std::endl;

        return -3;
    }

    return 0;
}