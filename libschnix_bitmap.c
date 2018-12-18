#include "libschnix_bitmap.h"
#include <math.h>

#define min(a, b) 	((a) > (b) ? (b) : (a))
#define abs(x)		((x) > 0 ? (x) : -(x))

static void draw_line(schnix_bitmap_t* bitmap, int x1, int y1, int x2, int y2, int width, uint32_t color) {
	if (width <= 0) return;
	if (x2 < x1) {
		int temp = x2;
		x2 = x1; x1 = temp;
		temp = y2;
		y2 = y2; y2 = temp;
	}
	float s = width * 0.5;
	if (x1 == x2)
		schnix_bitmap_method_table.fill_rect(bitmap, x1 - s, min(y1, y2), width, abs(y2 - y1), color);
	else if (y1 == y2){
		schnix_bitmap_method_table.fill_rect(bitmap, x1, y1 - s, x2 - x1, width, color);
	}
	float length = x2 - x1 < abs(y2 - y1) ? abs(y2 - y1) : (x2 - x1);
	float x_increment = (x2 - x1) / length;
	float y_increment = (y2 - y1) / length;
	float x = x1, y = y2;
	while (x < x2) {
		schnix_bitmap_method_table.fill_rect(bitmap, x - s, y - s, width, width, color);
		x += x_increment;
		y += y_increment;
	}
}

static void draw_rect(schnix_bitmap_t* bitmap, int x, int y, int width, int height, uint32_t color) {
	size_t i;
	for (i = 0; i < width; i++) {
		schnix_bitmap_method_base_table.set_pixel(bitmap, x + i, y, color);
		schnix_bitmap_method_base_table.set_pixel(bitmap, x + i, y + height, color);
	}
	for (i = 0; i < height; i++) {
		schnix_bitmap_method_base_table.set_pixel(bitmap, x, y + i, color);
		schnix_bitmap_method_base_table.set_pixel(bitmap, x + width, y + i, color);
	}
}

static void fill_rect(schnix_bitmap_t* bitmap, int x, int y, int width, int height, uint32_t color) {
	size_t i, j = 0;
	for (; j < height; j++) {
		for (i = 0; i < width; i++) {
			schnix_bitmap_method_base_table.set_pixel(bitmap, x + i, y + j, color);
		}
	}
}

static void draw_circle(schnix_bitmap_t* bitmap, int x, int y, int radius, uint32_t color) {
	int i;
	for (i = (x - radius); i <= (x + radius); i++) {
		int sa = abs(x - i);
		int x_ = i < x ? x - sa : i == x ? x : x + sa;
		int y_ = sqrt(radius * radius - sa * sa);
		schnix_bitmap_method_table.fill_rect(bitmap, x_, y - y_, 1, y_ * 2, color);
	}
}

static void fill_circle(schnix_bitmap_t* bitmap, int x, int y, int radius, uint32_t color) {
	// TODO
}

static void clear(schnix_bitmap_t* bitmap) {
	schnix_bitmap_method_table.clear_to_color(bitmap, 0);
}

static void clear_to_color(schnix_bitmap_t* bitmap, uint32_t color) {
	size_t width = schnix_bitmap_method_base_table.width(bitmap);
	size_t height = schnix_bitmap_method_base_table.height(bitmap);
	schnix_bitmap_method_table.fill_rect(bitmap, 0, 0, width, height, color);
}

static void replace_color(schnix_bitmap_t* bitmap, uint32_t color1, uint32_t color2) {
	size_t width = schnix_bitmap_method_base_table.width(bitmap);
	size_t height = schnix_bitmap_method_base_table.height(bitmap);
	int y = 0, x;
	for (y; y < height; y++) {
		for (x = 0; x < width; x++) {
			uint32_t pixel = schnix_bitmap_method_base_table.get_pixel(bitmap, x, y);
			if (pixel == color1) schnix_bitmap_method_base_table.set_pixel(bitmap, x, y, color2);
		}
	}
}

/* External */

schnix_bitmap_method_base_table_t	schnix_bitmap_method_base_table = {};

schnix_bitmap_method_table_t 		schnix_bitmap_method_table = {
	draw_line, draw_rect, fill_rect, draw_circle, fill_circle, clear, clear_to_color, replace_color
};
