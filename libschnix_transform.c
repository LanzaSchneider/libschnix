#include "libschnix_transform.h"
#include <math.h>

#define MATRIX_LEN 16

// Calculate
void add(const schnix_transform_t* transform, const schnix_transform_t* transform2, schnix_transform_t* dest) {
	int i = 0;
	for (;i < MATRIX_LEN; i++) {
		dest->m[i] = transform->m[i] + transform2->m[i];
	}
}

void add_scalar(const schnix_transform_t* transform, const float scalar, schnix_transform_t* dest) {
	int i = 0;
	for (;i < MATRIX_LEN; i++) {
		dest->m[i] = transform->m[i] + scalar;
	}
}

void multiply(const schnix_transform_t* transform, const schnix_transform_t* transform2, schnix_transform_t* dest) {
	float* product = dest->m;
	const float* m1 = transform->m;
	const float* m2 = transform2->m;
	product[0]  = m1[0] * m2[0]  + m1[4] * m2[1] + m1[8]   * m2[2]  + m1[12] * m2[3];
    product[1]  = m1[1] * m2[0]  + m1[5] * m2[1] + m1[9]   * m2[2]  + m1[13] * m2[3];
    product[2]  = m1[2] * m2[0]  + m1[6] * m2[1] + m1[10]  * m2[2]  + m1[14] * m2[3];
    product[3]  = m1[3] * m2[0]  + m1[7] * m2[1] + m1[11]  * m2[2]  + m1[15] * m2[3];
    
    product[4]  = m1[0] * m2[4]  + m1[4] * m2[5] + m1[8]   * m2[6]  + m1[12] * m2[7];
    product[5]  = m1[1] * m2[4]  + m1[5] * m2[5] + m1[9]   * m2[6]  + m1[13] * m2[7];
    product[6]  = m1[2] * m2[4]  + m1[6] * m2[5] + m1[10]  * m2[6]  + m1[14] * m2[7];
    product[7]  = m1[3] * m2[4]  + m1[7] * m2[5] + m1[11]  * m2[6]  + m1[15] * m2[7];
    
    product[8]  = m1[0] * m2[8]  + m1[4] * m2[9] + m1[8]   * m2[10] + m1[12] * m2[11];
    product[9]  = m1[1] * m2[8]  + m1[5] * m2[9] + m1[9]   * m2[10] + m1[13] * m2[11];
    product[10] = m1[2] * m2[8]  + m1[6] * m2[9] + m1[10]  * m2[10] + m1[14] * m2[11];
    product[11] = m1[3] * m2[8]  + m1[7] * m2[9] + m1[11]  * m2[10] + m1[15] * m2[11];
    
    product[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8]  * m2[14] + m1[12] * m2[15];
    product[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9]  * m2[14] + m1[13] * m2[15];
    product[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
    product[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
}

void multiply_scalar(const schnix_transform_t* transform, const float scalar, schnix_transform_t* dest) {
	int i = 0;
	for (;i < MATRIX_LEN; i++) {
		dest->m[i] = transform->m[i] * scalar;
	}
}

// Transformation
void transform_vector(const schnix_transform_t* transform, const float vector[3], float dest[3]) {
	const float* m = transform->m;
	float x = vector[0], y = vector[1], z = vector[2];
	dest[0] = x * m[0] + y * m[4] + z * m[8];// + w * m[12];
    dest[1] = x * m[1] + y * m[5] + z * m[9];// + w * m[13];
    dest[2] = x * m[2] + y * m[6] + z * m[10];// + w * m[14];
}

void normalize(schnix_transform_t* dest) {
	int i = 0;
	for (;i < MATRIX_LEN; i++) {
		dest->m[i] = (i % 5 == 0) ? 1 : 0;
	}
}

// Decompose
void decompose(const schnix_transform_t* transform, float scale[3], float rotation[4], float translation[3]) {
	translation[0] = transform->m[12];
	translation[1] = transform->m[13];
	translation[2] = transform->m[14];
	
	float xaxis[3] = {transform->m[0], transform->m[1], transform->m[2]};
	float yaxis[3] = {transform->m[4], transform->m[5], transform->m[6]};
	float zaxis[3] = {transform->m[8], transform->m[9], transform->m[10]};
	
	float scaleX = scale[0] = sqrt(xaxis[0] * xaxis[0] + xaxis[1] * xaxis[1] + xaxis[2] * xaxis[2]);
	float scaleY = scale[1] = sqrt(yaxis[0] * yaxis[0] + yaxis[1] * yaxis[1] + yaxis[2] * yaxis[2]);
	float scaleZ = scale[2] = sqrt(zaxis[0] * zaxis[0] + zaxis[1] * zaxis[1] + zaxis[2] * zaxis[2]);
	
	float rn;

    rn = 1.0f / scaleX;
    xaxis[0] *= rn;
    xaxis[1] *= rn;
    xaxis[2] *= rn;

    rn = 1.0f / scaleY;
    yaxis[0] *= rn;
    yaxis[1] *= rn;
    yaxis[2] *= rn;

    rn = 1.0f / scaleZ;
    zaxis[0] *= rn;
    zaxis[1] *= rn;
    zaxis[2] *= rn;
	
	float trace = xaxis[0] + yaxis[1] + zaxis[2] + 1.0f;

#define MATH_EPSILON                0.000001f
	
    if (trace > MATH_EPSILON)
    {
        float s = 0.5f / sqrt(trace);
        rotation[3] = 0.25f / s;
        rotation[0] = (yaxis[2] - zaxis[1]) * s;
        rotation[1] = (zaxis[0] - xaxis[2]) * s;
        rotation[2] = (xaxis[1] - yaxis[0]) * s;
    }
    else
    {
        // Note: since xaxis, yaxis, and zaxis are normalized, 
        // we will never divide by zero in the code below.
        if (xaxis[0] > yaxis[1] && xaxis[0] > zaxis[2])
        {
            float s = 0.5f / sqrt(1.0f + xaxis[0] - yaxis[1] - zaxis[2]);
            rotation[3] = (yaxis[2] - zaxis[1]) * s;
            rotation[0] = 0.25f / s;
            rotation[1] = (yaxis[0] + xaxis[1]) * s;
            rotation[2] = (zaxis[0] + xaxis[2]) * s;
        }
        else if (yaxis[1] > zaxis[2])
        {
            float s = 0.5f / sqrt(1.0f + yaxis[1] - xaxis[0] - zaxis[2]);
            rotation[3] = (zaxis[0] - xaxis[2]) * s;
            rotation[0] = (yaxis[0] + xaxis[1]) * s;
            rotation[1] = 0.25f / s;
            rotation[2] = (zaxis[1] + yaxis[2]) * s;
        }
        else
        {
            float s = 0.5f / sqrt(1.0f + zaxis[2] - xaxis[0] - yaxis[1]);
            rotation[3] = (xaxis[1] - yaxis[0] ) * s;
            rotation[0] = (zaxis[0] + xaxis[2] ) * s;
            rotation[1] = (zaxis[1] + yaxis[2] ) * s;
            rotation[2] = 0.25f / s;
        }
    }
}


/* External */

schnix_transform_method_table_t		schnix_transform_method_table = {
	add, add_scalar, multiply, multiply_scalar, transform_vector, normalize, decompose
};























