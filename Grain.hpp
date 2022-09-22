#ifndef GRANTIG_GRAIN_H
#define GRANTIG_GRAIN_H

#include "AudioFile.h"
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>

class Grain {
private:
    std::shared_ptr<AudioFile<double>> source_file;
    int start_in_file;
    int end_in_file;
    int next_zero_crossing(int position, int direction);
public:
    std::vector<double> samples;
    Grain(const std::shared_ptr<AudioFile<double>>& source_file);
    void move(int direction);
    void chlength(int direction, bool end);
    void reset();
};

#endif //GRANTIG_GRAIN_H