#pragma once
#include <SDL3/SDL.h>
#include <api.h>

namespace Gabr::Input
{
    enum class KeyState
    {
        None = 0,
        Pressed,
        Released,
        Held
    };

    struct Button
    {
        bool current = false;
        bool previous = false;
    };

    GABR_API void BeginFrame();
    GABR_API void ProcessEvent(const SDL_Event& e);

    GABR_API KeyState GetKey(SDL_Keycode key);
    GABR_API KeyState GetMouse(Uint8 button);
}
