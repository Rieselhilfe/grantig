#ifndef GRANTIG_CONTROLLER_H
#define GRANTIG_CONTROLLER_H

#include "Tone.hpp"
#include "Vector2.h"
#include <random>
#include <functional>
#include "raylib.h"

constexpr int AMPLITUDE = 28000;
constexpr int WINDOW_WIDTH = 500;
constexpr int WINDOW_HEIGHT = 500;
constexpr int WINDOW_CENTER = 250;
constexpr int FPS = 30;

class Controller {
private:
    std::vector<Grain> grains;
    std::vector<Envelope> envelopes;
    std::vector<Tone> tones;
    std::vector<Grain>::iterator grain_sel; 
    std::vector<Envelope>::iterator env_sel;
    std::vector<AudioFile<double>> files;
    int sample_nr;
    SDL_AudioSpec desired_spec;
    SDL_AudioSpec obtained_spec;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
    std::_Bind<std::uniform_int_distribution<int> (std::default_random_engine)> dice;
public:
    Controller();
    Controller(const std::vector<std::string>& filenames);
    void init();
    void update(float delta);
    void draw(float delta);
    void make_tone();
    static void audio_callback(void *user_data, Uint8 *raw_buffer, int bytes);
    inline Sint16 format_sample(double sample) { return (Sint16)AMPLITUDE*sample; };
    ~Controller();
};

extern Controller controller;
#endif //GRANTIG_CONTROLLER_H