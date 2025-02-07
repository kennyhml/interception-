#pragma once
#include "core.h"
#include "beziercurve.h"

namespace interception
{
    // Quite a common thing to have to adjust based on what you're sending inputs to,
    // this provides a better way to apply it to all calls automatically.
    inline std::chrono::milliseconds default_press_duration(5);

    // If enabled, the durations and intervals will get slightly randomize to emulate
    // a more human timing. For example a 50ms delay may be in the range of 45ms to 55ms.
    inline bool randomize_durations = true;

    // The upper and lower bounds for the randomly generated factor that will be used to
    // randomize durations if the flag is enabled.
    inline std::pair rand_factor_bounds{0.8f, 1.2f};

    // If enabled, mouse acceleration will be automatically disabled on rel. mouse movements.
    // If you disable this, you must take care of it yourself or deal with the inaccuracy!
    inline bool auto_disable_mouse_accel = true;

    /**
     * @brief Determines both input devices (mouse and keyboard).
     *
     * @param keyboard_filter A keyword to find within the HWIDs to favor the keyboard device.
     * @param mouse_filter A keyword to find within the HWIDs to favor the device mouse.
     *
     * @return Whether a valid, usable device was found for the mouse and the keyboard.
     */
    INTERCEPTION_API bool capture_input_devices(const std::wstring& keyboard_filter = L"",
                                                const std::wstring& mouse_filter = L"");

    /**
     * @brief Sends one or more input event of the requested key or mouse button.
     *
     * @param input The key / mouse button to send the press events of.
     * @param times How many times to press the given input, default 1.
     * @param duration The duration to keep the input pressed for.
     * @param interval The time to sleep between the individual presses.
     *
     * @remark The duration is subject to slight randomization if the option is enabled.
     */
    INTERCEPTION_API void press(const inputable_t& input, int32_t times = 1,
                                ms duration = default_press_duration, ms interval = 50ms);

    /**
     * @brief Sends a down input event of the requested key or mouse button.
     *
     * @param input The key / mouse button to send the down event of.
     * @param duration If specified, how long to hold the key until it is released.
     *
     * @remark If hold_for is not set (as per default), the key must be manually released.
     * @remark The duration is subject to slight randomization if the option is enabled.
     */
    INTERCEPTION_API void hold(const inputable_t& input,
                               const std::optional<ms>& duration = std::nullopt);

    /**
     * @brief Sends an up input event of the requested key or mouse button.
     *
     * @param input The key / mouse button to send the up event of.
     *
     * @remark Nothing will happen if the requested key was not previously held.
     */
    INTERCEPTION_API void release(const inputable_t& input);

    /**
     * @brief Writes out the given text, every character is treated as an input.
     *
     * @param text The text to write, upper and lowercase are respected.
     *
     * @remark The duration is subject to slight randomization if the option is enabled.
     */
    INTERCEPTION_API void write(const std::string& text);

    /**
     * @brief Scrolls the mouse wheel in the given direction by a number of times.
     *
     * @param times The number of times to scroll up or down.
     * @param interval The interval (in milliseconds) to sleep between each scroll.
     *
     * @remark The interval is subject to slight randomization if the option is enabled.
     */
    INTERCEPTION_API void scroll(ScrollDirection, int32_t times, ms interval = 5ms);

    /**
     * @brief Moves a mouse to the given point on the screen.
     *
     * @param to The point to move to, consisting of (x, y) coordinates.
     * @param curve The parameters for the curve to use for the movement, or nullptr.
     *
     * @remark The movements throughout the curve are of relative type.
     */
    INTERCEPTION_API void move_mouse_to(const point& to, const curve_params* curve = nullptr);

    /**
     * @brief Sets the mouse position to the point on the screen.
     *
     * @param pos The point to set the mouse to, consisting of (x, y) coordinates.
     *
     * @remark The singular movement is of absolute type.
     */
    INTERCEPTION_API void set_mouse_pos(const point& pos);
}
