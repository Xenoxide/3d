#include "matrix.h"

VECTOR CUBE_points[8] = {
    (VECTOR) {{0,0,0}},
    (VECTOR) {{0,0,1}},
    (VECTOR) {{0,1,0}},
    (VECTOR) {{0,1,1}},
    (VECTOR) {{1,0,0}},
    (VECTOR) {{1,0,1}},
    (VECTOR) {{1,1,0}},
    (VECTOR) {{1,1,1}}
};

#define CUBE_NUM_points 8

VECTOR_2_INT CUBE_lines[8] = {
    (VECTOR_2_INT) {{0,1}},
    (VECTOR_2_INT) {{2,3}},
    (VECTOR_2_INT) {{6,7}},
    (VECTOR_2_INT) {{4,5}},
    (VECTOR_2_INT) {{3,7}},
    (VECTOR_2_INT) {{1,5}},
    (VECTOR_2_INT) {{0,4}},
    (VECTOR_2_INT) {{2,6}}
};

#define CUBE_NUM_lines 8