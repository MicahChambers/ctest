#if !defined(SELFINCLUDE_FLOAT_H)
	#define SELFINCLUDE_FLOAT_H
	#define USE_FLOAT
	#define GO_SELFINCLUDE_H
	#define FTYPE float
#elif !define(SELFINCLUDE_DOUBLE_H)
	#define SELFINCLUDE_DOUBLE_H
	#define USE_DOUBLE
	#define GO_SELFINCLUDE_H
	#define FTYPE double
#endif

#ifdef GO_SELFINCLUDE_H

FTYPE test();

#include "selfinclude.h"
#undef GO_SELFINCLUDE_H
#endif
