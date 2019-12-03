/**
 * AudialVisualization.cpp defines the functionality that is common
 * to wanting running TSAL and TSGL applictions together.
 *
 * Who: Nate Herder
 * When: 11/06/2019
 * Where: Calvin University
 * 
 */

#include "AudialVisualization.h"


namespace avlib {

cxxopts::ParseResult parse( int argc, char **argv ) {

    try {

        cxxopts::Options options("AudialVisualization", "- command line options");

        options.positional_help("[optional args]").show_positional_help();

        options
            .allow_unrecognised_options()
            .add_options()
            ("help", "Print help")
            ("a, audial", "play audialization using TSAL", cxxopts::value<bool>()->default_value("false"))
            ("v, visual", "show visualization using TSGL", cxxopts::value<bool>()->default_value("false"))
            ("h, canvas-height", "TSGL canvas height", cxxopts::value<int>()->default_value("1024"))
            ("w, canvas-width", "TSGL canvas width", cxxopts::value<int>()->default_value("1024"))
            ("t, threads", "number of threads to use", cxxopts::value<int>()->default_value("1"));

        auto results =  options.parse(argc, argv);

        if( results.count("help") ) {
            std::cout << options.help({"", "Group"}) << std::endl;
            exit(0);
        }

        return results;

    } catch( const cxxopts::OptionSpecException& e ) {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }
}

AudialVisualization::AudialVisualization( int argc, char **argv ) {

    auto result = parse(argc, argv);
    
    if( result["canvas-height"].as<int>() > 0 ) {
        setCanvasHeight( result["canvas-height"].as<int>() );
    }
    if( result["canvas-width"].as<int>() > 0 ) {
        if( result["canvas-width"].as<int>() < 10 ) { //don't make the canvas any smaller than this
            setCanvasWidth( 100 );
        }
        setCanvasWidth( result["canvas-width"].as<int>() );
    }
    if( result["threads"].as<int>() > omp_get_num_procs() ) {
        setNumThreads( omp_get_num_procs() );
    } else {
        setNumThreads( result["threads"].as<int>() );
    }
    setAudialization( result["audial"].as<bool>() );
    setVisualization( result["visual"].as<bool>() );

}

Canvas* AudialVisualization::createCanvas() {

    if( showVisualization() ) {
        canvas = new Canvas(0, 0, getCanvasWidth(), getCanvasHeight(), "Canvas");
    }
    return canvas;
}

Mixer* AudialVisualization::createMixer() {

    if( playAudialization() ) {
        mixer = new Mixer();
    }
    return mixer;
}

void AudialVisualization::setVisualization(const bool b) {

    show_visualizaiton = b;
}

void AudialVisualization::setAudialization(const bool b) {

    play_audialization = b;
}

void AudialVisualization::setNumThreads(const int n) {

    num_threads = n;
}

void AudialVisualization::setCanvasHeight(const int h) {

    canvas_height = h;
}

void AudialVisualization::setCanvasWidth(const int w) {

    canvas_width = w;
}

bool AudialVisualization::showVisualization() const {

    return show_visualizaiton;
}

bool AudialVisualization::playAudialization() const {

    return play_audialization;
}

int AudialVisualization::getNumThreads() const {

    return num_threads;
}

int AudialVisualization::getCanvasHeight() const {

    return canvas_height;
}

int AudialVisualization::getCanvasWidth() const {

    return canvas_width;
}

AudialVisualization::~AudialVisualization() {

    delete canvas;
    delete mixer;
}

}