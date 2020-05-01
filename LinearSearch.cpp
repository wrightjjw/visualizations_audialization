/**
 * LinearSearch.cpp defines the methods and algorithm required to make the
 * audial/visualizaiton for a linear search
 *
 * Who: Nate Herder
 * When: 04/23/2020
 * Where: Calvin University
 *
 */

#include "LinearSearch.h"
#include <cmath>

namespace avlib {

  LinearSearch::LinearSearch(int argc, char **argv) : AudialVisualization(argc, argv) {

  }

  void LinearSearch::makeSearch(Canvas *can, std::vector<ThreadSynth> &voices, int data_elements) {

    int cwh = getCanvasHeight();  // canvas window height
    ColorFloat color = RED;
    ColorFloat bg = BLACK;
    ColorFloat sort_done_color = WHITE;

    int block_size;
    int number_normal_block_size;
    if( (getCanvasWidth() % getDataAmount()) == 0 ) {
      block_size = (getCanvasWidth()/getDataAmount());
      number_normal_block_size = getDataAmount();
    } else {
      block_size = floor( (getCanvasWidth()/getDataAmount()) );
      number_normal_block_size = (getDataAmount() - (getCanvasWidth() % getDataAmount()));
    }
    int block_size_plus_one = block_size + 1;
    if (showVisualization()) {
      can->start();
    }

    // generate the data to sort
    int *numbers = new int[data_elements];  // Array to store the data
    for (int i = 0; i < data_elements; i++) {
      numbers[i] = rand() % getCanvasHeight();
    }

    // draw the original random data
    if (showVisualization()) {
    for (int i = 0; i < data_elements; i++) {
      if( i < number_normal_block_size ) {
        can->drawRectangle((i*block_size), (cwh-numbers[i]), block_size, numbers[i], color);
      } else {
        can->drawRectangle(((number_normal_block_size*block_size)+(((i-number_normal_block_size)*block_size_plus_one)) ), (cwh-numbers[i]), block_size_plus_one, numbers[i], color);
      }
    }
    }

  }

  void LinearSearch::run() {

    if (showVisualization()) {
      createCanvas("Linear Search");
      canvas->setBackgroundColor(BLACK);
    }

    if (playAudialization()) {
      createMixer();

      voices = std::vector<ThreadSynth>(1, ThreadSynth(mixer));
      mixer->add(voices[0]);
      //voices[0].setVolume(0.5);
      voices[0].setEnvelopeActive(false);
    }

    if (showVisualization() || playAudialization()) {
      makeSearch(canvas, voices, getDataAmount());
    } else {
      std::cout << "neither -v or -a flags set" << std::endl;
      std::exit(0);
    }

  }

}