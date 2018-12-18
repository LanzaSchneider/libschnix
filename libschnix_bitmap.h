#ifndef LIBSCHNIX_BITMAP
#define LIBSCHNIX_BITMAP

#include <stdint.h>
#include <stdio.h>

typedef struct schnix_bitmap_t schnix_bitmap_t;

typedef struct {
	// Manager
	schnix_bitmap_t*(*create)(size_t width, size_t height);
	void(*dispose)(schnix_bitmap_t* bitmap);
	// Parameter
	size_t(*width)(schnix_bitmap_t* bitmap);
	size_t(*height)(schnix_bitmap_t* bitmap);
	// Unit Operator
	uint32_t(*get_pixel)(schnix_bitmap_t* bitmap, int x, int y);
	void(*set_pixel)(schnix_bitmap_t* bitmap, int x, int y, uint32_t color);
	void*(*get_data)(schnix_bitmap_t* bitmap);
	// Blit
	void(*blit)(schnix_bitmap_t* bitmap, schnix_bitmap_t* dest_bitmap, int x, int y, int src_x, int src_y, int width, int height, int opacity);
	void(*stretch_blt)(schnix_bitmap_t* bitmap, schnix_bitmap_t* dest_bitmap, int x, int y, int width, int height, int src_x, int src_y, int src_width, int src_height, int opacity);
	void(*masked_blit)(schnix_bitmap_t* bitmap, schnix_bitmap_t* dest_bitmap, int x, int y, int src_x, int src_y, int width, int height, int opacity);
	void(*masked_stretch_blt)(schnix_bitmap_t* bitmap, schnix_bitmap_t* dest_bitmap, int x, int y, int width, int height, int src_x, int src_y, int src_width, int src_height, int opacity);
} schnix_bitmap_method_base_table_t;

typedef struct {
	// Draw Functions
	void(*draw_line)(schnix_bitmap_t* bitmap, int x1, int y1, int x2, int y2, int width, uint32_t color);
	void(*draw_rect)(schnix_bitmap_t* bitmap, int x, int y, int width, int height, uint32_t color);
	void(*fill_rect)(schnix_bitmap_t* bitmap, int x, int y, int width, int height, uint32_t color);
	void(*draw_circle)(schnix_bitmap_t* bitmap, int x, int y, int radius, uint32_t color);
	void(*fill_circle)(schnix_bitmap_t* bitmap, int x, int y, int radius, uint32_t color);
	void(*clear)(schnix_bitmap_t* bitmap);
	void(*clear_to_color)(schnix_bitmap_t* bitmap, uint32_t color);
	void(*replace_color)(schnix_bitmap_t* bitmap, uint32_t color1, uint32_t color2);
} schnix_bitmap_method_table_t;

extern schnix_bitmap_method_base_table_t	schnix_bitmap_method_base_table;
extern schnix_bitmap_method_table_t 		schnix_bitmap_method_table;

#endif