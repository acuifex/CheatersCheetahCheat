#pragma once
#include <windows.h>

static char buffer[4096];
inline HANDLE log_handle;

inline void init_logger(const char* filename) {
	static bool init = false;
	if (!init){
		log_handle = CreateFile(
				filename,
				GENERIC_WRITE, FILE_SHARE_READ, NULL,
				CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		init = true;
	}

}

inline void free_logger() { CloseHandle(log_handle); }

template<typename... Args>
size_t log(const char* message, Args... args) {
	size_t len = wsprintfA(buffer, TEXT(message), args...);
	WriteFile(log_handle, buffer, len, NULL, NULL);
	return len;
}
#define LOG(msg, ...) log(msg "\n", ##__VA_ARGS__)
