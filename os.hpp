#pragma once

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <time.h>
#endif
#include <cstddef>

class Mmap {
	std::size_t size_;
	char* map;
public:
	Mmap(const char* path) {
		#ifdef _WIN32
		HANDLE file = CreateFile(path, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		LARGE_INTEGER large_integer;
		GetFileSizeEx(file, &large_integer);
		size_ = large_integer.QuadPart;
		HANDLE mapping = CreateFileMapping(file, nullptr, PAGE_READONLY, 0, 0, nullptr);
		map = static_cast<char*>(MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, size_));
		CloseHandle(mapping);
		CloseHandle(file);
		#else
		const int fd = open(path, O_RDONLY);
		struct stat stat;
		fstat(fd, &stat);
		size_ = stat.st_size;
		map = static_cast<char*>(mmap(nullptr, size_, PROT_READ, MAP_PRIVATE, fd, 0));
		close(fd);
		#endif
	}
	Mmap(const Mmap&) = delete;
	~Mmap() {
		#ifdef _WIN32
		UnmapViewOfFile(map);
		#else
		munmap(map, size_);
		#endif
	}
	Mmap& operator =(const Mmap&) = delete;
	std::size_t size() const {
		return size_;
	}
	const char* data() const {
		return map;
	}
	char operator [](std::size_t i) const {
		return map[i];
	}
	const char* begin() const {
		return map;
	}
	const char* end() const {
		return map + size_;
	}
};

class Time {
public:
	static double get_monotonic() {
		#ifdef _WIN32
		static const double frequency = []() {
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			return frequency.QuadPart;
		}();
		LARGE_INTEGER count;
		QueryPerformanceCounter(&count);
		return count.QuadPart / frequency;
		#else
		struct timespec ts;
		clock_gettime(CLOCK_MONOTONIC, &ts);
		return ts.tv_sec + ts.tv_nsec / 1e9;
		#endif
	}
};
