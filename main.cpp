nclude "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

PwmOut piezo(P2_1);

#define r 0
#define c4 261.63
#define sc4 277.18
#define d4 293.66
#define sd4 311.13
#define e4 329.63
#define f4 349.23
#define sf4 369.99
#define g4 392.00
#define sg4 415.30
#define a4 440.00
#define sa4 466.16
#define b4 493.88
#define c5 523.5
#define sc5 554.37
#define d5 587.33
#define sd5 622.25
#define e5 659.25
#define f5 698.46
#define sf5 739.99
#define g5 783.99
#define sg5 830.61
#define a5 880.00
#define sa5 932.33
#define b5 987.77
#define c6 1046.50
#define sc6 1108.73
#define d6 1174.66
#define sd6 1244.51
#define e6 1318.51
#define f6 1396.91
#define sf6 1479.98
#define g6 1567.98
#define sg6 1661.22
#define a6 1760.00
#define sa6 1864.66
#define b6 1975.53
#define c7 2217.46

void playNote(float note, float duration){
    float period = 1.0f/note;
    piezo.period(period);
    piezo.pulsewidth(period/2); 
    wait(duration);   
}

void playNoteSeparated(float note, float duration){
    playNote(note, duration);
    piezo.period(0);
    wait(.05f);
}

void playChromatic(){
    float melody[] = {c5, sc5, d5, sd5, e5, f5, sf5, g5, sg5, a5, sa5, b5, c6};
    for(int i=0; i< (sizeof melody / sizeof *melody); i++){
        playNote(melody[i], .25);   
    }
    for(int i=(sizeof melody / sizeof *melody)-1; i>=0; i--){
        playNote(melody[i], .25);
    }
}

void playScale(){
    float melody[] = {c5, d5, e5, f5, g5, a5, b5, c6};
    for(int i=0; i< (sizeof melody / sizeof *melody); i++){
        playNote(melody[i], .25);   
    }
    for(int i=(sizeof melody / sizeof *melody)-1; i>=0; i--){
        playNote(melody[i], .25);
    }
}

void rage(){
    float melody[] = {b4, b4, b4, b4,  b4, b4, b4, b4, b4, b4, b4, b4, e5, e5, e5, e5, e5, e5, e5, e5, d5, d5, d5, d5, d5, d5, d5, a4, a4};
    float beat[] =   {.1, .1, .1, .1, .2, .1, .1, .1, .1, .1, .1, .2, .1, .1, .1, .1, .1, .1, .1, .2, .1, .1, .1, .1, .1, .1, .2, .1, .1};
    
    for(int i=0; i<(sizeof melody / sizeof *melody); i++){
        playNoteSeparated(melody[i], beat[i]*.7);
        switch(i%4){
            case 0:
                led1 = !led1;
                break;
            case 1:
                led2 = !led2;
                break;
            case 2:
                led3 = !led3;
                break;
            case 3:
                led4 = !led4;
                break;        
        }     
    }
}

void birthday(){
    float melody[] = {g5, g5, a5, g5, c6, b5, g5, g5, a5, g5, d6, c6, g5, g5, g6, e6, c6, b5, a5, f6, f6, e6, c6, d6, c6};
    float beat[]   = {.1, .1, .2, .2, .2, .4, .1, .1, .2, .2, .2, .4, .1, .1, .2, .2, .2, .2, .2, .1, .1, .2, .23, .28, .4};
    
    for(int i=0; i<(sizeof melody / sizeof *melody); i++){
        playNoteSeparated(melody[i], beat[i]*1.4);    
    }
    
    //Slide from c6 to b4
    for(float note = c6; note>b4; note = note-.1){
        float period = 1.0f/note;
        piezo.period(period);
        piezo.pulsewidth(period/2);
        wait(.001f);
    }
    
}

int main() { 

    playChromatic();
    playScale();
    birthday();
    while(1){
        rage();
        led1 = !led1;
        led2 = !led2;
        led3 = !led3;
        led4 = !led4;   
    }
}
