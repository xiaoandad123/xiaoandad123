#pragma once

template <typename... Args>
void log(const char* format, Args... args)
{
	printf(format, args...);
}

#ifndef DEBUG
#define log(...)
#endif // DEBUG