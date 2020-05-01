/**
 * SelectionSorter.h declares declares, overrides, and implements the algorithm
 * necessary to implement a selection sort audialization and visualization. It
 * inherits from SortingAudialVisualizations.h
 *
 * Who: Nate Herder
 * When: 04/08/2020
 * Where: Calvin University
 *
 */

#pragma once

#include "SortingAudialVisualization.h"

namespace avlib {

class SelectionSorter : public SortingAudialVisualization {
 public:
  SelectionSorter(int argc, char **argv, bool value = false);
  void run();
  void SelectionSort(Canvas *can, std::vector<ThreadSynth> &voices, int data_elements);
};

}