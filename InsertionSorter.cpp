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

InsertionSorter::InsertionSorter(int argc, char** argv) : SortingAudialVisualization(argc, argv) {

}

void InsertionSorter::InsertionSort(Canvas* can, std::vector<ThreadSynth>& voices, int size) {
  if (showVisualization()) {
    can->start();
  }

  // Generate data
  int max_element;
  int* data = new int[size];
  for (int i = 0; i < size; i++) {
    data[i] = rand() % (getCanvasHeight() -
                        MARGIN);  // map data height into range of canvas
  }
  auto result = std::max_element(data, data+size);
  max_element = *result;

  int cwh = getCanvasHeight() -
            MARGIN / 2;  // canvas window height //- MARGIN/2 or just
                         // -MARGIN...look into this eventually
  ColorFloat color = RED;
  ColorFloat bg = BLACK;

  // draw the original random data
  if (showVisualization()) {
    for (int i = 0; i < size; i++) {
      can->drawLine(i, cwh, i, (cwh - data[i]), color);
    }
  }

  int insertValue;
  int j;

  // begin sorting
  for (int i = 1; i < size; i++) {
    insertValue = data[i];
    j = i;
    while (j > 0 && data[j - 1] > insertValue) {
      if (showVisualization()) {
        can->sleep();
        can->drawLine(j, cwh, j, 0, bg);
        can->drawLine(j - 1, cwh, j - 1, 0, bg);
      }
      if (playAudialization()) {
        MidiNote note = Util::scaleToNote(data[j], std::make_pair(0, max_element), std::make_pair(C3, C7));
        voices.at(0).play(note, Timing::MILLISECOND, 5);  // getCanvasHeight() //C2 + 55 * ((double)data[j] / getCanvasHeight())
      }
      data[j] = data[j - 1];
      if (showVisualization()) {
        can->drawLine(j - 1, cwh, j - 1, (cwh - insertValue), color);
        can->drawLine(j, cwh, j, (cwh - data[j]), color);
      }
      j--;
    }
    data[j] = insertValue;
  }

  // after sorting turn data white
  if (showVisualization()) {
    ColorFloat wht = WHITE;
    for (int i = 0; i < size; i++) {
      can->drawLine(size - i, cwh, size - i, data[i], wht);
    }
  }

  if (showVisualization()) {
    can->wait();
  }
  delete[] data;
}

void InsertionSorter::run() {
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
    InsertionSort(canvas, voices, (getCanvasWidth() - MARGIN));
  } else {
    std::cout << "neither -v or -a flags set" << std::endl;
    std::exit(0);
  }

}

}