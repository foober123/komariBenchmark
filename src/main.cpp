#include <intrin.h>
#include <raylib.h>
#include "audioManager.h"
#include "timer.h"
#include <vector>
#include <string>

#define MIN 15
#define MAX 75
#define TRANSLUSCENT_MIDNIGHT_BLUE {25,25,112,128}
#define TEXTPADDING 2

static inline unsigned long long read_cycles() {
    return __rdtsc();
}

void dfs(int index,
         int currentSum,
         int target,
         const std::vector<int>& nums,
         std::vector<int>& subset,
         std::vector<std::vector<int>>& results)
{
    if(index == nums.size()){
        if(currentSum == target)
            results.push_back(subset);
        return;
    }

    // include
    subset.push_back(nums[index]);
    dfs(index + 1, currentSum + nums[index], target, nums, subset, results);

    // exclude
    subset.pop_back();
    dfs(index + 1, currentSum, target, nums, subset, results);
}

std::vector<std::vector<int>> subsetSum(const std::vector<int>& nums, int target)
{
    std::vector<std::vector<int>> results;
    std::vector<int> subset;

    dfs(0, 0, target, nums, subset, results);

    return results;
}

int evaluateKomari(int cycles){
    if(cycles <= 2000000) return 0;


    if(cycles <= 50000000) return 1;

    return 2;
};

std::string evaluateKomariLine(int frame){
    switch(frame){
        case 0:
        return "ehe";
        case 1:
        return "fue";
        case 2:
        return "wah";
    }

    return "wah";
}


std::vector<int> generateVec(int size, int min, int max){
    std::vector<int> result;

    for(int i = 0; i < size; i++)
    {
        int num = GetRandomValue(min, max);
        result.push_back(num);
    }


    return result;
}

std::string vectorToString(const std::vector<int>& v)
{
    std::string result = "<";

    for(size_t i = 0; i < v.size(); i++){
        result += std::to_string(v[i]);

        if(i != v.size() - 1)
            result += ",";
    }

    result += ">";
    return result;
}


std::string evaluateKomariMessage(int avgCycles);
void drawVectorListOnScreen(const std::vector<std::vector<int>>&);

int main() {
    InitWindow(800, 600, "Komari-Max Benchmark");
    SetTargetFPS(60);
    InitAudioDevice();
    AudioManager audioManager;
    audioManager.loadSoundAndMusicPool("data/audio.json");

    Texture2D komariAtlas = LoadTexture("assets/komariAtlas.png");
    Texture2D background = LoadTexture("assets/background.jpg");
    Timer komariTime;

    StartTimer(&komariTime, 0.1);
    int n = 5;
    int frame = 0;
    int framesElapsed = 1;
    unsigned long long sumCycles = 0;
		
    PlayMusicStream(audioManager.getMusicFromPool("menu"));
    PlaySound(audioManager.getSoundFromPool(evaluateKomariLine(frame)));
    while (!WindowShouldClose()) {
        UpdateTimer(&komariTime);
        audioManager.updateMusic();

        if (IsKeyPressed(KEY_UP)){
            n++;
            framesElapsed = 0;
            sumCycles = 0;
        }

        if (IsKeyPressed(KEY_DOWN)){
            n--;
            framesElapsed = 0;
            sumCycles = 0;
        }
        int target = GetRandomValue(MIN, MAX) * GetRandomValue(1, 3);
        auto generatedSet = generateVec(n, MIN, MAX);

        int oldFrame = frame;
        unsigned long long start = read_cycles();

        auto subset = subsetSum(generatedSet, target); 

        unsigned long long end = read_cycles();
        unsigned long long cycles = end - start;
        sumCycles = sumCycles + cycles;
        framesElapsed++;
        auto avgFrames = (framesElapsed == 0) ? sumCycles / 1 : sumCycles/framesElapsed;

        frame = evaluateKomari(avgFrames);
        if(oldFrame != frame && TimerDone(&komariTime)){
            audioManager.stopAllSound();
            PlaySound(audioManager.getSoundFromPool(evaluateKomariLine(frame)));
            StartTimer(&komariTime, 0.5);
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureRec(background, {0,0,800,600}, {0,0}, WHITE); 

        if(subset.size() <= 100)drawVectorListOnScreen(subset); 


        DrawTexturePro(komariAtlas, {(static_cast<float>(frame) * 315),0,315,600}, {(800-315)/2,0,315,600}, {0,0}, 0, WHITE);

        DrawRectangleRounded({50,475,700,100}, .3,20,TRANSLUSCENT_MIDNIGHT_BLUE);

        DrawRectangleRounded({50,440,90,28}, .3, 20, TRANSLUSCENT_MIDNIGHT_BLUE);
        DrawText("Komari", 55 + TEXTPADDING, 442 + TEXTPADDING, 24, BLACK);
        DrawText("Komari", 55, 442, 24, RAYWHITE);

        DrawText(TextFormat("At n = %d. Your computer's CPU is doing %llu cycles", n, cycles), 55 + TEXTPADDING, 485 + TEXTPADDING, 22, BLACK);
        DrawText(TextFormat("At n = %d. Your computer's CPU is doing %llu cycles", n, cycles), 55, 485, 22, RAYWHITE);

        DrawText(TextFormat("Average: %d. You have generated %d subsets", avgFrames, subset.size()), 55 + TEXTPADDING, 509 + TEXTPADDING, 22, BLACK);
        DrawText(TextFormat("Average: %d. You have generated %d subsets", avgFrames, subset.size()), 55, 509, 22, RAYWHITE);

        DrawText(TextFormat("%s", evaluateKomariMessage(avgFrames).c_str()), 55 + TEXTPADDING, 533 + TEXTPADDING, 22, BLACK);
        DrawText(TextFormat("%s", evaluateKomariMessage(avgFrames).c_str(), subset.size()), 55, 533, 22, RAYWHITE);

        if(subset.size() > 100) drawVectorListOnScreen(subset);

        EndDrawing();
    }

    CloseWindow();
}

void drawVectorListOnScreen(const std::vector<std::vector<int>>& set){
        for(const auto& vec : set)
        {
            std::string text = vectorToString(vec);

            int x = GetRandomValue(-50, 750);
            int y = GetRandomValue(-50, 550);
    

            DrawText(text.c_str(), x+2, y+2, 20, BLACK);
            DrawText(text.c_str(), x, y, 20, RAYWHITE);
        }

}


std::string evaluateKomariMessage(int avgCycles){
    if(avgCycles < 0) return "You broke the profiler. Silly, silly, silly, silly you...";

    if(avgCycles <= 2000000) return "Not that many...";


    if(avgCycles <= 50000000) return "Fue... this is starting to look big";

    return "Wah! your computer is going to overheat";
} 
