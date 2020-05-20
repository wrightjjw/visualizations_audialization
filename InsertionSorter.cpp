/**
 * InsertionSorter.cpp defines the methods and algorithm required to make the
 * audial/visualizaiton for insertion sort
 *
 * Who: Nate Herder
 * When: 02/27/2020
 * Where: Calvin University
 *
 */

#include "InsertionSorter.h"

namespace avlib {

InsertionSorter::InsertionSorter(int argc, char** argv, bool value) : SortingAudialVisualization(argc, argv, value) {

}


void InsertionSorter::InsertionSort(Canvas* can, std::vector<ThreadSynth>& voices, int data_elements) {
  int cwh = getCanvasHeight();
  ColorFloat color = RED;
  ColorFloat bg = BLACK;
  ColorFloat sort_done_color = WHITE;
  
  int block_size = getBlockSize();
  int number_normal_block_size = getNumberNormalBlockSize();
  int block_size_plus_one = block_size + 1;
  if (showVisualization()) {
    can->start();
  }

  // Generate data
  int* numbers = new int[data_elements];
  for (int i = 0; i < data_elements; i++) {
    numbers[i] = rand() % (getCanvasHeight());
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

  int insertValue;
  int j;
  int temp;
  // begin sorting
  for (int i = 1; i < data_elements; i++) {
    insertValue = numbers[i];
    j = i;
    while (j > 0 && numbers[j - 1] > insertValue) {

      if(showVisualization()) {
        if(j < number_normal_block_size) {
          can->drawRectangle( (j*block_size), 0, block_size, cwh, bg );
          can->drawRectangle( ((j-1)*block_size), 0, block_size, cwh, bg );
        } else {
          can->drawRectangle( ((j*number_normal_block_size)+((j-number_normal_block_size)*block_size_plus_one)), 0, block_size_plus_one, cwh, bg);
          can->drawRectangle( (((j-1)*number_normal_block_size)+((j-1)-number_normal_block_size)*block_size_plus_one), 0, block_size_plus_one, cwh, bg);
        }
      }

      if (playAudialization()) {
        MidiNote note = Util::scaleToNote(numbers[j], std::make_pair(0, getCanvasHeight()), std::make_pair(C3, C7));
        voices.at(0).play(note, Timing::MILLISECOND, 30);
      }

      numbers[j] = numbers[j - 1];
      if (showVisualization()) {
        can->sleep();
        if(j < number_normal_block_size) {
          can->drawRectangle( (j*block_size), (cwh-numbers[j]), block_size, numbers[j], color );
          can->drawRectangle( ((j-1)*block_size), (cwh-insertValue), block_size, insertValue, color );
        } else {
          can->drawRectangle( ((j*number_normal_block_size)+((j-number_normal_block_size)*block_size_plus_one)), (cwh-numbers[j]), block_size_plus_one, numbers[j], color );
          can->drawRectangle( (((j-1)*number_normal_block_size)+((j-1)-number_normal_block_size)*block_size_plus_one), (cwh-numbers[j-1]), block_size_plus_one, numbers[j-1], color );
        }
      }
      j--;
    }
    numbers[j] = insertValue;
  }

  //make sure that the ThreadSynth stops playing
  if(playAudialization()) {
    voices.at(0).stop();
  }

  // after sorting turn data white
  if (showVisualization()) {
    for (int i = 0; i < data_elements; i++) {
      if( i < number_normal_block_size ) {
        can->drawRectangle((i*block_size), (cwh-numbers[i]), block_size, numbers[i], sort_done_color);
      } else {
        can->drawRectangle(((number_normal_block_size*block_size)+(((i-number_normal_block_size)*block_size_plus_one)) ), (cwh-numbers[i]), block_size_plus_one, numbers[i], sort_done_color);
      }
    }

    can->wait();
  }

  delete[] numbers;
}


void InsertionSorter::run() {
  if (showVisualization()) {
    createCanvas("Insertion Sort");
  }
  if (playAudialization()) {
    createMixer();
  }

  if (playAudialization()) {
    voices = std::vector<ThreadSynth>(1, ThreadSynth(mixer));
    mixer->add(voices[0]);
    voices[0].setEnvelopeActive(false);
  }

  if (showVisualization()) {
    canvas->setBackgroundColor(BLACK);
  }

  if (showVisualization() || playAudialization()) {
    InsertionSort(canvas, voices, getDataAmount());
  } else {
    std::cout << "neither -v or -a flags set" << std::endl;
    std::exit(0);
  }

}


}