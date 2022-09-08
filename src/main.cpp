#include "cast.h"
#include <algorithm>

using namespace std;

bool argExists(int argc, char **argv, const string &option)
{
    return find(argv, argc + argv, option) != (argv + argc);
}

int main(int argc, char *argv[])
{
    Cast c;

    if (argExists(argc, argv, "-f"))
        c.toggleViabilityCut();

    if (argExists(argc, argv, "-o"))
        c.toggleOptimalityCut();

    if (argExists(argc, argv, "-a"))
        c.toggleDefaultFunc();

    c.branchAndBound();
    c.showResults();

    return 0;
}
