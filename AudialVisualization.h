/**
 * AudialVisualization.h declares a class that can be inherited from
 * to wrap TSGL and TSAL programs.
 * 
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 * 
 */

#ifndef Audialisualization_H
#define AudialVisualization_H

#include <iostream>
#include <cxxopts.hpp>
#include <tsgl.h>
#include <tsal.hpp>
#include <omp.h>
#include <memory>

using namespace tsgl;
using namespace tsal;


class AudialVisualization {

    private:
        int num_threads;
        bool show_visualizaiton = false;
        bool play_audialization = false;
        // int window_height;
        // int window_width;
        std::string sound_file = "";
        Mixer *mixer = nullptr;
        Canvas *canvas = nullptr;

    public:
        Canvas* getCanvas();
        Mixer* getMixer();
        AudialVisualization( int argc, char **argv );
        void setVisualization(const bool b);
        void setAudialization(const bool b);
        void setNumThreads(const int n);
        // void setWindowHeight(const int h);
        // void setWindowWidth(const int w);
        bool showVisualization() const;
        bool playAudialization() const;
        int getNumThreads() const;
        ~AudialVisualization();
        // int getWindowHeight() const;
        // int getWindowWidth() const;

};

#endif