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

  void LinearSearch::makeSearch(Canvas *can, std::vector<ThreadSynth> &voices, int data_elements, int search) {
    int cwh = getCanvasHeight();  // canvas window height
    ColorFloat color = RED;
    ColorFloat bg = BLACK;
    ColorFloat sort_done_color = WHITE;
    if (showVisualization()) {
      can->start();
    }

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

    // generate the data to sort
    int *numbers = new int[data_elements];  // Array to store the data
    for (int i = 0; i < data_elements; i++) {
      numbers[i] = rand() % getCanvasHeight();
    }

    if(showVisualization()) {
      std::string display_text = "Searching for: " + std::to_string(search);
      can->drawText( display_text, 10, 20, 20, color );
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

    int result_location = NULL;
    bool search_found = false;
    //begin searching
    for(int i = 0; i < data_elements; i++) {
      if(numbers[i] == search) {
        result_location = i;
        search_found = true;
        break;

      }else {

        if (playAudialization()) {
          MidiNote note = Util::scaleToNote(numbers[i], std::make_pair(0, getCanvasHeight()), std::make_pair(C3, C7));
          voices.at(0).play(note, Timing::MICROSECOND, 50);
        }

        if(showVisualization()) {
          can->sleep();
          if( i < number_normal_block_size ) {
            can->drawRectangle( i*block_size, (cwh-numbers[i]), block_size, numbers[i], sort_done_color );
          } else {
            can->drawRectangle( ((number_normal_block_size*block_size)+(((i-number_normal_block_size)*block_size_plus_one)) ), (cwh-numbers[i]), block_size_plus_one, numbers[i], sort_done_color );
          }
        }
        
      }
    }
    if(search_found) {
      std::string display_text = "Found at index: " + std::to_string(result_location);
      can->drawText( display_text, 10, 45, 20, color );
    } else {
      std::string display_text = "No matches found";
      can->drawText( display_text, 10, 45, 20, color );
    }
    

    if(playAudialization()) {
      voices.at(0).stop();
    }

    if(showVisualization()) {
      can->wait();
    }

    delete[] numbers;
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
      voices[0].setEnvelopeActive(false);
    }

    int search = rand() % getCanvasHeight();

    if (showVisualization() || playAudialization()) {
      std::cout << "Searching for: " << search << std::endl;
      makeSearch(canvas, voices, getDataAmount(), search);
    } else {
      std::cout << "neither -v or -a flags set" << std::endl;
      std::exit(0);
    }

  }

}