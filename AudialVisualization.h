/**
 * AudialVisualization.h declares a class that can be inherited from
 * to wrap TSGL and TSAL programs.
 *
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 *
 */

#ifndef Audialisualization_H
#define AudialVisualization_H

#include <tsgl.h>
#include <tsal.hpp>
#include <cxxopts.hpp>
#include <omp.h>
#include <iostream>
#include <memory>

using namespace tsgl;
using namespace tsal;

namespace avlib {

class AudialVisualization {
protected:
  int num_threads;
  bool show_visualizaiton;
  bool play_audialization;
  int canvas_height;
  int canvas_width;
  std::string sound_file;
  Mixer *mixer = nullptr;
  Canvas *canvas = nullptr;
  std::vector<ThreadSynth> voices;
  const int MARGIN = 8;

public:
  AudialVisualization(int argc, char **argv);
  virtual Canvas *createCanvas();
  virtual Mixer *createMixer();
  void setVisualization(const bool b);
  void setAudialization(const bool b);
  void setNumThreads(const int n);
  void setCanvasHeight(const int h);
  void setCanvasWidth(const int w);
  bool showVisualization() const;
  bool playAudialization() const;
  int getNumThreads() const;
  int getCanvasHeight() const;
  int getCanvasWidth() const;
  ~AudialVisualization();
};

}

#endif