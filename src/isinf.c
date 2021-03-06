/*
 * isinf function
 *
 * Copyright 2008 Petr Sumbera
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

#include "wine/config.h"
#include "wine/port.h"

#if !defined(HAVE_ISINF) && !defined(isinf)

#ifdef HAVE_IEEEFP_H
#include <ieeefp.h>

int isinf(double x)
{
  return (!(finite(x) || isnand(x)));
}

#else
#error No isinf() implementation available.
#endif

#endif /* HAVE_ISINF */
