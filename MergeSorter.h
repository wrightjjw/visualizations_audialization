/**
 * MergeSorter.h declares declares, overrides, and implements the algorithm
 * necessary to implement a merge sort audialization and visualization. It
 * inherits from SortingAudialVisualizations.h
 *
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 *
 */

#pragma once

#include "SortingAudialVisualization.h"

namespace avlib {

class MergeSorter : public SortingAudialVisualization {
 public:
  MergeSorter(int argc, char **argv, bool value = false);
  void MergeSort(Canvas *can, std::vector<ThreadSynth> &voices, int threads, int size);
  void run();
};

}