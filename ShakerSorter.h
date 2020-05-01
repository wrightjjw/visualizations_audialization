/**
 * ShakerSorter.h declares declares, overrides, and implements the algorithm
 * necessary to implement a shaker sort audialization and visualization. It
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

class ShakerSorter : public SortingAudialVisualization {
 public:
  ShakerSorter(int argc, char **argv, bool value = false);
  void run();
  void ShakerSort(Canvas *can, std::vector<ThreadSynth> &voices, int data_elements);
};

}