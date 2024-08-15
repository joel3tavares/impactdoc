#ifndef ARGS_H
#define ARGS_H

#include <string>
#include <set>

struct Args {
    private:
        std::string fileName;
        std::set<int> lines;

    public:
        Args(int argc,char *argv[]);
        std::string getFileName() const;
        std::set<int> getLines() const;
};

#endif