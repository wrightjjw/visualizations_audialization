/**
 * SortingAudialVisualizations.cpp holds defines the common methods and data
 * across all sorting algorithms.
 *
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 *
 */

#include "SortingAudialVisualization.h"

namespace avlib {

SortingAudialVisualization::SortingAudialVisualization(int argc, char** argv) : AudialVisualization(argc, argv) {

}

Canvas* SortingAudialVisualization::createCanvas() {
  // for sorting algorithms make the canvas = width / 2
  setCanvasWidth(getCanvasWidth() + MARGIN);
  setCanvasHeight((getCanvasWidth() / 2) + MARGIN);
  canvas = new Canvas(0, 0, getCanvasWidth(), (getCanvasWidth() / 2), "Canvas");  // this could be bad.. because someone could
                                  // make multiple maybe make singleton?
  return canvas;
}

Mixer* SortingAudialVisualization::createMixer() {
  mixer = new Mixer();  // this could be bad.. because someone could make
                        // multiple maybe make singleton?
  return mixer;
}

SortingAudialVisualization::~SortingAudialVisualization() {
  delete canvas;
  delete mixer;
}

}