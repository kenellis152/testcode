#include "LTimer.h"

LTimer::LTimer()
{
    //ctor
    //initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

void LTimer::start()
{
    //start the timer
    mStarted = true;

    //unpause the itmer
    mPaused = false;

    //get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop()
{
    //stop hte itmer
    mStarted = false;

    //unpause the timer
    mPaused = false;

    //clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause()
{
    //if hte itmer is running and isn't already paused
    if(mStarted && !mPaused)
    {
        //pause the timer
        mPaused = true;

        //calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    //if hte timer is running and paused
    if(mStarted && mPaused)
    {
        //unpause the timer
        mPaused = false;

        //reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        //reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
    //the actual itmer time
    Uint32 time = 0;

    //if the timer is running
    if(mStarted)
    {
        //if the timer is paused
        if(mPaused)
        {
            //return hte number of itcks when the itmer was paused
            time = mPausedTicks;
        }
        else
        {
            //return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}

bool LTimer::isStarted()
{
    //timer is running and paused or unpaused
    return mStarted;
}

bool LTimer::isPaused()
{
    //timer is running and paused
    return mPaused && mStarted;
}


LTimer::~LTimer()
{
    //dtor
}
