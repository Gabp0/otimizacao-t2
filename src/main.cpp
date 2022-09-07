#include "cast.h"

int main(int argc, char const *argv[])
{
    Cast c;

    // c.toggleDefaultFunc();
    c.toggleOptimalityCut();
    c.toggleViabilityCut();

    c.branchAndBound();

    return 0;
}
