#ifndef _LOGGER_LOG_H
#define _LOGGER_LOG_H

#include <stdbool.h>
#include <stddef.h>

typedef enum {
	SILENT  = 0,
	ERROR   = 1,
	WARNING = 2,
	NOTICE  = 3,
	INFO    = 4,
	DEBUG   = 5,
} logger_priority_t;

typedef enum {
	OFF = 0,
	ON  = 1,
} logger_colors_t;

void logger_init(logger_priority_t priority);
void logger_set_priority(logger_priority_t priority);
void logger_toggle_colors(logger_colors_t mode);
logger_priority_t logger_get_priority(void);
size_t _localtime(char *buf, size_t size);

void _logger_abort(const char *filepath, int line, const char* format, ...)
	__attribute__((format(printf,3,4)));
#define logger_abort(FMT, ...)	\
	_logger_abort(__FILE__, __LINE__, FMT, ##__VA_ARGS__)

void _logger_log(const char *filepath, int line, logger_priority_t priority,
		const char *format, ...) __attribute__((format(printf,4,5)));
#define logger_log(PRIORITY, FMT, ...)	\
	_logger_log(__FILE__, __LINE__, PRIORITY, FMT, ##__VA_ARGS__)

bool _logger_assert(bool condition, const char *filepath, int line,
		const char *format, ...) __attribute__((format(printf,4,5)));
#define logger_assert(COND, FMT, ...) \
	_logger_assert(COND, __FILE__, __LINE__, "%s: " FMT, \
		__PRETTY_FUNCTION__, ##__VA_ARGS__)

#endif /* ifndef _LOGGER_LOG_H */
