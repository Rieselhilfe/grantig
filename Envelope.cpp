#include "Envelope.hpp"

constexpr int ENVMULT = 10;

Envelope::Envelope(int attack, int decay, int sustain, double sustain_level, int release) : 
        attack(attack*ENVMULT), decay(decay*ENVMULT), sustain(sustain*ENVMULT), 
        sustain_level(sustain_level), release(release*ENVMULT) {
    samples.reserve((attack+decay+sustain+release)*ENVMULT);
    
    for (int i = 1; i <= this->attack; i++) {
        samples.emplace_back(pow((double)i/this->attack, 2));
    }
    
    for (int i = 1; i <= this->decay; i++) {
        samples.emplace_back(1-pow((double)i/this->decay, 2)*(1-this->sustain_level));
    }
    
    for (int i = 1; i <= this->sustain; i++) {
        samples.emplace_back(this->sustain_level);
    }
    
    for (int i = 1; i <= this->release; i++) {
        samples.emplace_back(this->sustain_level-pow((double)i/this->release, 2)*(this->sustain_level));
    }
};