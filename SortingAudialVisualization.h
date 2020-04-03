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

#ifndef SortingAudialVisualization_H
#define SortingAudialVisualization_H

#include <string.h>
#include "AudialVisualization.h"
#include "tsgl.h"

using namespace tsgl;
using namespace tsal;

namespace avlib {

class SortingAudialVisualization : public AudialVisualization {
 public:
  SortingAudialVisualization(int argc, char** argv);
  Canvas* createCanvas();
  Mixer* createMixer();
  // maybe think about making getter for the canvas and thread synth vector
  ~SortingAudialVisualization();
};

}

#endif