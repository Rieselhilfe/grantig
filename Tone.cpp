#include "Tone.hpp"

Tone::Tone(std::vector<Grain>::iterator grain, std::vector<Envelope>::iterator envelope) : 
        grain(grain), envelope(envelope) {}

std::pair<double, bool> Tone::get_next_sample() {
    double grain_value = grain->samples[position%grain->samples.size()];
    double env_value = envelope->samples[position];
    double ret_value = grain_value*env_value;
    position++;
    if (position >= envelope->samples.size()) return std::make_pair(ret_value, false);
    return std::make_pair(ret_value, true);
}