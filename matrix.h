#include <stdio.h>
#include <math.h>

#define SCALAR float
#define T 6.28

typedef struct MATRIX_MATRIX
{
    float m[3][3];
} MATRIX;

typedef struct MATRIX_VECTOR
{
    float m[3];
} VECTOR;

typedef struct MATRIX_VECTOR_2
{
    float m[2];
} VECTOR_2;

typedef struct MATRIX_VECTOR_2_INT
{
    int m[2];
} VECTOR_2_INT;

void MATRIX_PRINT(MATRIX in)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            printf("%f\t", in.m[i][j]);
        putchar('\n');
    }
    putchar('\n');
}

void MATRIX_PRINT_VECTOR(VECTOR in)
{
    int i, j;
    for (i = 0; i < 3; i++)
        printf("%f\t", in.m[i]);
    putchar('\n');
    putchar('\n');
}

void MATRIX_PRINT_VECTOR_2(VECTOR_2 in)
{
    int i, j;
    for (i = 0; i < 2; i++)
        printf("%f\t", in.m[i]);
    putchar('\n');
    putchar('\n');
}

void MATRIX_SUBTRACT_VECTOR(VECTOR left, VECTOR right, VECTOR * out)
{
    int i;
    for (i = 0; i < 3; i++)
        out->m[i] = left.m[i] - right.m[i];
}

// Multiply two 3x3 matrices left and right, output to matrix third term
void MATRIX_MXM(MATRIX left, MATRIX right, MATRIX * out)
{
    int i, j, k;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            out->m[i][j] = 0; // set to zero
            // multiplication
            for (k = 0; k < 3; k++)
                out->m[i][j] += left.m[i][k] * right.m[k][j];
        }
    }
}

// Apply a 3x3 matrix to a 3D vector, matrix left, vector right, vector out
void MATRIX_MXV(MATRIX left, VECTOR right, VECTOR * out)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        out->m[i] = 0.0;
        for (j = 0; j < 3; j++)
        {
            out->m[i] += left.m[i][j] * right.m[i];
        };
    }
}

// Get x direction rotation matrix from scalar angle, matrix out
void MATRIX_GET_ROT_X(SCALAR angle, MATRIX * out) 
{
    *out = (MATRIX){{
        { 1, 0,             0          }, 
        { 0, cos(angle), 0 -sin(angle) },
        { 0, sin(angle),    cos(angle) }
    }};
}

// Get y direction rotation matrix from scalar angle, matrix out
void MATRIX_GET_ROT_Y(SCALAR angle, MATRIX * out)
{
    *out = (MATRIX){{
        {    cos(angle), 0, sin(angle) },
        {    0,          1, 0          },
        { 0 -sin(angle), 0, cos(angle) }
    }};

}

// Get z direction rotation matrix from scalar angle, matrix out
void MATRIX_GET_ROT_Z(SCALAR angle, MATRIX * out)
{
    *out = (MATRIX){{
        { cos(angle), 0 -sin(angle), 0 },
        { sin(angle),    cos(angle), 0 },
        { 0,             0,          1 }
    }};
}

// Calculate perspective projection on x/y plane of 'point'
// VECTOR point:              Point to transform
// VECTOR camera:             Position of the camera's pinhole
// VECTOR camera_orientation: Camera direction
// VECTOR display_surface:    Relative position of the display surface to the pinhole
// VECTOR_2 * out:            Output (pass as pointer)

void MATRIX_PERSPECTIVE(VECTOR point, VECTOR camera, VECTOR camera_orientation, VECTOR display_surface, VECTOR_2 * out)
{
    MATRIX rot_x, rot_y, rot_z, rot;
    VECTOR difference, transformed;
    
    // Get rotation matrices
    MATRIX_GET_ROT_X(0 -camera_orientation.m[0], &rot_x);
    MATRIX_GET_ROT_Y(0 -camera_orientation.m[1], &rot_y);
    MATRIX_GET_ROT_Z(0 -camera_orientation.m[2], &rot_z);

    // Camera transform
    MATRIX_SUBTRACT_VECTOR(point, camera, &difference);

    // Combine matrices and apply to vector
    MATRIX_MXM(rot_x, rot_y, &rot);
    MATRIX_MXM(rot, rot_z, &rot);
    MATRIX_MXV(rot, difference, &transformed);

    // Save calculation
    float d_t = display_surface.m[2] / transformed.m[2];

    // projection plane is x/y
    // Finish perspective projection
    out->m[0] = d_t * transformed.m[0] + display_surface.m[0];
    out->m[1] = d_t * transformed.m[1] + display_surface.m[1];
}
// I give up, orthographic projection
void MATRIX_ORTHOGRAPHIC(VECTOR point, VECTOR_2 * out)
{
    *out = (VECTOR_2) {{point.m[0], point.m[1]}};
}

// Both rotate, translate, and complete a perspective projection on the point
// VECTOR point:              Point to transform
// VECTOR angles:             Three angles (x, y, z) as a vector
// VECTOR displace:           Move the point  
// VECTOR camera:             Position of the camera's pinhole
// VECTOR camera_orientation: Camera direction angles (x, y, z) as a vector
// VECTOR display_surface:    Relative position of the display surface to the pinhole
// VECTOR_2 * out:            Output (pass as pointer)
void MATRIX_FULL_TRANSFORM(VECTOR point, VECTOR displace, VECTOR angles, VECTOR_2 * out)
{
    VECTOR transformed_point = (VECTOR) 
    {{
        point.m[0] + displace.m[0],
        point.m[1] + displace.m[1],
        point.m[2] + displace.m[2]
    }};
    MATRIX rot_x, rot_y, rot_z, rot;
    MATRIX_GET_ROT_X(angles.m[0], &rot_x);
    MATRIX_GET_ROT_Y(angles.m[1], &rot_y);
    MATRIX_GET_ROT_Z(angles.m[2], &rot_z);

    MATRIX_MXM(rot_x, rot_y, &rot);
    MATRIX_MXM(rot, rot_z, &rot);

    MATRIX_MXV(rot, transformed_point, &transformed_point);
    //MATRIX_PERSPECTIVE(transformed_point, camera, camera_orientation, display_surface, out);
      MATRIX_ORTHOGRAPHIC(transformed_point, out);
    // MATRIX_PRINT_VECTOR_2(*out); debug code
}