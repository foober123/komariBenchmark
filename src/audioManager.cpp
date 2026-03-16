#include "audioManager.h"
#include <iostream>
#include <raylib.h>
#include "../include/nlohmann/json.hpp"
#include <fstream>
using json = nlohmann::json;

AudioManager::AudioManager(){}
AudioManager::~AudioManager(){
    unloadSoundAndMusicPool();
}

void AudioManager::loadSoundAndMusicPool(std::string path){
    std::ifstream file(path);
    json j;
    file >> j;

    for (auto& [id, data] : j.items())
    {
        std::string type = data["type"];
        std::string filePath = data["path"];
        float volume = data.value("volume", 1.0f);

        if (type == "sound")
        {
            Sound s = LoadSound(filePath.c_str());
            SetSoundVolume(s, volume);
            soundPool[id] = s;
        }
        else if (type == "music")
        {
            Music m = LoadMusicStream(filePath.c_str());
            SetMusicVolume(m, volume);
            musicPool[id] = m;
        }
    }

} 

Sound AudioManager::getSoundFromPool(std::string key){
    if(soundPool.count(key)){
        return soundPool.at(key);
    }
    else{
        std::cerr << "Sound: '" << key << "' was not loaded";
        return Sound{};
    }

}

Music AudioManager::getMusicFromPool(std::string key){
    if(musicPool.count(key)){
        return musicPool.at(key);
    }
    else{
        std::cerr << "Sound: '" << key << "' was not loaded";
        return Music{};
    }

}

void AudioManager::stopAllMusicTrack(){

    for (std::pair<const std::string, Music>& keyPairMusic : musicPool) {
        if(IsMusicStreamPlaying(keyPairMusic.second)){
            StopMusicStream(keyPairMusic.second);
        }

    }
}

void AudioManager::stopAllSound(){

    for(std::pair<const std::string, Sound>& keyPairSound : soundPool){
        if(IsSoundPlaying(keyPairSound.second)){
            StopSound(keyPairSound.second);
        }
    }

}

void AudioManager::unloadSoundAndMusicPool(){

    for (std::pair<const std::string, Sound>& keyPairSound : soundPool) {
        UnloadSound(keyPairSound.second); 
    }

    for (std::pair<const std::string, Music>& keyPairMusic : musicPool) {
        UnloadMusicStream(keyPairMusic.second); 
    }


}

void AudioManager::updateMusic(){
    for(std::pair<const std::string, Music>& keyPairMusic : musicPool ){
        UpdateMusicStream(keyPairMusic.second);
    }


}
