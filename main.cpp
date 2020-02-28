/**
 * main.cpp is the driver
 * 
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 * 
 */

#include "MergeSorter.h"
#include "BubbleSorter.h"
#include "InsertionSorter.h"


using namespace avlib;

int main(int argc, char **argv) {

    // MergeSorter m(argc, argv);
    // m.run();

    // BubbleSorter b(argc, argv);
    // b.run();

    InsertionSorter i(argc, argv);
    i.run();

    return 0;
}