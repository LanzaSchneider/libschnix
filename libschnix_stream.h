#ifndef LIBSCHNIX_STREAM
#define LIBSCHNIX_STREAM

#include <stdint.h>
#include <stdio.h>

typedef struct {
	int(*fclose)(uint32_t flags, void* userdata);
	size_t(*fread)(uint32_t flags, void* userdata, void* buffer, size_t size, size_t count);
	size_t(*fwrite)(uint32_t flags, void* userdata, const void* ptr, size_t size, size_t count);
	int(*feof)(uint32_t flags, void* userdata);
	void(*rewind)(uint32_t flags, void* userdata);
	int(*fseek)(uint32_t flags, void* userdata, long offset, int from_where);
	long(*ftell)(uint32_t flags, void* userdata);
	int(*ferror)(uint32_t flags, void* userdata);
	int(*fflush)(uint32_t flags, void* userdata);
	int(*fgetc)(uint32_t flags, void* userdata);
} schnix_stream_vtable_t;

typedef struct {
	schnix_stream_vtable_t* vtable;
	uint32_t flags;
	void* userdata;
} schnix_stream_t;

extern schnix_stream_vtable_t				schnix_stream_vtable_memfile;

typedef struct {
	schnix_stream_t*(*fopen)(const char* path, const char* mode);
} schnix_stream_method_base_table_t;

typedef struct {
	schnix_stream_t*(*memstream_open)(void* buffer, size_t size, int writable, int need_free);
} schnix_stream_method_table_t;

extern schnix_stream_method_base_table_t	schnix_stream_method_base_table;
extern schnix_stream_method_table_t			schnix_stream_method_table;

#endif