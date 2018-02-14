#define DECOD2 PA1
#define DECOD1 PB2
#define DECOD0 PB1

#define idle 0
#define pressed 1
#define press_debounce 2
#define key_stable 3
#define released 4
#define key_ok 5
#define outRow 10
#define keyPresses 20
#define debounce 30
#define releasedDebounce 35
#define keyStill 40
#define getKey 50
#define waitRelease 60


extern char keyPadScan();
extern void init_keyPad();
extern char ms;
