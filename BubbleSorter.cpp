/**
 * BubbleSorter.cpp defines the methods and algorithm required to make the
 * audial/visualizaiton for bubble sort
 *
 * Who: Nate Herder
 * When: 02/27/2020
 * Where: Calvin University
 *
 */

#include "BubbleSorter.h"

namespace avlib {

BubbleSorter::BubbleSorter(int argc, char **argv, bool value) : SortingAudialVisualization(argc, argv, value) {

}


void BubbleSorter::BubbleSort(Canvas *can, std::vector<ThreadSynth> &voices, int data_elements) {
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
        Rectangle rec((i*block_size + block_size) / 2, cwh/2, 0, (block_size - i*block_size), 2*numbers[i] - cwh, 0, 0, 0, color);
        can->add(&rec)
        // can->drawRectangle((i*block_size), (cwh-numbers[i]), block_size, numbers[i], color);
      } else {
        can->drawRectangle(((number_normal_block_size*block_size)+(((i-number_normal_block_size)*block_size_plus_one)) ), (cwh-numbers[i]), block_size_plus_one, numbers[i], color);
      }
    }
  }

  int temp;
  // begin sorting
  for (int i = 0; i < data_elements; i++) {
    for (int j = 1; j < data_elements - i; j++) {
      if (numbers[j] < numbers[j-1]) {
        temp = numbers[j];
        numbers[j] = numbers[j-1];
        numbers[j-1] = temp;

        if (playAudialization()) {
          MidiNote note = Util::scaleToNote(numbers[j], std::make_pair(0, getCanvasHeight()), std::make_pair(C3, C7));
          voices.at(0).play(note, Timing::MICROSECOND, 50);
        }

        if (showVisualization()) {
          can->sleep();  // recommended to sleep before drawing
          if(j <= number_normal_block_size) {
            can->drawRectangle((j*block_size), 0, block_size, cwh, bg);
            can->drawRectangle((j*block_size), (cwh-numbers[j]), block_size, numbers[j], color);
            can->drawRectangle(((j-1)*block_size), 0, block_size, cwh, bg);
            can->drawRectangle(((j-1)*block_size), (cwh-numbers[j-1]), block_size, numbers[j-1], color);
          } else {
            can->drawRectangle(((number_normal_block_size*block_size)+(((j)-number_normal_block_size)*block_size_plus_one)), 0, block_size_plus_one, cwh, bg);
            can->drawRectangle(((number_normal_block_size*block_size)+(((j)-number_normal_block_size)*block_size_plus_one)), (cwh-numbers[j]), block_size_plus_one, numbers[j], color );
            can->drawRectangle(((number_normal_block_size*block_size)+(((j-1)-number_normal_block_size)*block_size_plus_one)), 0, block_size_plus_one, cwh, bg);
            can->drawRectangle(((number_normal_block_size*block_size)+(((j-1)-number_normal_block_size)*block_size_plus_one)), (cwh-numbers[j-1]), block_size_plus_one, numbers[j-1], color);
          }
        }
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
        can->drawRectangle(((number_normal_block_size*block_size)+((i-number_normal_block_size)*block_size_plus_one)), (cwh-numbers[i]), block_size_plus_one, numbers[i], sort_done_color);
      }
    }

    can->wait();
  }

  delete[] numbers;
}

void BubbleSorter::run() {
  if (showVisualization()) {
    createCanvas("Bubble Sort");
    canvas->setBackgroundColor(BLACK);
  }

  if (playAudialization()) {
    createMixer();

    voices = std::vector<ThreadSynth>(1, ThreadSynth(mixer));
    mixer->add(voices[0]);
    voices[0].setEnvelopeActive(false);
  }

  if (showVisualization() || playAudialization()) {
    BubbleSort(canvas, voices, getDataAmount());
  } else {
    std::cout << "neither -v or -a flags set" << std::endl;
    std::exit(0);
  }
}


}