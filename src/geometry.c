#include "include/geometry.h"


unsigned int rect_intersects(vec4 a, vec4 b)
{
    return (a[1] > b[0] && a[0] < b[1]) && (a[3] > b[2] && a[2] < b[3]);
}
