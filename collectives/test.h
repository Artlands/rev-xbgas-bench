/* _xBGAS_test.h__
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

#include <sys/time.h>

/*color print*/
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"
#define BBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BRED     "\033[1m\033[31m"      /* Bold Red */
#define BGRN   "\033[1m\033[32m"      /* Bold Green */
#define BYEL  "\033[1m\033[33m"      /* Bold Yellow */
#define BBLU    "\033[1m\033[34m"      /* Bold Blue */
#define BMAG "\033[1m\033[35m"      /* Bold Magenta */
#define BCYN    "\033[1m\033[36m"      /* Bold Cyan */
#define BWHT   "\033[1m\033[37m"      /* Bold White */


#define _XBGAS_ALLOC_SIZE_ 8
#define _XBGAS_ALLOC_NELEMS_ 1024

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>
#include <sys/types.h>

																								        static long
																												       perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
																															                        int cpu, int group_fd, unsigned long flags)
																															        {
																																				           int ret;

																																									            ret = syscall(__NR_perf_event_open, hw_event, pid, cpu,
																																															                          group_fd, flags);
																																															           return ret;
																																																				        }





 struct perf_event_attr pe2;
 long long  cnt = 0;
 int fd1;
 long long  total_cnt = 0;
 int iter_test = 1;
 void perf_init(){

 memset(&pe2, 0, sizeof(struct perf_event_attr));
 pe2.type = PERF_TYPE_HARDWARE;
 pe2.size = sizeof(struct perf_event_attr);
 pe2.config = PERF_COUNT_HW_INSTRUCTIONS;
 pe2.disabled = 1;
 pe2.exclude_kernel = 1;
 pe2.exclude_hv = 1;
 fd1 = perf_event_open(&pe2, 0, -1, -1, 0);
 if (fd1 == -1) {
   fprintf(stderr, "Error opening leader %llx\n", pe2.config);
    exit(EXIT_FAILURE);
 }

}

void perf_end(){
 		printf("Used %lld instructions\n", total_cnt);
		close(fd1);

}


void test_start()
{

	ioctl(fd1, PERF_EVENT_IOC_RESET, 0); 
 ioctl(fd1, PERF_EVENT_IOC_ENABLE, 0); 


}
void test_end()
{
 ioctl(fd1, PERF_EVENT_IOC_DISABLE, 0); 
 read(fd1, &cnt, sizeof(long long));
 total_cnt+=cnt;
 //printf("section checker: %lld instructions\n", cnt);
 cnt = 0;
 //printf("Used %lld instructions\n", total_cnt);
 //close(fd1);


}


double mysecond() {
	  struct timeval tp;
		//struct timezone tzp;
		int i = 0;
		i = gettimeofday( &tp, NULL );
		return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}


void PRINT(double local, double remote, double t_init, double t_mem){
	size_t			ne  				= _XBGAS_ALLOC_NELEMS_;
	int64_t 		i  					= 0;
	int64_t 		percent			= 0;

	percent = (int64_t)(100*remote/ne);
	printf("Time.init       = %f sec\n", t_init);	
	printf("Time.transfer   = %f sec\n", t_mem);
	printf("Remote Access   = " BRED "%.3f%%  " RESET, 100*remote/ne);
	printf("\n");
	printf("Local  Access   = " BGRN "%.3f%%  " RESET, 100*local/ne);
	printf("\n");
	printf("------------------------------------------\n");
	printf("Request Distribution:  [");
	for(i = 0; i < percent; i++)
		printf(BRED "|" RESET);
	for(i = 0; i < 100 - percent; i++)
		printf(BGRN "|" RESET);
	printf("]\n");
	printf("------------------------------------------\n");

}

