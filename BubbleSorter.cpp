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

BubbleSorter::BubbleSorter(int argc, char **argv) : SortingAudialVisualization(argc, argv) {

}

void BubbleSorter::BubbleSort(Canvas *can, std::vector<ThreadSynth> &voices, int size) {
  if (showVisualization()) {
    can->start();
  }

  // generate the data to sort
  int max_element;
  int *numbers = new int[size];  // Array to store the data
  for (int i = 0; i < size; i++) {
    numbers[i] = rand() % (getCanvasHeight() - MARGIN);
  }
  auto result = std::max_element(numbers, numbers+size);
  max_element = *result;

  int cwh = getCanvasHeight() - MARGIN / 2;  // canvas window height
  ColorFloat color = RED;
  ColorFloat bg = BLACK;

  // draw the original random data
  if (showVisualization()) {
    for (int i = 0; i < size; i++) {
      can->drawLine(i, cwh, i, (cwh - numbers[i]), color);
    }
  }

  // begin sorting
  int temp;
  for (int i = 0; i < size; i++) {
    for (int j = 1; j < size - i; j++) {
      if (showVisualization()) {
        can->sleep();  // recommended to sleep before drawing
      }
      if (playAudialization()) {
        MidiNote note = Util::scaleToNote(numbers[j], std::make_pair(0, max_element), std::make_pair(C3, C7));
        voices.at(0).play(note, Timing::MICROSECOND, 100);  //C3 + 40 * ((double)numbers[j] / getCanvasHeight())
      }

      if (numbers[j] < numbers[j - 1]) {
        if (showVisualization()) {
          can->drawLine(j, cwh, j, 0, bg);
          can->drawLine(j - 1, cwh, j - 1, 0, bg);
        }
        temp = numbers[j];
        numbers[j] = numbers[j - 1];
        numbers[j - 1] = temp;
        if (showVisualization()) {
          can->drawLine(j - 1, cwh, j - 1, (cwh - numbers[j - 1]), color);
          can->drawLine(j, cwh, j, (cwh - numbers[j]), color);
        }
      }
    }
  }

  // after sorting turn data white
  ColorFloat wht = WHITE;
  for (int i = 0; i < size; i++) {
    can->drawLine(size - i, cwh, size - i, numbers[i], wht);
  }

  can->wait();
  delete[] numbers;
}

void BubbleSorter::run() {
  if (showVisualization()) {
    createCanvas();
  }
  if (playAudialization()) {
    createMixer();
  }

  if (playAudialization()) {
    voices = std::vector<ThreadSynth>(1, ThreadSynth(mixer));
    mixer->add(voices[0]);
    voices[0].setVolume(0.5);
    voices[0].setEnvelopeActive(false);
  }

  if (showVisualization()) {
    canvas->setBackgroundColor(BLACK);
  }

  if (showVisualization() || playAudialization()) {
    BubbleSort(canvas, voices, (getCanvasWidth() - MARGIN));
  } else {
    std::cout << "neither -v or -a flags set" << std::endl;
    std::exit(0);
  }
}

}