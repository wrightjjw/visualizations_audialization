/**
 * ShakerSorter.cpp defines the methods and algorithm required to make the
 * audial/visualizaiton for shaker sort
 *
 * Who: Nate Herder
 * When: 02/27/2020
 * Where: Calvin University
 *
 */

#include "ShakerSorter.h"

namespace avlib {

ShakerSorter::ShakerSorter(int argc, char **argv, bool value) : SortingAudialVisualization(argc, argv, value) {

}

void ShakerSorter::ShakerSort(Canvas *can, std::vector<ThreadSynth> &voices, int data_elements) {
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

  // generate the data to sort
  int *numbers = new int[data_elements];  // Array to store the data
  for (int i = 0; i < data_elements; i++) {
    numbers[i] = rand() % getCanvasHeight();
  }

  std::cout << "MADE IT HERE!!!" << std::endl;

  // draw the original random data
  if (showVisualization()) {
    can->sleep();
    for (int i = 0; i < data_elements; i++) {
      if( i < number_normal_block_size ) {
        can->drawRectangle((i*block_size), (cwh-numbers[i]), block_size, numbers[i], color);
      } else {
        can->drawRectangle(((number_normal_block_size*block_size)+(((i-number_normal_block_size)*block_size_plus_one)) ), (cwh-numbers[i]), block_size_plus_one, numbers[i], color);
      }
    }
  }

  // // begin sorting
  // while (can.isOpen()) {
  //   can.sleep();  //Removed the timer and replaced it with an internal timer in the Canvas class
  //   if (min >= max) return;  // We are done sorting
  //   for (int i = 0; i < IPF; i++) {
  //     if (goingUp) {
  //       if (numbers[pos] > numbers[pos + 1]) {
  //         temp = numbers[pos];
  //         numbers[pos] = numbers[pos + 1];
  //         numbers[pos + 1] = temp;
  //         lastSwap = pos;
  //       }
  //       if (pos >= max) {
  //         pos = max;
  //         max = (lastSwap < max) ? lastSwap : max - 1;
  //         goingUp = !goingUp;
  //       } else
  //         pos++;
  //     } else {
  //       if (numbers[pos] < numbers[pos - 1]) {
  //         temp = numbers[pos];
  //         numbers[pos] = numbers[pos - 1];
  //         numbers[pos - 1] = temp;
  //         lastSwap = pos;
  //       }
  //       if (pos <= min) {
  //         pos = min;
  //         min = (lastSwap > min) ? lastSwap : min + 1;
  //         goingUp = !goingUp;
  //       } else
  //         pos--;
  //     }
  //   }
  //   int start = 50, width = 1, height;
  //   int cwh = can.getWindowHeight() - 20;
  //   ColorFloat color;
  //   can.pauseDrawing(); //Tell the Canvas to stop updating the screen temporarily
  //   can.clearProcedural();
  //   for (int i = 0; i < SIZE; i++, start += width * 2) {
  //     height = numbers[i];
  //     color = ColorInt(MAX_COLOR, (i == pos) ? MAX_COLOR : 0, 0);
  //     can.drawRectangle(start, cwh - height, width, height, color);
  //   }
  //   can.resumeDrawing(); //Tell the Canvas it can resume drawing
  // }


  // if(playAudialization()) {
  //   voices.at(0).stop();
  // }

  // //after sorting turn data white
  // if( showVisualization()) {
  //   for (int i = 0; i < data_elements; i++) {
  //     if(i < number_normal_block_size) {
  //       can->drawRectangle((i*block_size), (cwh-numbers[i]), block_size, numbers[i], sort_done_color);
  //     } else {
  //       can->drawRectangle(((number_normal_block_size*block_size)+((i-number_normal_block_size)*block_size_plus_one)), (cwh-numbers[i]), block_size_plus_one, numbers[i], sort_done_color);
  //     }
  //   }

  //   can->wait();
  // }

  delete[] numbers;


}

void ShakerSorter::run() {
  if (showVisualization()) {
    createCanvas("Shaker Sort");
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
    ShakerSort(canvas, voices, getDataAmount());
  } else {
    std::cout << "neither -v or -a flags set" << std::endl;
    std::exit(0);
  }
}


}