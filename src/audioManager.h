#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <unordered_map>
#include <string>
#include <raylib.h>

class AudioManager{
    public:
    AudioManager();
    ~AudioManager();

    void loadSoundAndMusicPool(std::string path);
    void unloadSoundAndMusicPool();
    void updateMusic();
    void stopAllSound();

    Sound getSoundFromPool(std::string key);
    Music getMusicFromPool(std::string key);
    void stopAllMusicTrack();
    private:
        std::unordered_map<std::string, Music> musicPool;
        std::unordered_map<std::string, Sound> soundPool;
};


#endif
