/**
 * MergeSort.h declares declares, overrides, and implements the algorithm necessary to implement a merge
 * sort audialization and visualization. It inherits from SortingAudialVisualizations.h
 * 
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 * 
 */

#ifndef MergeSorter_H
#define MergeSorter_H

#include "SortingAudialVisualization.h"


namespace avlib {

class MergeSorter : public SortingAudialVisualization {

private:
    std::vector<ThreadSynth> voices;

public:
    MergeSorter( int argc, char **argv );
    void run();
};

}

#endif