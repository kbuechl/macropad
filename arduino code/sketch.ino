#include <Keyboard.h>

const int CODING_PIN = 9; //moved this to one that isnt used
const int PAUSE_PIN = 1;
const int DISCORD_PIN = 2;
const int SPOTIFY_PIN = 4;
const int KILL_PROCESS_PIN = 6;

/*
_________
|1 3 5 7|
|0 2 4 6|
---------
*/

boolean safeMode = false;
boolean isKeyboardStarted = false;

int pauseCommand[] = {KEY_LEFT_SHIFT, KEY_LEFT_ALT, 0x70}; //p
const int discordTriggerKey = KEY_F11;
const int spotifyTriggerKey = KEY_F12;
const int runKey = KEY_LEFT_CTRL;
const int killKey = KEY_LEFT_ALT;
const int unsupportedSetupKey = 0x0;

void setup()
{
    // we will use 0-7 so we can go ahead and pin that out
    for (int i = 0; i < 8; i++)
    {
        pinMode(i, INPUT_PULLUP);
    }

    pinMode(LED_BUILTIN, OUTPUT);

    safeMode = digitalRead(CODING_PIN) == LOW;

    if (!safeMode)
    {
        Keyboard.begin();
        isKeyboardStarted = true;
    }
}

void loop()
{
    if (safeMode && isKeyboardStarted)
    {
        Keyboard.end();
    }
    else if (!safeMode)
    {
        for (int i = 1; i < 8; i++) //dont include panic key
        {
            if (digitalRead(i) == LOW)
            {
                keyPressed(i);
            }
        }
        //always delay a little
        delay(150);
    }
}

void keyPressed(int key)
{
    switch (key)
    {
    case PAUSE_PIN:
        sendCommand(pauseCommand);
        break;
    case DISCORD_PIN:
        processKey(discordTriggerKey);
        break;
    case SPOTIFY_PIN:
        processKey(spotifyTriggerKey);
        break;
    default:
        processKey(unsupportedSetupKey);
    }
}
void sendCommand(int command[])
{
    for (int i = 0; i < 3; i++)
    {
        Keyboard.press(command[i]);
    }
    delay(100);
    Keyboard.releaseAll();
}

void processKey(int triggerKey)
{
    int command[] = {0x0, KEY_LEFT_SHIFT, triggerKey};

    if (digitalRead(KILL_PROCESS_PIN) == LOW)
    {
        command[0] = killKey;
    }
    else
    {
        command[0] = runKey;
    }
    sendCommand(command);
}
