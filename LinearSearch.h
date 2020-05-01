/**
 * linearSearch.h declares declares, overrides, and implements the algorithm
 * necessary to implement a linear search audialization and visualization. It
 * inherits from AudialVisualization.h
 *
 * Who: Nate Herder
 * When: 04/23/2020
 * Where: Calvin University
 *
 */

#pragma once

#include "AudialVisualization.h"

namespace avlib {

  class LinearSearch : public AudialVisualization {
  public:
    LinearSearch(int argc, char **argv);
    void makeSearch(Canvas *can, std::vector<ThreadSynth> &voices, int data_elements);
    void run();
  };

}