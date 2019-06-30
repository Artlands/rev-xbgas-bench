/* _xBGAS_gather.c__
 *
 * Copyright (C) 2017-2018 Tactical Computing Laboratories, LLC
 * All Rights Reserved
 * contact@tactcomplabs.com
 *
 * This file is a part of the XBGAS-RUNTIME package.  For license
 * information, see the LICENSE file in the top level directory
 * of the distribution.
 *
 */

#include <stdio.h>
#include <inttypes.h>
#include "xbrtime.h"
#include "test.h"



int main( int argc, char **argv ){
	/* vars */
  int 			rtn 			= 0;
  size_t 		sz 				= _XBGAS_ALLOC_SIZE_;
  size_t 		ne 				= _XBGAS_ALLOC_NELEMS_;
	size_t		pe				= 0;
	int64_t		target		= 0;
	int64_t		index			= 0;
	int64_t 	*idx     	= NULL;
  uint64_t 	i   			= 0;
  uint64_t 	*private  = NULL;
	uint64_t 	*shared  	= NULL;
	/* statistic gathering var */
	double		local			= 0;
	double		remote		= 0;
	double 		t_init	  = 0;
	double 		t_mem	  	= 0;
	double 		t_start  	= 0;
	double 		t_end  		= 0;

	t_start = mysecond();
	/* init */
	private = malloc( sizeof( uint64_t ) * ne );
	idx  		= malloc( sizeof( int64_t ) * ne );

  rtn 	= xbrtime_init();
  shared = (uint64_t *)(xbrtime_malloc( sz*ne ));

#ifdef DEBUG
  printf( "PE=%d; *SHARED = 0x%"PRIu64"\n", xbrtime_mype(), (uint64_t)(shared) );
#endif
	srand(1);
	pe		=	xbrtime_num_pes();
 	for( i = 0; i< ne; i++ ){
		idx[i] 			= (uint64_t)(rand()%(pe*ne-1));
		shared[i] 	= (uint64_t)(xbrtime_mype());
		private[i] 	= 99;
	}

  /* perform a barrier */
#ifdef DEBUG
  printf( "PE=%d; EXECUTING BARRIER\n", xbrtime_mype() );
#endif
  xbrtime_barrier();

	if(xbrtime_mype() == 0){
		t_end = mysecond();
		t_init = t_end - t_start;
		printf("=========================\n");
		printf(" xBGAS Gather Benchmark\n");
		printf("=========================\n");
		printf("Data size       = %d Bytes\n", (int)(sz) * (int)(ne) );
		printf("Element #       = %d\n", ne);
		printf("PE #            = %d\n", pe);
		//printf("------------------------------------------\n");
		t_start = mysecond();
	}



	/* Gathering */
  for(i = 0; i < ne; i++){
		target = idx[i]/ne;
		index  = idx[i] - target*ne;
		// private access
		if(target == xbrtime_mype()){
			private[i] = shared[index];
			local++;
		}
		// remote access
		else{
    	xbrtime_ulonglong_get((unsigned long long *)(&(private[i])),								// dest
                          	(unsigned long long *)(&(shared[index])),							// src
                          	1,																										// ne
                          	1,																										// stride
                          	target); 																							// pe
			remote++;
		}
	}
  /* perform a barrier */
#ifdef DEBUG
  printf( "PE=%d; EXECUTING BARRIER\n", xbrtime_mype() );
#endif
  xbrtime_barrier();

	if(xbrtime_mype() == 0){
		t_end = mysecond();
		t_mem = t_end - t_start;
	}
#ifdef DEBUG
  printf( "PE=%d; SHARED[0]=0x%"PRIu64"\n",
          xbrtime_mype(), shared[0]);
  printf( "PE=%d; xBGAS is Closing\n", xbrtime_mype() );
#endif


	if(xbrtime_mype() == 0)
		PRINT(local, remote, t_init, t_mem);

	free(private);
	free(idx);
  xbrtime_free( shared );
  xbrtime_close();

#ifdef DEBUG
  printf( "xBGAS is Closed\n" );
#endif

  return rtn;
}

/* EOF */
