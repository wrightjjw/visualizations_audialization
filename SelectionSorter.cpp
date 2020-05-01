/**
 * SelectionSorter.cpp defines the methods and algorithm required to make the
 * audial/visualizaiton for selection sort
 *
 * Who: Nate Herder
 * When: 02/27/2020
 * Where: Calvin University
 *
 */

#include "SelectionSorter.h"

namespace avlib {


SelectionSorter::SelectionSorter(int argc, char **argv, bool value): SortingAudialVisualization(argc, argv, value) {

}

void SelectionSorter::SelectionSort(Canvas *can, std::vector<ThreadSynth> &voices, int data_elements) {
  int cwh = getCanvasHeight();  // canvas window height
  ColorFloat color = RED;
  ColorFloat bg = BLACK;
  ColorFloat sort_done_color = WHITE;

  int block_size = getBlockSize();
  int number_normal_block_size = getNumberNormalBlockSize();
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

  // begin sorting
  int min;
  int temp;
  for (int i = 0; i < data_elements; i++) {
    min = i; 
    for (int j = i; j < data_elements; j++) {
      min = numbers[j] < numbers[min] ? j : min;
    }
    
    if(showVisualization()) {
      can->sleep();  // recommended to sleep before drawing
      if(min < number_normal_block_size) { //this isnt going to work well work well for odd data elemtns that don't divide evenly
        can->drawRectangle( (i*block_size), 0, block_size, cwh, bg );
        can->drawRectangle( (min*block_size), 0, block_size, cwh, bg  );
      } else {
        // can->drawRectangle(  );
        // can->drawRectangle(  );
      }
    }

    temp = numbers[i];
    numbers[i] = numbers[min];
    numbers[min] = temp;

    if (playAudialization()) {
      MidiNote note = Util::scaleToNote(numbers[min], std::make_pair(0, getCanvasHeight()), std::make_pair(C3, C7));
      voices.at(0).play(note, Timing::MICROSECOND, 30);
    }

    if (showVisualization()) {
      if(min < number_normal_block_size) {
        can->drawRectangle((i*block_size), (cwh-numbers[i]), block_size, numbers[i], color);
        can->drawRectangle((min*block_size), (cwh-numbers[min]), block_size, numbers[min], color);
      } else {
        //can->drawRectangle(((number_normal_block_size*block_size)+(((j)-number_normal_block_size)*block_size_plus_one)), (cwh-numbers[j]), block_size_plus_one, numbers[j], color );
        //can->drawRectangle(((number_normal_block_size*block_size)+(((j-1)-number_normal_block_size)*block_size_plus_one)), (cwh-numbers[j-1]), block_size_plus_one, numbers[j-1], color);
      }
    }

  }

  if(playAudialization()) {
    voices.at(0).stop();
  }

  //after sorting turn data white
  if( showVisualization()) {
    for (int i = 0; i < data_elements; i++) {
      if(i < number_normal_block_size) {
        can->drawRectangle((i*block_size), (cwh-numbers[i]), block_size, numbers[i], sort_done_color);
      } else {
        //can->drawRectangle(((number_normal_block_size*block_size)+((i-number_normal_block_size)*block_size_plus_one)), (cwh-numbers[i]), block_size_plus_one, numbers[i], sort_done_color);
      }
    }
  
    can->wait();
  }

  delete[] numbers;

}

void SelectionSorter::run() {

  if (showVisualization()) {
    createCanvas("Selection Sort");
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
    SelectionSort(canvas, voices, getDataAmount());
  } else {
    std::cout << "neither -v or -a flags set" << std::endl;
    std::exit(0);
  }

}


}