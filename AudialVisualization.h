/**
 * AudialVisualization.h declares a class that can be inherited from
 * to wrap TSGL and TSAL programs.
 *
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 *
 */

#pragma once

#include <tsgl.h>
#include <tsal.hpp>
#include <cxxopts.hpp>
#include <omp.h>
#include <iostream>
#include <memory>
#include <string>

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
  int num_algorithms_to_run;
  std::vector<std::string> sorting_algorithms;
  Mixer *mixer = nullptr;
  Canvas *canvas = nullptr;
  std::vector<ThreadSynth> voices;
  int data_amount;

public:
  AudialVisualization(int argc, char **argv);
  virtual Canvas *createCanvas(std::string canvas_name);
  virtual Mixer *createMixer();
  void setVisualization(const bool b);
  void setAudialization(const bool b);
  void setNumThreads(const int n);
  void setCanvasHeight(const int h);
  void setCanvasWidth(const int w);
  void setSortingAlgorithm(const std::vector<std::string>& a);
  void setDataAmount(const int a);
  bool showVisualization() const;
  bool playAudialization() const;
  int getCanvasHeight() const;
  int getCanvasWidth() const;
  int getDataAmount() const;
  int getNumThreads() const;
  std::vector<std::string> getSortingAlgorithms() const;
  ~AudialVisualization();
};


}