/*
 * rint family
 *
 * Copyright 2017 Alex Henrie
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "config.h"
#include "wine/port.h"

#include <math.h>

#ifndef HAVE_RINT
double rint(double x)
{
    return x >= 0 ? floor(x + 0.5) : ceil(x - 0.5);
}
#endif

#ifndef HAVE_RINTF
float rintf(float x)
{
    return rintf(x);
}
#endif

#ifndef HAVE_LRINT
long lrint(double x)
{
    return x >= 0 ? floor(x + 0.5) : ceil(x - 0.5);
}
#endif

#ifndef HAVE_LRINTF
long lrintf(float x)
{
    return lrint(x);
}
#endif

#ifndef HAVE_LLRINT
__int64 llrint(double x)
{
    return x >= 0 ? floor(x + 0.5) : ceil(x - 0.5);
}
#endif

#ifndef HAVE_LLRINTF
__int64 llrintf(float x)
{
    return llrint(x);
}
#endif
