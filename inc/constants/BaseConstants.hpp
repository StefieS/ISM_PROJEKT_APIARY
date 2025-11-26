#ifndef __BASE_CONSTANTS
#define __BASE_CONSTANTS


namespace BaseConstants {
    constexpr int FRAMES_PER_HIVE = 5;
    constexpr int TIME_TO_OPEN_HIVE = 15;
    constexpr int TIME_TO_TAKE_OUT_FRAME = 20;
    constexpr int TIME_FROM_STAND_TO_TRANSPORT = 2*20;
    constexpr int TIME_TO_PUT_THE_FRAME_BACK = 10;

    constexpr int TIME_OF_EXTRACTOR_RUNNING = 5*60;
    constexpr int TIME_TO_UNLOAD_FRAME_FROM_EXTRACTOR = 7;
    constexpr int EXTRACTOR_CAPACITY = 5;
    constexpr double PERC_EXTRACTOR_AGAIN = 0.25;
};

#endif // __BASE_CONSTANTS