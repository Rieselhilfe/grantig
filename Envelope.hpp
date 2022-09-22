#ifndef ENVELOPE_CONTROLLER_H
#define ENVELOPE_CONTROLLER_H

#include "Grain.hpp"

class Envelope {
private:
    int attack;
    int decay;
    int sustain;
    double sustain_level;
    int release;
public:
    std::vector<double> samples;
    Envelope(int attack, int decay, int sustain, double sustain_level, int release);
};

#endif //ENVELOPE_CONTROLLER_H