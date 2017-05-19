## Logger [![](https://api.travis-ci.org/SirJls/logger.svg)](https://travis-ci.org/SirJls/logger)

Logger is a simple C library that aims to make general logging easy. It
does this by letting you specify different [priorities](http://www.github.com/SirJls/logger.git#priorities)

## Priorities ##

Logger lets you specify one of the following priorities:

  * `SILENT`: No messages
  * `ERROR`: Error messages, colored red
  * `WARNING`: Warning messages, colored yellow
  * `NOTICE`: Normal but significant messages, colored blue
  * `INFO`: Informational messages, colored magenta
  * `DEBUG`: Debugging messages, colored cyan

## Logging ##

Logger let's you log messages by calling `logger_log(priority, msg)`. This will
write out the current filename with line number to the log.

## Assertions ##

Logger also supports assertions. To perform an assertion just call
`logger_assert(condition, msg)`. This wil evaluate the assertion resulting in a
return `condition` that you must handle if false.

## Locale ##

Logger uses the standard C library `strftime()` function to format a date based
on your current locale. If the format isn't what you expected make sure that
the standard locale environment variables `LC_TIME` or `LC_ALL` are correct.
If not defined  the system will fall back on the _"C"_ default.

__Example formatted output:__
  * `en_US.UTF-8`
    * 05/20/2017 00:00:00 PM - [\<File\>:\<Line Number\>] \<Your Message\>
  * `nl_NL.UTF-8`
    * 20-05-17 00:00:00 - [\<File\>:\<Line Number\>] \<Your Message\>

## Installation ##

### Building from source ###

__Dependencies:__
  * cmake
  * git

To build run the following commands:

    mkdir build && cd build
    cmake ..
    make
    sudo make install

## Releases ##

Releases are signed with with 36BEBC5B
