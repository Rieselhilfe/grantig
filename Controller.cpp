#include "Controller.hpp"

Controller::Controller() : distribution(1,10000), 
        dice(std::bind(distribution, generator)) {};

Controller::Controller(const std::vector<std::string>& filenames) : 
        distribution(1,10000), 
        dice(std::bind(distribution, generator)) {
    if(SDL_Init(SDL_INIT_AUDIO) != 0) SDL_Log("Failed to initialize SDL: %s", SDL_GetError());

    sample_nr = 0;
    for (auto &&f: filenames) {
        AudioFile<double> audioFile;
        audioFile.load(f);    
        files.emplace_back(f);
    }

    desired_spec.freq = files[0].getSampleRate(); // number of samples per second
    desired_spec.format = AUDIO_S16SYS; // sample type (here: signed short i.e. 16 bit)
    desired_spec.channels = 1; // only one channel
    desired_spec.samples = 2048; // buffer-size
    desired_spec.callback = audio_callback; // function SDL calls periodically to refill the buffer
    desired_spec.userdata = &sample_nr; // counter, keeping track of current sample number

    if(SDL_OpenAudio(&desired_spec, &obtained_spec) != 0) SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to open audio: %s", SDL_GetError());
    if(desired_spec.format != obtained_spec.format) SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to get the desired AudioSpec");

    for (auto &&f: files) {
        grains.emplace_back(Grain(std::make_shared<AudioFile<double>>(f)));
    }
    grain_sel = grains.begin()+2;
    envelopes.emplace_back(Envelope(250,75,75,0.8,2000));
    env_sel = envelopes.begin();
}

void Controller::init() {
    ClearBackground(RAYWHITE);
}

void Controller::update(float delta) {
    int pressed = 0;
    while ((pressed = GetKeyPressed())) {
        switch (pressed) {
        case 'c':
            CloseWindow();
            break;
        case 'a':
            grain_sel->move(-1);
            break;
        case 'd':
            grain_sel->move(1);
            break;
        case 'w':
            grain_sel->chlength(1, 1);
            break;
        case 's':
            grain_sel->chlength(-1, 1);
            break;
        case 'k':
            grain_sel++;
            if (grain_sel == grains.end()) grain_sel=grains.begin();
            break;
        case ' ':
            make_tone();
            break;
        default:
            break;
        }
    }
    if (tones.size() == 0) {
        SDL_PauseAudio(true);
    } // TODO schöner
}

void Controller::draw(float delta) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText(std::to_string(grain_sel->samples.size()).c_str(), WINDOW_CENTER-15, WINDOW_CENTER-15, 50, RAYWHITE);

    EndDrawing();
}

void Controller::make_tone() {
    if (tones.size()<=4) {
        tones.emplace_back(Tone(grain_sel, env_sel));
        SDL_PauseAudio(false);
    }
}


void Controller::audio_callback(void *user_data, Uint8 *raw_buffer, int bytes) {    
    Sint16 *buffer = (Sint16*)raw_buffer;
    int length = bytes / 2; // 2 bytes per sample for AUDIO_S16SYS
    int &sample_nr(*(int*)user_data);


    for(int i = 0; i < length; i++, sample_nr++) {
        Sint16 sample = 0;
        auto t_it = controller.tones.begin();
        while( t_it != controller.tones.end() ) {
            double val; bool not_finished;
            std::tie(val, not_finished) = t_it->get_next_sample();
            sample += (Sint16) controller.format_sample(val);
            if (not_finished) ++t_it;
            else t_it = controller.tones.erase(t_it);
        }
        buffer[i] = sample;
    }
}

Controller::~Controller() {
    SDL_PauseAudio(true);
    SDL_CloseAudio();
}