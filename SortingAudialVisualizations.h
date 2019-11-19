/**
 * SortingAudialVisualization.h declares the class that all audial visualizations
 * will inherit from containing all methods, command line preferences, and other data
 * that is common across all sorting algorithms.
 * 
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 * 
 */

#ifndef SortingAudialVisualization_H
#define SortingAudialVisualization_H

#include "tsgl.h"
#include "AudialVisualization.h"
#include <string.h>


using namespace tsgl;
using namespace tsal;

class SortingAudialVisualization : public AudialVisualization {

    public:
        SortingAudialVisualization( int argc, char **argv );
        virtual void sortData(int *array, int first, int last, ColorFloat color);
};

#endif