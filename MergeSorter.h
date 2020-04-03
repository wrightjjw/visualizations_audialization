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

#ifndef MergeSorter_H
#define MergeSorter_H

#include "SortingAudialVisualization.h"

namespace avlib {

class MergeSorter : public SortingAudialVisualization {
 public:
  MergeSorter(int argc, char **argv);
  // void avMergeSort(Canvas& can, std::vector<ThreadSynth>& voices, int threads, int size); 
  // void vMergeSort(Canvas& can, int threads, int size);
  // void aMergeSort(std::vector<ThreadSynth>& voices, int threads, int size);
  void MergeSort(Canvas *can, std::vector<ThreadSynth> &voices, int threads, int size);
  void run();
};

}

#endif