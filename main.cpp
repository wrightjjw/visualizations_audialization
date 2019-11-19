/**
 * main.cpp is the driver
 * 
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 * 
 */

#include "MergeSorter.h"


using namespace tsgl;
using namespace tsal;

int main(int argc, char **argv) {

    MergeSorter m(argc, argv);

    m.run();

    return 0;
}