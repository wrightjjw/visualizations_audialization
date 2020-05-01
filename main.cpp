/**
 * main.cpp is the driver
 *
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 *
 */

#include "SortingAudialVisualization.h"
#include "LinearSearch.h"

using namespace avlib;

int main(int argc, char **argv) {

  LinearSearch ls(argc, argv);
  ls.run();  
  //SortingAudialVisualization av(argc, argv);

  return 0;
}