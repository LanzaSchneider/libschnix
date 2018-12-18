#ifndef LIBSCHNIX_TRANSFORM
#define LIBSCHNIX_TRANSFORM

typedef struct {
	float m[16];
} schnix_transform_t;

typedef struct {
	// Calculate
	void(*add)(const schnix_transform_t* transform, const schnix_transform_t* transform2, schnix_transform_t* dest);
	void(*add_scalar)(const schnix_transform_t* transform, const float scalar, schnix_transform_t* dest);
	void(*multiply)(const schnix_transform_t* transform, const schnix_transform_t* transform2, schnix_transform_t* dest);
	void(*multiply_scalar)(const schnix_transform_t* transform, const float scalar, schnix_transform_t* dest);
	// Transformation
	void(*transform_vector)(const schnix_transform_t* transform, const float vector[3], float dest[3]);
	void(*normalize)(schnix_transform_t* dest);
	// Decompose
	void(*decompose)(const schnix_transform_t* transform, float scale[3], float rotation[4], float translation[3]);
} schnix_transform_method_table_t;

extern schnix_transform_method_table_t			schnix_transform_method_table;

#endif