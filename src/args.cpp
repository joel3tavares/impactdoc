#include "args.h"

#include <stdexcept>

Args::Args(int argc,char *argv[])
{
    if (argc < 3) {
        throw std::invalid_argument("impactdoc 0.1\nUsage: impactdoc <filename.php> <ModifiedLinesSeparatedBySpaces>\n");
    }

    fileName = std::string(argv[1]);

    if (!fileName.ends_with(".php")) {
        throw std::invalid_argument("Error: Invalid file extension. Please ensure the file has a valid extension (e.g., .php) and try again.\n");
    }

    for (int i = 2; i < argc; i++) {
        lines.insert(atoi(argv[i]));
    }
}

std::string Args::getFileName() const
{
    return fileName;
}

std::set<int> Args::getLines() const
{
    return lines;
}
