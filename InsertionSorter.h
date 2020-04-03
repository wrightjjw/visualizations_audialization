/**
 * InsertionSorter.h declares declares, overrides, and implements the algorithm
 * necessary to implement a insertion sort audialization and visualization. It
 * inherits from SortingAudialVisualizations.h
 *
 * Who: Nate Herder
 * When: 02/27/2020
 * Where: Calvin University
 *
 */

#ifndef InsertionSorter_H
#define InsertionSorter_H

#include "SortingAudialVisualization.h"

namespace avlib {

class InsertionSorter : public SortingAudialVisualization {
 public:
  InsertionSorter(int argc, char **argv);
  void InsertionSort(Canvas *can, std::vector<ThreadSynth> &voices, int size);
  void run();
};

}

#endif