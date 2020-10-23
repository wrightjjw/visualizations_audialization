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
// #include "BubbleSorter.h"
// #include "InsertionSorter.h"
#include "MergeSorter.h"
// #include "SelectionSorter.h"
// #include "ShakerSorter.h"
#include <cmath>

namespace avlib {

SortingAudialVisualization::SortingAudialVisualization(int argc, char** argv, bool value) : AudialVisualization(argc, argv), main_thread{value} {
  if( (getCanvasWidth() % getDataAmount()) == 0 ) {
    setEvenDataChunks(true);
    setBlockSize( (getCanvasWidth()/getDataAmount()) );
    setNumberNormalBlockSize( getDataAmount() );
  } else {
    setEvenDataChunks(false);
    setBlockSize( floor( (getCanvasWidth()/getDataAmount()) ) );
    setNumberNormalBlockSize( (getDataAmount() - (getCanvasWidth() % getDataAmount())) );
  }

  std::vector<std::string> sort_run_vector = getSortingAlgorithms();

  if( getMainThread() == true ) {
    // #pragma omp parallel num_threads( sort_run_vector.size() )
    {
      int tid = omp_get_thread_num();
      
      // if(sort_run_vector.at(tid) == "bubble") {
      //   BubbleSorter b(argc, argv);
      //   b.run();
      // } else if(sort_run_vector.at(tid) == "insertion") {
      //   InsertionSorter i(argc, argv);
      //   i.run();
      // } else 
      if(sort_run_vector.at(tid) == "merge") {
        MergeSorter m(argc, argv);
        m.run();
      // } else if(sort_run_vector.at(tid) == "selection") {
      //   SelectionSorter s(argc, argv);
      //   s.run();
      // } else if(sort_run_vector.at(tid) == "shaker") {
      //   ShakerSorter sh(argc, argv);
      //   sh.run();
      }
    }
  }


}

Canvas* SortingAudialVisualization::createCanvas(std::string canvas_name) {
  setCanvasWidth(getCanvasWidth() );
  setCanvasHeight((getCanvasWidth() / 2));
  canvas = new Canvas(0, 0, getCanvasWidth(), (getCanvasWidth() / 2), canvas_name);
  return canvas;
}

Mixer* SortingAudialVisualization::createMixer() {
  mixer = new Mixer();
  return mixer;
}

void SortingAudialVisualization::setEvenDataChunks(const int v) {
  even_data_chunks = v;
}

bool SortingAudialVisualization::getEvenDataChunks() const {
  return even_data_chunks;
}

void SortingAudialVisualization::setBlockSize(const int bs) {
  block_size = bs;
}

int SortingAudialVisualization::getBlockSize() const {
  return block_size;
}

void SortingAudialVisualization::setNumberNormalBlockSize(const int n) {
  number_normal_block_size = n;
}

int SortingAudialVisualization::getNumberNormalBlockSize() const {
  return number_normal_block_size;
}

bool SortingAudialVisualization::getMainThread() {
  return main_thread;
}


SortingAudialVisualization::~SortingAudialVisualization() {
  delete canvas;
  delete mixer;
}

}