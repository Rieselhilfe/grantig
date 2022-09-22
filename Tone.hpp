#ifndef GRANTIG_TONE_H
#define GRANTIG_TONE_H

#include "Envelope.hpp"

class Tone {
private:
    int position = 0;
    std::vector<Grain>::iterator grain;
    std::vector<Envelope>::iterator envelope;
public:
    Tone(std::vector<Grain>::iterator grain, std::vector<Envelope>::iterator envelope);
    std::pair<double, bool> get_next_sample();
};

#endif //GRANTIG_TONE_H