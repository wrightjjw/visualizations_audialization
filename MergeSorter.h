/**
 * MergeSort.h declares declares, overrides, and implements the algorithm necessary to implement a merge
 * sort audialization and visualization. It inherits from SortingAudialVisualizations.h
 * 
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 * 
 */

#ifndef MergeSort_H
#define MergeSort_H

#include "SortingAudialVisualizations.h"


class MergeSorter : public SortingAudialVisualization {

    public:
        enum MergeState {
            S_MERGE = 1,
            S_SHIFT = 2,
            S_WAIT = 3,
            S_DONE = 4,
            S_HIDE = 5
        };

        MergeSorter( int argc, char **argv );
        void run();
};

#endif