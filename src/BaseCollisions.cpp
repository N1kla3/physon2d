#include "BaseCollisions.h"


void phys2::lineToCircleCollision(vec2 start, vec2 end, vec2 sphereCenter, real_t radius)
{
#if PHYS_SIMD
    start = end;
#else
    end = start;
#endif
}
