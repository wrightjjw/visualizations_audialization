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
            ("h, window-height", "TSGL window height", cxxopts::value<int>()->default_value("1024"))
            ("w, window-width", "TSGL window width", cxxopts::value<int>()->default_value("1024"))
            ("t, threads", "number of threads to use", cxxopts::value<int>()->default_value("1"));

        auto results =  options.parse(argc, argv);

        if ( results.count("help") ) {
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
    
    if ( result["audial"].as<bool>() ) {
        setAudialization( true );
        mixer = new Mixer();
    }
    if ( result["visual"].as<bool>() ) {
        setVisualization( true );
        canvas = new Canvas(0, 0, 1024, 1024, "Wowowowowow it works");
    }
    // if ( result["window-height"].as<int>() > 0 ) {
    //     setWindowHeight( result["window-height"].as<int>() )
    // }
    // if ( result["window-width"].as<int>() > 0 ) {
    //     setWindowWitdth( result["window-width"].as<int>() );
    // }

    setNumThreads( result["threads"].as<int>() );

}

Canvas* AudialVisualization::getCanvas() {
    return canvas;
}

Mixer* AudialVisualization::getMixer() {
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

// void AudialVisualization::setWindowHeight(const int h) {

//     window_height = h;
// }

// void AudialVisualization::setWindowWidth(const int w) {

//     window_width = w;
// }

bool AudialVisualization::showVisualization() const {

    return show_visualizaiton;
}

bool AudialVisualization::playAudialization() const {

    return play_audialization;
}

int AudialVisualization::getNumThreads() const {

    return num_threads;
}

// int AudialVisualization::getWindowHeight() const {

//     return window_height;
// }

// int AudialVisualization::getWindowWidth() const {

//     return window_width;
// }

AudialVisualization::~AudialVisualization() {

    delete canvas;
    delete mixer;
}