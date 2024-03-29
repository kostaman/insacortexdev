
/*
FUNCTION
	<<isblank>>---blank character predicate

INDEX
	isblank

ANSI_SYNOPSIS
	#include <ctype.h>
	int isblank(int <[c]>);

TRAD_SYNOPSIS
	#include <ctype.h>
	int isblank(<[c]>);

DESCRIPTION
<<isblank>> is a function which classifies ASCII integer values by table
lookup.  It is a predicate returning non-zero for blank characters, and 0
for other characters.

RETURNS
<<isblank>> returns non-zero if <[c]> is a blank character.

PORTABILITY
<<isblank>> is C99.

No supporting OS subroutines are required.
*/

#include <ctype.h>

#undef isblank
int isblank(int c)
{
	return ((c == ' ') || (c == '\t'));
}
