#define _POSIX_C_SOURCE 1
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>

#include "log.h"

static const char *logger_priority_colors[] = {
	[SILENT]    = "",
	[ERROR]   = "\x1b[31m", // red
	[WARNING] = "\x1b[33m", // yellow
	[NOTICE]  = "\x1b[34m", // blue
	[INFO]    = "\x1b[35m", // magenta
	[DEBUG]   = "\x1b[36m", // cyan
};

static logger_priority_t p    = SILENT;
static logger_colors_t colors = ON;

void logger_init(logger_priority_t priority)
{
	p = priority;
}

void logger_set_priority(logger_priority_t priority)
{
	p = priority;
}

void logger_toggle_colors(logger_colors_t mode)
{
	colors = (colors == ON) ? OFF : ON;
}

logger_priority_t logger_get_priority()
{
	return p;
}

size_t _localtime(char *buf, size_t size)
{
	static time_t raw_t;
	static struct tm result;

	setlocale(LC_ALL, "");
	raw_t = time(NULL);
	localtime_r(&raw_t, &result);
	return strftime(buf, size, "%x %X - ", &result);
}

void _log(const char *filepath, int line, logger_priority_t priority,
		const char *format, va_list args)
{
	if (priority <= p) {
		char buf[26];
		_localtime(buf, 26);
		fprintf(stderr, "%s", buf);

		unsigned int c = priority;
		if (isatty(STDERR_FILENO) && colors)
			fprintf(stderr, "%s", logger_priority_colors[c]);

		if (filepath && line) {
			const char *file = filepath + strlen(filepath);
			while (file != filepath && *file != '/')
				--file;
			if (*file == '/')
				++file;
			fprintf(stderr, "[%s:%d] ", file, line);
		}

		vfprintf(stderr, format, args);

		if (isatty(STDERR_FILENO) && colors)
			fprintf(stderr, "\x1b[0m");

		fprintf(stderr, "\n");
	}
}

bool _logger_assert(bool condition, const char *filepath, int line,
		const char *format, ...)
{
	if (condition)
		return true;

	va_list args;
	va_start(args, format);
	_log(filepath, line, ERROR, format, args);
	va_end(args);

	#ifndef NDEBUG
		raise(SIGABRT);
	#endif

	return false;
}

void _logger_log(const char *filepath, int line, logger_priority_t priority,
		const char *format, ...)
{
	va_list args;
	va_start(args, format);
	_log(filepath, line, priority, format, args);
	va_end(args);
}

void _logger_abort(const char *filepath, int line, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	_log(filepath, line, ERROR, format, args);
	va_end(args);
	exit(EXIT_FAILURE);
}
