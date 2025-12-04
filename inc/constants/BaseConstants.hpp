#ifndef __BASE_CONSTANTS
#define __BASE_CONSTANTS


namespace BaseConstants {
    constexpr int FRAMES_PER_HIVE = 5;
    extern int HIVES_TO_OPEN;
    constexpr int TIME_TO_OPEN_HIVE = 15;
    constexpr int TIME_TO_TAKE_OUT_FRAME = 20;
    constexpr int TIME_FROM_STAND_TO_TRANSPORT = 2*20;
    constexpr int TIME_TO_PUT_THE_FRAME_BACK = 10;

    constexpr int TIME_OF_EXTRACTOR_RUNNING = 4*60;
    constexpr int TIME_TO_UNLOAD_FRAME_FROM_EXTRACTOR = 7;
    constexpr int TIME_TO_PUT_FRAME = 13;
    constexpr int EXTRACTOR_CAPACITY = 5;
    constexpr double PERC_EXTRACTOR_AGAIN = 0.1;
    constexpr double PERC_LONG_UNCAPPING = 0.25;

    constexpr int HONEY_PER_EXTRACTOR_RUN = 5;
    constexpr int BUCKET_CAPACITY = 20;
    constexpr int BUCKET_TAKING_TIME = 40;

    constexpr int TIME_OF_LONG_UNCAPPING = 1*60;
    constexpr int TIME_OF_SHORT_UNCAPPING = 20;

    constexpr int STRAINING_TIME = 30*60;
};

#endif // __BASE_CONSTANTS