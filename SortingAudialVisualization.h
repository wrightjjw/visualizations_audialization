/**
 * SortingAudialVisualization.h declares the class that all audial
 * visualizations will inherit from containing all methods, command line
 * preferences, and other data that is common across all sorting algorithms.
 *
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 *
 */

#pragma once

#include <string>
#include "AudialVisualization.h"
#include "tsgl.h"

using namespace tsgl;
using namespace tsal;

namespace avlib {

class SortingAudialVisualization : public AudialVisualization {
private:
  bool even_data_chunks;
  bool main_thread;
  int block_size;
  int number_normal_block_size;

public:
  SortingAudialVisualization(int argc, char** argv, bool value = true);
  Canvas* createCanvas(std::string canvas_name);
  Mixer* createMixer();
  void setEvenDataChunks(const int v);
  bool getEvenDataChunks() const;
  void setBlockSize(const int bs);
  int getBlockSize() const;
  void setNumberNormalBlockSize(const int n);
  int getNumberNormalBlockSize() const;
  bool getMainThread();
  ~SortingAudialVisualization();
};

}