/*
 * _BROADCAST_DEMO_C_
 *
 * Copyright (C) 2017-2019 Tactical Computing Laboratories, LLC
 * All Rights Reserved
 * contact@tactcomplabs.com
 *
 * This file is a part of the XBGAS-RUNTIME package.  For license
 * information, see the LICENSE file in the top level directory
 * of the distribution.
 *
 */

 #include "xbrtime.h"

int main()
{	
	int my_pe, *b_val;
	/* Initialize the runtime */
	xbrtime_init();
	my_pe = xbrtime_mype();

	/* Allocate a symmetric memory region */
	b_val = (int*) xbrtime_malloc(sizeof(int));

	/* Set the value to the PE number */
	*b_val = my_pe;

	printf("Pre-Broadcast - PE:%d B_Val: %d\n", 
			my_pe, *b_val);

	/* Perform a barrier*/
	xbrtime_barrier();

	if (my_pe == 4) {
		printf("Broadcasting from PE:%d, value=%d\n", 
				4, *b_val);
	}
	/* Broadcast the value from PE 4 to all other PEs */
	xbrtime_int_broadcast(b_val, b_val, 1, 1, 4);

	/* Perform a barrier*/
	xbrtime_barrier();

	printf("Post-Broadcast - PE:%d B_Val: %d\n", 
			my_pe, *b_val);

	/* Finalize the runtime */
	xbrtime_close();

	return 0;
}
