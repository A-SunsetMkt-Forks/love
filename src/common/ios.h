/**
 * Copyright (c) 2006-2025 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#ifndef LOVE_IOS_H
#define LOVE_IOS_H

#include "config.h"

#ifdef LOVE_IOS

#include "common/math.h"

#include <string>

struct SDL_Window;

namespace love
{
namespace ios
{

/**
 * Gets the filepath of the first detected love file. The main .app Bundle is
 * searched first, and then the app's Documents folder.
 **/
std::string getLoveInResources(bool &fused);

/**
 * Causes devices with vibration support to vibrate for about 0.5 seconds.
 **/
void vibrate();

/**
 * Enable mix mode (e.g. with background music apps) and playback with a muted device.
 **/
bool setAudioMixWithOthers(bool mixEnabled);

/**
 * Returns whether another application is playing audio.
 **/
bool hasBackgroundMusic();

/**
 * Registers notifications to handle and restore audio interruptions
 **/
void initAudioSessionInterruptionHandler();
void destroyAudioSessionInterruptionHandler();
    
/**
 * Gets the area in the window that is safe for UI to render to (not covered by
 * the status bar, notch, etc.)
 **/
Rect getSafeArea(SDL_Window *window);

} // ios
} // love

#endif // LOVE_IOS
#endif // LOVE_IOS_H
