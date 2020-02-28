/**
 * InsertionSorter.cpp defines the methods and algorithm required to make the audial/visualizaiton for insertion sort
 * 
 * Who: Nate Herder
 * When: 02/27/2020
 * Where: Calvin University
 * 
 */

#include "InsertionSorter.h"

namespace avlib {

    InsertionSorter::InsertionSorter( int argc, char **argv ) : SortingAudialVisualization(argc, argv) {

    }

    void InsertionSorter::aInsertionSort(ThreadSynth& synth, int size) {
        const int MAX_VALUE = 1000;

        // Generate data
        int* data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = rand() % MAX_VALUE;
        }

        int insertValue;
        int j;
        for (int i = 1; i < size; i++) {
            insertValue = data[i];
            j = i;
            while (j > 0 && data[j - 1] > insertValue) {
                synth.play(C2 + 55 * ((double) data[j] / getCanvasHeight()), Timing::MILLISECOND, 5);
                
                data[j] = data[j - 1];
                j--;
            }
            data[j] = insertValue;
        }

        delete [] data;
    }

    void InsertionSorter::vInsertionSort(Canvas& can, int size) {
        can.start();
        const int MAX_VALUE = 1000;

        // Generate data
        int* data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = rand() % (can.getWindowHeight() - MARGIN); //map data height into range of canvas
        }

        ColorFloat color = RED;
        ColorFloat bg = BLACK;
        int cwh = can.getWindowHeight() - MARGIN/2; //canvas window height
        for( int i = 0; i < size; i++ ) {
            can.drawLine(i, cwh, i, (cwh - data[i]), color);
        }

        int insertValue;
        int j;
        for (int i = 1; i < size; i++) {
            insertValue = data[i];
            j = i;
            while (j > 0 && data[j - 1] > insertValue) {
                can.sleep();
                can.drawLine(j, cwh, j, 0, bg);
                can.drawLine(j-1, cwh, j-1, 0, bg);
                data[j] = data[j - 1];
                can.drawLine(j-1, cwh, j-1, (cwh-insertValue), color);
                can.drawLine(j, cwh, j, (cwh-data[j]), color);
                j--;
            }
            data[j] = insertValue;
        }

        ColorFloat wht = WHITE;
        for( int i = 0; i < size; i++ ) {
            can.drawLine(size-i, cwh, size-i, data[i], wht);
        }

        can.wait();
        delete [] data;

    }

    void InsertionSorter::avInsertionSort(Canvas& can, ThreadSynth& synth, int size) {
        can.start();
        const int MAX_VALUE = 1000;

        // Generate data
        int* data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = rand() % (can.getWindowHeight() - MARGIN); //map data height into range of canvas
        }

        ColorFloat color = RED;
        ColorFloat bg = BLACK;
        int cwh = can.getWindowHeight() - MARGIN/2; //canvas window height
        for( int i = 0; i < size; i++ ) {
            can.drawLine(i, cwh, i, (cwh - data[i]), color);
        }

        int insertValue;
        int j;
        for (int i = 1; i < size; i++) {
            insertValue = data[i];
            j = i;
            while (j > 0 && data[j - 1] > insertValue) {
                can.sleep();
                synth.play(C2 + 55 * ((double) data[j] / getCanvasHeight()), Timing::MILLISECOND, 5);
                can.drawLine(j, cwh, j, 0, bg);
                can.drawLine(j-1, cwh, j-1, 0, bg);
                data[j] = data[j - 1];
                can.drawLine(j-1, cwh, j-1, (cwh-insertValue), color);
                can.drawLine(j, cwh, j, (cwh-data[j]), color);
                j--;
            }
            data[j] = insertValue;
        }

        ColorFloat wht = WHITE;
        for( int i = 0; i < size; i++ ) {
            can.drawLine(size-i, cwh, size-i, data[i], wht);
        }

        can.wait();
        delete [] data;
    }

    void InsertionSorter::run() {

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
            avInsertionSort(*canvas, voices.at(0), (getCanvasWidth() - MARGIN));
        } else if( showVisualization() ) {
            vInsertionSort(*canvas, (getCanvasWidth() - MARGIN));
        } else if( playAudialization() ) {
            aInsertionSort(voices.at(0), (getCanvasWidth() - MARGIN));
        } else {
            std::exit(0);
        }

    }

}