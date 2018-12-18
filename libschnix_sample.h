#ifndef LIBSCHNIX_SAMPLE
#define LIBSCHNIX_SAMPLE

#include <stdint.h>
#include <stdio.h>

typedef struct schnix_sample_t schnix_sample_t;

typedef struct {
	// Manager
	schnix_sample_t*(*create)(uint8_t bits, uint8_t stereo, size_t frequency, size_t sample_length);
	void(*dispose)(schnix_sample_t* sample);
	// Parameter
	uint8_t(*bits)(schnix_sample_t* sample);
	uint8_t(*stereo)(schnix_sample_t* sample);
	size_t(*frequency)(schnix_sample_t* sample);
	// Unit Operator
	void*(*get_data)(schnix_sample_t* sample);
	// Playing
	size_t(*play_instance)(schnix_sample_t* sample, float volume, float pan, float pitch, int loop);
	void(*instance_adjust)(schnix_sample_t* sample, size_t instance_id, float volume, float pan, float pitch, int loop);
	void(*instance_stop)(schnix_sample_t* sample, size_t instance_id);
	void(*stop)(schnix_sample_t* sample);
} schnix_sample_method_base_table_t;

extern schnix_sample_method_base_table_t	schnix_sample_method_base_table;

#endif