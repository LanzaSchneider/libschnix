#ifndef LIBSCHNIX_SYSTEMS
#define LIBSCHNIX_SYSTEMS

#include <stdint.h>

typedef struct {
	// Manager
	int(*install)(void* argv, int argc);
	void(*uninstall)();
	// System
	const char*(*get_implemention_name)();
	const char*(*get_cpu_info)();
	size_t(*get_ram_size)();
	uint64_t(*get_tick_count)();
	void(*sleep)(size_t ms);
	// Window
	void(*message)(const char* text);
	void(*set_title)(const char* title);
	// Graphics
	const char*(*get_graphics_driver)();
	int(*get_hardware_resolution)(int* width, int* height);
	int(*set_background_type)(int enable_background);
	int(*initialize_graphics)(size_t width, size_t height);
	void(*dispose_graphics)();
	int(*resize_graphics)(size_t width, size_t height);
	void(*flip_buffer)();
	void(*vsync)();
	// Audio
	int(*initialize_audio)();
	void(*dispose_audio)();
	int(*get_hardware_volume)(float* volume);
	int(*set_hardware_volume)(float volume);
} schnix_systems_base_table_t;

extern schnix_systems_base_table_t	schnix_systems_base_table;

#endif