/**
 * showfireworks.cpp defines the methods and algorithm required to make the
 * audial/visualizaiton for a linear search
 *
 * Who: Nate Herder
 * When: 04/23/2020
 * Where: Calvin University
 *
 */

#include "showfireworks.h"
#include "Arc.h"

namespace avlib {

  ShowFireworks::ShowFireworks(int argc, char **argv) : AudialVisualization(argc, argv) {

  }

  void ShowFireworks::fireWorkFunction(Canvas *can, std::vector<ThreadSynth> &voices, int threads, int numFireworks, int speed) {

    Arc** arcs = new Arc*[numFireworks];
    for (int i = 0; i < numFireworks; i++) {
      arcs[i] = new Arc(can);
    }
    ColorFloat col = can->getBackgroundColor();
    col.A = 0.04f;
    const int CWW = can->getWindowWidth(), CWH = can->getWindowHeight();
    while(can->isOpen()) {
      #pragma omp parallel num_threads(threads)
      {
      int tid = omp_get_thread_num();
      int nthreads = omp_get_num_threads();
      for (int n = 0; n < speed; ++n) {
        for (int i = tid; i < numFireworks; i += nthreads)
          arcs[i]->step();
        if (tid == 0)
          can->drawRectangle(0, 0, CWW, CWH, col);
        #pragma omp barrier
      }
      can->sleep();
      }
    }
    for (int i = 0; i < numFireworks; i++) {
      delete arcs[i];
    }
    delete [] arcs;

  }

  void ShowFireworks::run() {

    if ( showVisualization() ) {
      createCanvas("Fireworks!");
      canvas->setBackgroundColor(BLACK);
    }

    if ( playAudialization() ) {
      createMixer();

      voices = std::vector<ThreadSynth>(1, ThreadSynth(mixer));
      mixer->add(voices[0]);
      //voices[0].setVolume(0.5);
      voices[0].setEnvelopeActive(false);
    }

    if ( showVisualization() ) {
      fireWorkFunction(canvas, voices, getNumThreads(), 50, 10);
    } else {
      std::cout << "no -v falg set" << std::endl;
      std::exit(0);
    }

  }

}