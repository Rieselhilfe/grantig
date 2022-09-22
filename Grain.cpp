#include "Grain.hpp"

Grain::Grain(const std::shared_ptr<AudioFile<double>>&  source_file) : source_file(source_file) {
    int file_length = source_file->getNumSamplesPerChannel();
    start_in_file = file_length / 3;
    end_in_file = start_in_file+2000;
    end_in_file = std::min(end_in_file, file_length);
    start_in_file = next_zero_crossing(start_in_file, 1);
    end_in_file = next_zero_crossing(end_in_file, 1);
    reset();
}

void Grain::reset() {
    samples.clear();
    samples.reserve(end_in_file-start_in_file);
    for (int i = start_in_file; i < end_in_file; i++) {
        samples.push_back(source_file->samples[0][i]);
    }
}

int Grain::next_zero_crossing(int position, int direction) {
    position = std::min(position, source_file->getNumSamplesPerChannel());
    bool sign = source_file->samples[0][position] >= 0;
    for (int i = position; 0 < i < source_file->getNumSamplesPerChannel(); i+=direction) {
        if ((source_file->samples[0][i] >= 0) != sign) {
            return i;
        }
    }
    return source_file->getNumSamplesPerChannel();
}

void Grain::move(int direction) {
    start_in_file += 2*direction;
    end_in_file += 2*direction;
    start_in_file = next_zero_crossing(start_in_file, direction);
    end_in_file = next_zero_crossing(end_in_file, direction);
    reset();
}

void Grain::chlength(int direction, bool end) {
    if (end) {
        end_in_file += 2*direction;
        end_in_file = next_zero_crossing(end_in_file, direction);
    } else {
        start_in_file += 2*direction;
        start_in_file = next_zero_crossing(start_in_file, direction);
    }
    reset();
}