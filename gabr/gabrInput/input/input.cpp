#include "input.h"
#include <unordered_map>

namespace Gabr::Input
{
    static std::unordered_map<SDL_Keycode, Button> keyboard;
    static std::unordered_map<Uint8, Button> mouse;

    void BeginFrame()
    {
        for (auto& [key, btn] : keyboard)
            btn.previous = btn.current;

        for (auto& [key, btn] : mouse)
            btn.previous = btn.current;
    }

    void ProcessEvent(const SDL_Event& e)
    {
        switch (e.type)
        {
        case SDL_EVENT_KEY_DOWN:
            keyboard[e.key.key].current = true;
            break;

        case SDL_EVENT_KEY_UP:
            keyboard[e.key.key].current = false;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            mouse[e.button.button].current = true;
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            mouse[e.button.button].current = false;
            break;
        }
    }

    KeyState GetKey(SDL_Keycode key)
    {
        auto it = keyboard.find(key);
        if (it == keyboard.end())
            return KeyState::None;

        auto& btn = it->second;

        if (btn.current && !btn.previous)
            return KeyState::Pressed;
        if (!btn.current && btn.previous)
            return KeyState::Released;
        if (btn.current && btn.previous)
            return KeyState::Held;

        return KeyState::None;
    }

    KeyState GetMouse(Uint8 button)
    {
        auto it = mouse.find(button);
        if (it == mouse.end())
            return KeyState::None;

        auto& btn = it->second;

        if (btn.current && !btn.previous)
            return KeyState::Pressed;
        if (!btn.current && btn.previous)
            return KeyState::Released;
        if (btn.current && btn.previous)
            return KeyState::Held;

        return KeyState::None;
    }
}
