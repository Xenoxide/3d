#include "matrix.h"

// All functions are ok (transforms were not tested)
int main(void) {

    MATRIX m1 = (MATRIX) {{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    }};
    MATRIX m2 = (MATRIX) {{
        {11, 12, 13},
        {14, 15, 16},
        {17, 18, 19}
    }};
    MATRIX i = (MATRIX) {{
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    }};
    MATRIX rot_x;
    MATRIX rot_y;
    MATRIX rot_z;
    MATRIX product;

    VECTOR v;
    VECTOR v2 = (VECTOR) {{2, 3, 5}};
    VECTOR v3 = (VECTOR) {{7, 11, 13}};

    printf("matrix 1:\n");
    MATRIX_PRINT(m1);
    printf("matrix 2:\n");
    MATRIX_PRINT(m2);
    printf("product:\n");
    MATRIX_MXM(m1, m2, &product);
    MATRIX_PRINT(product);
    printf("vector 1:\n");
    MATRIX_PRINT_VECTOR(v2);
    printf("vector 2:\n");
    MATRIX_PRINT_VECTOR(v3);
    MATRIX_SUBTRACT_VECTOR(v2, v3, &v);
    printf("difference:\n");
    MATRIX_PRINT_VECTOR(v);

    printf("identity matrix and vector 1:\n");
    MATRIX_MXV(i, v2, &v);
    MATRIX_PRINT_VECTOR(v);

    MATRIX_GET_ROT_X(0, &rot_x);
    printf("rotate x 0 degrees:\n");
    MATRIX_PRINT(rot_x);
    MATRIX_GET_ROT_Y(T / 4, &rot_y);
    printf("rotate y 90 degrees:\n");
    MATRIX_PRINT(rot_y);
    MATRIX_GET_ROT_Z(T / 2, &rot_z);
    printf("rotate z 180 degrees:\n");
    MATRIX_PRINT(rot_z);

    printf("product of two 180 degree rotations:\n");
    MATRIX rot;
    MATRIX_MXM(rot_z, rot_z, &rot);
    MATRIX_PRINT(rot);

    return 0;
}