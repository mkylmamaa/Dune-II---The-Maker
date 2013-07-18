#pragma once
/*
 * allegroh.h
 *
 *  Created on: 7-nov-2010
 *      Author: Stefan
 */

#ifndef ALLEGROH_H_
#define ALLEGROH_H_

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// ALLEGRO
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Allegro: must be after any default headers...
#include <allegro.h>


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// ALLEGRO ADD-ONS
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#ifndef UNIX
#  define ALFONT_DLL
#  define ALMP3_DLL
#endif

#include <alfont.h>
#include <almp3.h>

// Needed by fblend (fast blending techniques (3 - 10 times faster than
// default Allegro routines)
#include "fblend.h"
#include "sse.h"
#include "mmx.h"

#endif /* ALLEGROH_H_ */