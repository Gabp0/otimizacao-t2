#include "cast.h"

int main(int argc, char const *argv[])
{
    Cast c;

    c.toggleDefaultFunc();
    // c.toggleOptimalityCut();
    //  c.toggleViabilityCut();

    c.branchAndBound();

    c.showResults();

    return 0;
}
