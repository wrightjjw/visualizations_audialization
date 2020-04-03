/**
 * BubbleSorter.h declares declares, overrides, and implements the algorithm
 * necessary to implement a bubble sort audialization and visualization. It
 * inherits from SortingAudialVisualizations.h
 *
 * Who: Nate Herder
 * When: 02/27/2020
 * Where: Calvin University
 *
 */

#ifndef BubbleSorter_H
#define BubbleSorter_H

#include "SortingAudialVisualization.h"

namespace avlib {

class BubbleSorter : public SortingAudialVisualization {
 public:
  BubbleSorter(int argc, char **argv);
  void run();
  void BubbleSort(Canvas *can, std::vector<ThreadSynth> &voices, int size);
};

}

#endif