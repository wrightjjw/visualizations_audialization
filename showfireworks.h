/**
 * showfireworks.h spices up the TSGL exmaple by combining with TSAL to add sound to the fireworks.
 * It inherits from AudialVisualization.h
 *
 * Who: Nate Herder
 * When: 04/23/2020
 * Where: Calvin University
 *
 */

#pragma once

#include "AudialVisualization.h"

namespace avlib {

  class ShowFireworks : public AudialVisualization {
  public:
    ShowFireworks(int argc, char **argv);
    void fireWorkFunction(Canvas *can, std::vector<ThreadSynth> &voices, int threads, int numFireworks, int speed);
    void run();
  };

}