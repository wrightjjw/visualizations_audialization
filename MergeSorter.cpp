/**
 * MergeSort.cpp defines the methods and algorithm required to make the audial/visualizaiton for merge sort
 * 
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 * 
 */

#include "MergeSorter.h"

MergeSorter::MergeSorter( int argc, char **argv ) : SortingAudialVisualization(argc, argv) {


}

void MergeSorter::run() {

    std::cout << "RUN() funciton called" << std::endl;

    auto c = getCanvas();
    auto m = getMixer();

    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        {
            if( showVisualization() ) {
                c->start();
                
                //'H'
                Line h0(100, 50, 100, 300, BLACK);
                Line h1(100, 150, 165, 150, BLACK);
                Line h2(165, 50, 165, 300, BLACK);

                //'E'
                Line e0(200, 50, 280, 50, BLACK);
                Line e1(200, 50, 200, 300, BLACK);
                Line e2(200, 150, 280, 150, BLACK);
                Line e3(200, 300, 280, 300, BLACK);

                //The two 'L's
                Line l0(300, 50, 300, 300, BLACK);
                Line l1(300, 300, 320, 300, BLACK);
                Line l2(350, 50, 350, 300, BLACK);
                Line l3(350, 300, 370, 300, BLACK);

                //'O'
                Ellipse o(400, 180, 30, 100, BLACK, false);

                // //Add 'HELLO' to the Canvas
                c->add(&h0); c->add(&h1); c->add(&h2);
                c->add(&e0); c->add(&e1); c->add(&e2); c->add(&e3);
                c->add(&l0); c->add(&l1); c->add(&l2); c->add(&l3);
                c->add(&o);

                c->wait();
            }
        }

        #pragma omp section
        {   
            if( playAudialization() ) {
            
                // Create the synthesizer object
                Synth synth(m);
                
                // Add the synth to the mixer
                m->add(synth);
                
                // Play a note on the synth
                synth.play(tsal::C4);
                
                // Wait for the user to stop the synth
                char input;
                std::cout << "Press <enter> to quit:" << std::flush;
                std::cin.get(input);
                
                // Stop the synth
                synth.stop();
            }
        }
    }
}