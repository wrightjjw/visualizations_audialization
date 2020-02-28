/**
 * BubbleSorter.cpp defines the methods and algorithm required to make the audial/visualizaiton for bubble sort
 * 
 * Who: Nate Herder
 * When: 02/27/2020
 * Where: Calvin University
 * 
 */

#include "BubbleSorter.h"

namespace avlib {

BubbleSorter::BubbleSorter( int argc, char **argv ) : SortingAudialVisualization(argc, argv) {

}

void BubbleSorter::aBubbleSort(ThreadSynth& synth, int size) {

  const int maxNumber = 1000;
  int* numbers = new int[size];       // Array to store the data
  for ( int i = 0; i < size; i++ ) {
    numbers[i] = rand() % maxNumber;
  }

  int temp;
  for( int i = 0; i < size; i++ ) {
    for( int j = 1; j < size - i; j++ ) { //int j = size - 1; j > i; j-- 
      
      synth.play(C3 + 40 * ((double) numbers[j] / getCanvasHeight()), Timing::MICROSECOND, 100);
      
      if ( numbers[j] < numbers[j - 1] ) {
        temp = numbers[j];
        numbers[j] = numbers[j - 1];
        numbers[j - 1] = temp;
      }
    }
  }

}

void BubbleSorter::vBubbleSort(Canvas& can, int size) {

  can.start();
  int* numbers = new int[size];       // Array to store the data

  for( int i = 0; i < size; i++ ) {
    numbers[i] = rand() % (can.getWindowHeight() - MARGIN);
  }

  ColorFloat color = RED;
  ColorFloat bg = BLACK;
  int cwh = can.getWindowHeight() - MARGIN/2; //canvas window height
  for( int i = 0; i < size; i++ ) {
    can.drawLine(i, cwh, i, (cwh - numbers[i]), color);
  }

  int temp;
  for( int i = 0; i < size; i++ ) {
    for( int j = 1; j < size-i; j++ ) {
      can.sleep(); //it is recommended to sleep before drawing
      if ( numbers[j] < numbers[j - 1] ) {
        can.drawLine(j, cwh, j, 0, bg);
        can.drawLine(j-1, cwh, j-1, 0, bg);
        temp = numbers[j];
        numbers[j] = numbers[j - 1];
        numbers[j - 1] = temp;
        can.drawLine(j-1, cwh, j-1, (cwh - numbers[j-1]), color);
        can.drawLine(j, cwh, j, (cwh - numbers[j]), color);
      }
    }
  }

  ColorFloat wht = WHITE;
  for( int i = 0; i < size; i++ ) {
    can.drawLine(size-i, cwh, size-i, numbers[i], wht);
  }

  can.wait();
  delete [] numbers;

}

void BubbleSorter::avBubbleSort(Canvas& can, ThreadSynth& synth, int size) {

  can.start();
  int* numbers = new int[size];       // Array to store the data

  for( int i = 0; i < size; i++ ) {
    numbers[i] = rand() % (can.getWindowHeight() - MARGIN);
  }

  ColorFloat color = RED;
  int cwh = can.getWindowHeight() - MARGIN/2; //canvas window height
  for( int i = 0; i < size; i++ ) {
    can.drawLine(i, cwh, i, (cwh - numbers[i]), color);
  }

  int temp;
  for( int i = 0; i < size; i++ ) {
    for( int j = 1; j < size-i; j++ ) {

      can.sleep(); //it is recommended to sleep before drawing
      synth.play(C3 + 40 * ((double) numbers[j] / getCanvasHeight()), Timing::MICROSECOND, 100);
      if ( numbers[j] < numbers[j - 1] ) {
        can.drawLine(j, cwh, j, 0, can.getBackgroundColor());
        can.drawLine(j-1, cwh, j-1, 0, can.getBackgroundColor());
        temp = numbers[j];
        numbers[j] = numbers[j - 1];
        numbers[j - 1] = temp;
        can.drawLine(j-1, cwh, j-1, (cwh - numbers[j-1]), color);
        can.drawLine(j, cwh, j, (cwh - numbers[j]), color);
      }
    }
  }

  ColorFloat wht = WHITE;
  for( int i = 0; i < size; i++ ) {
    can.drawLine(size-i, cwh, size-i, numbers[i], wht);
  }

  can.wait();
  delete [] numbers;

}

void BubbleSorter::run() {
    
    if( showVisualization() ) {
        createCanvas();
    }
    if( playAudialization() ) {
        createMixer();
    }

    if( playAudialization() ) {
        voices = std::vector<ThreadSynth>(1, ThreadSynth(mixer));
        mixer->add(voices[0]);
        voices[0].setVolume(0.5);
        voices[0].setEnvelopeActive(false);
    }

    if( showVisualization() ) {
        canvas->setBackgroundColor(BLACK);
    }

    if( showVisualization() && playAudialization() ) {
        avBubbleSort(*canvas, voices.at(0), (getCanvasWidth() - MARGIN));
    } else if( showVisualization() ) {
        vBubbleSort(*canvas, (getCanvasWidth() - MARGIN));
    } else if( playAudialization() ) {
        aBubbleSort(voices.at(0), (getCanvasWidth() - MARGIN));
    } else {
        std::exit(0);
    }

}

}