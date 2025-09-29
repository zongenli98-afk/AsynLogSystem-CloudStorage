#pragma once

#include <string_view>

namespace mylog {

    /**
     * @class LogLevel
     * @brief Defines logging levels and provides utilities to convert levels to text.
     *
     * This class contains an enum representing supported log levels and a
     * constexpr helper to obtain the textual name of a level. The helper
     * returns a `std::string_view` to avoid heap allocation and is marked
     * `noexcept` so it can be used in constexpr contexts.
     */
    class LogLevel {
    public:
        // Log severity levels
        enum class value { DEBUG, INFO, WARN, ERROR, FATAL };

        /**
         * Convert a log level to its string representation.
         *
         * @param level The log level to convert.
         * @return A string view containing the level name (e.g. "INFO").
         */
        static constexpr std::string_view ToString(value level) noexcept {
            switch (level) {
                case value::DEBUG: return "DEBUG";
                case value::INFO:  return "INFO";
                case value::WARN:  return "WARN";
                case value::ERROR: return "ERROR";
                case value::FATAL: return "FATAL";
            }
            return "UNKNOWN"; // fallback for unrecognized values
        }
    };

} // namespace mylog
