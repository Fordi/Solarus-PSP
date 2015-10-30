/*
 * Copyright (C) 2006-2015 Christopho, Solarus - http://www.solarus-games.org
 *
 * Solarus is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Solarus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SOLARUS_INPUT_EVENT_H
#define SOLARUS_INPUT_EVENT_H

#include "solarus/Common.h"
#include <map>
#include <memory>
#include <set>
#include <string>
#include <SDL_events.h>

typedef struct _SDL_Joystick SDL_Joystick;

namespace Solarus {

class Rectangle;

/**
 * \brief Represents a low-level event.
 *
 * This low-level class provides an API for input events (keyboard, joypad and window events).
 * It encapsulates the library-dependent events.
 */
class InputEvent {

  public:

    /**
     * Enumeration of keyboard keys.
     * This is a Solarus dedicated enumeration.
     * To make the SDL encapsulation easier, this enumeration is compatible
     * with the SDL_Keycode enumeration from SDL.
     * If you intend to replace SDL by another library one day, the API of the
     * Input class will not have to change
     * (only its implementation will).
     * The numeric values of the enumeration can be changed without breaking
     * savegames because savegames use a string name to store the commands.
     */	
	SceCtrlData ctrl;
	sceCtrlPeekBufferPositive(&ctrl, 1);
	
    enum KeyboardKey {
      KEY_SPACE                    = (ctrl.Buttons & CROSS),
      KEY_c                        = (ctrl.Buttons & PSP_CTRL_SQUARE),
      KEY_d                        = (ctrl.Buttons & PSP_CTRL_START),
      KEY_v                        = (ctrl.Buttons & PSP_CTRL_CIRCLE),
      KEY_w                        = (ctrl.Buttons & PSP_CTRL_LTRIGGER),
	  KEY_s                        = (ctrl.Buttons & PSP_CTRL_RTRIGGER),
      KEY_x                        = (ctrl.Buttons & PSP_CTRL_TRIANGLE),

      KEY_UP                       = (ctrl.Buttons & PSP_CTRL_UP),
      KEY_DOWN                     = (ctrl.Buttons & PSP_CTRL_DOWN),
      KEY_RIGHT                    = (ctrl.Buttons & PSP_CTRL_RIGHT),
      KEY_LEFT                     = (ctrl.Buttons & PSP_CTRL_LEFT),
    };


    static void initialize();
    static void quit();

    // retrieve the current event
    static std::unique_ptr<InputEvent> get_event();

    // global information
    static void set_key_repeat(bool repeat);
    static bool is_shift_down();
    static bool is_control_down();
    static bool is_alt_down();
    static bool is_caps_lock_on();
    static bool is_num_lock_on();
    static bool is_key_down(KeyboardKey key);
    static bool is_joypad_button_down(int button);
    static int get_joypad_axis_state(int axis);
    static int get_joypad_hat_direction(int hat);

    // event type
    bool is_valid() const;
    bool is_keyboard_event() const;
    bool is_joypad_event() const;
    bool is_window_event() const;

    // keyboard
    bool is_keyboard_key_pressed() const;
    bool is_keyboard_key_pressed(KeyboardKey key) const;
    bool is_keyboard_key_pressed(const KeyboardKey* keys) const;
    bool is_keyboard_direction_key_pressed() const;
    bool is_keyboard_non_direction_key_pressed() const;

    bool is_keyboard_key_released() const;
    bool is_keyboard_key_released(KeyboardKey key) const;
    bool is_keyboard_key_released(const KeyboardKey* keys) const;
    bool is_keyboard_direction_key_released() const;
    bool is_keyboard_non_direction_key_released() const;

    bool is_with_shift() const;
    bool is_with_control() const;
    bool is_with_alt() const;

    KeyboardKey get_keyboard_key() const;
    static const std::string& get_keyboard_key_name(InputEvent::KeyboardKey key);
    static InputEvent::KeyboardKey get_keyboard_key_by_name(const std::string& keyboard_key_name);

    bool is_character_pressed() const;
    std::string get_character() const;

    // joypad
    static bool is_joypad_enabled();
    static void set_joypad_enabled(bool joypad_enabled);

    bool is_joypad_button_pressed() const;
    bool is_joypad_button_released() const;
    int get_joypad_button() const;
    bool is_joypad_axis_moved() const;
    int get_joypad_axis() const;
    int get_joypad_axis_state() const;
    bool is_joypad_axis_centered() const;
    bool is_joypad_hat_moved() const;
    int get_joypad_hat() const;
    int get_joypad_hat_direction() const;
    bool is_joypad_hat_centered() const;


    // functions common to keyboard, joypad and mouse
    int get_direction() const;
    bool is_pressed() const;
    bool is_direction_pressed() const;
    bool is_non_direction_pressed() const;
    bool is_released() const;

    // window event
    bool is_window_closing() const;

  private:

    InputEvent(const SDL_Event& event);

    static const KeyboardKey directional_keys[];  /**< array of the keyboard directional keys */
    static bool joypad_enabled;                   /**< true if joypad support is enabled
                                                   * (may be true even without joypad plugged) */
    static SDL_Joystick* joystick;                /**< the joystick object if enabled and plugged */
    static int joypad_axis_state[2];              /**< keep track of the current horizontal and verticle axis states */
    static std::map<KeyboardKey, std::string>
      keyboard_key_names;                         /**< Names of all existing mouse buttons. */
    static bool repeat_keyboard;                  /**< True to handle repeat KEYDOWN and KEYUP events. */
    static std::set<KeyboardKey> keys_pressed;    /**< Keys currently down, only according to SDL_KEYDOWN and SDL_KEYUP events
                                                   * (i.e. independently of the real current state SDL_GetKeyboardState()). */

    const SDL_Event internal_event;               /**< the internal event encapsulated */

};

}

#endif

