
/* _xBGAS_kmeans.c__
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
#include <stdlib.h>
#include <math.h>
#include "xbrtime.h"
#include "test.h"

/*i and j are index of array cluster_assign*/
double euclidean(uint64_t i, uint64_t j, double* data, double* cluster_center){
	/*dim is constant set as 8 in main()*/
	double 	tmp = 0.0;
	int    	ni  = 0;
	int	nj  = 0;
	for( ni = i*8, nj = j*8 ; ni < (i+1)*8; ni++,nj++){
		tmp += (data[ni]-cluster_center[nj])* (data[ni]-cluster_center[nj]);
	}
	tmp = sqrt(tmp);
	return tmp;
}

void centroid(double* data, int n, int k, int i, int flag, double* center)
{
	int 	j;
	int 	dim = 8;
	for(j = flag*dim, i = i*dim; j < (flag+1)*dim; j++, i++ )
		center[j] += data[i];
}

void kmeans_iter(double*  center, double* data, int n,int k, uint64_t *cluster_assign, double* cluster_center,uint64_t* cluster_size, int myid)
{
	int	i;
	int 	j;
	int	flag;
	double	dist	= 2;
	double 	tmp	= 0.0;
	int 	size	= xbrtime_num_pes();

	/*----calculate the distance to each center for each local point*/
	for (i = myid*n/size; i < (myid+1)*n/size; i++){
		for(j = 0; j < k; j++){
			tmp = euclidean(i, j, data, cluster_center);
			if (dist > tmp){
				dist = tmp;
				flag = j;
			}
		}
		dist = 2;
		cluster_assign[i]  = flag;
		cluster_size[flag] += 1;
		centroid(data, n, k, i, flag, center);
	}
}

int kmeans(int dim, int n, double* data, int k, uint64_t *cluster_assign, double* cluster_center, uint64_t* cluster_size, int myid)
{
	double	*center = xbrtime_malloc(sizeof(double)*dim*k);
	double	precen[dim*k];
	double  buffer[dim*k];
	uint64_t  buffer2[k];
	uint64_t 	buffer3[n];
	int			i, j;
	int 		*flag			= NULL;
	int 		index			= 0;
	double	tmp[dim];
	double	dist 			= 0.0;
	double 	dist_last	= 0.0;
	double  threshold = 1/1000000;
	uint64_t	temp[k];

	flag 	= (int*)(xbrtime_malloc( sizeof(int) ));
	*flag =	-k;
	temp_barrier();
	if(myid == 0){
		/*---init previous centroid-----*/
		for(j = 0; j < dim*k; j++)
			precen[j] = cluster_center[j];
	}

	for(j = 0; j < n; j++)
		cluster_assign[j] = 0;
	while(*flag != 0){
		*flag	=	-k;
		/*---init cluster sizes as 0---*/
		for(i = 0; i < k; i++){
			cluster_size[i] = 0;
		}
		/*-----update last distance----*/
		dist_last = dist;
		/*----init center[] to zero----*/
		for(j = 0; j < dim*k; j++)
			center[j] = 0.0;

		kmeans_iter(center, data, n , k, cluster_assign, cluster_center, cluster_size, myid);

		if(myid == 0){
		  xbrtime_double_get((double *)(&buffer),   					// dest
				                    (double *)(center),   				// src
				    							  dim*k, 				                         		// ne
														1,                                        // stride
														1);					                              // pe

			for( i = 0; i < k*dim; i ++)
				buffer[i]  += center[i];

		  xbrtime_double_get((double *)(&buffer2),   				// dest
				                    (double *)(cluster_size),   		// src
				    							  k, 				                            		// ne
														1,                                        // stride
														1);					                              // pe

			for( i = 0; i < k; i++ )
				buffer2[i]  += cluster_size[i];

		}
		temp_barrier();

		if(myid == 0){
			/*---update previous centroid----*/
			for(j = 0; j < dim*k; j++){
				center[j] = buffer[j];
				precen[j] = cluster_center[j];
			}
			for(j = 0; j < k; j++)
				cluster_size[j] = buffer2[j];
			/*---calcalate the centroids---*/
			for(i = 0; i < k*dim; i++){
				index 		  = 	i/dim;
				center[i]	  /= 	(double)cluster_size[index];
				cluster_center[i] = 	center[i];
			}
			dist	=	0;
			/*calculate the distance between 2 centers*/
			for(i = 0; i < k; i++){
				for(j = 0; j < dim; j++){
					dist +=sqrt((center[i*dim+j] - precen[i*dim+j])*(center[i*dim+j] - precen[i*dim+j]));
				}
				if(sqrt((dist-dist_last)*(dist-dist_last)) <= threshold)
					*flag += 1;
			}
		}
		if(myid == 0){
		  xbrtime_double_put((double *)(cluster_center),   // dest
				                    (double *)(cluster_center),   // src
				    							  k*dim, 				                            // ne
														1,                                        // stride
														1);					                              // pe


		  xbrtime_int_put((int *)(flag),   					// dest
				                    ( int *)(flag),   					// src
				    							  1,		 				                            // ne
														1,                                        // stride
														1);					                              // pe

		}
		temp_barrier();
	}

	if(myid == 0){
		  xbrtime_ulonglong_get((unsigned long long *)(buffer3),   				// dest
				                    (unsigned long long *)(cluster_assign),   // src
				    							  n,		 				                            // ne
														1,                                        // stride
														1);					                              // pe

			for(i = 0; i < n; i++)
				if(cluster_assign[i] < buffer3[i])
					cluster_assign[i] = buffer3[i];
	}
	temp_barrier();
	xbrtime_free( flag );
	xbrtime_free( center );
	return 0;
}

int main(int argc,char *argv[])
{
	int 			dim							= 8;
	int 			n 							= 500;
	int 			k								= atoi(argv[1]);
	int 			i 							= 0;
	int			  j								= 0;
	int 			myid						= 0;
	int				flag						= 0;
	double		sse							= 0;
	double  	*data 					= NULL;
	double 		t_start  				= 0;
	double 		t_end  					= 0;
	double 		*cluster_center	= NULL;
	size_t  	sz 							= 8; 			// 64-bit uint64_t/double
	uint64_t 	*cluster_assign = NULL;
	uint64_t	*cluster_size		= NULL;



	if(argc>=3){
		printf("error occured in number of input variables\n");
		return 0;
	}

	/*------init------*/
	xbrtime_init();
	data 						= (double*)(xbrtime_malloc( sz*n*dim ));
	cluster_center 	= (double*)(xbrtime_malloc( sz*k*dim ));
	cluster_assign	= (uint64_t*)(xbrtime_malloc( sz*n ));
	cluster_size		= (uint64_t*)(xbrtime_malloc( sz*k ));
	myid 						= xbrtime_mype();


	/*------set random data------*/
	srand(1);
	for (i = 0; i < n*dim; i++){
		data[i] 	= (double)rand()/(double)RAND_MAX;
	}
	/*---init cluster centers as first k points in data[]*/
	for(i = 0; i < k*dim; i++){
		cluster_center[i] = data[i];
	}

	temp_barrier();
	if(myid == 0 ){
		printf("=========================\n");
		printf(" xBGAS K-means Benchmark\n");
		printf("=========================\n");
		t_start = mysecond();
	}

	kmeans( dim, n,  data, k, cluster_assign, cluster_center, cluster_size, myid);

	/*---print the completed cluster_center[]---*/
	if(myid == 0){
		t_end = mysecond();
		printf("Data size       = %d Bytes\n", n*sz);
		printf("Dimention       = %d\n", dim);
		printf("Element #       = %d\n", n);
		printf("Cluster #       = %d\n", k);
		printf("PE #            = %d\n", xbrtime_num_pes());
		printf("Time cost       = %f sec\n", t_end - t_start);
		printf("------------------------------------------\n\n");
		for(i = 0; i < k; i++){
			printf("cluster_center[%d] = ", i);
			for(j = 0; j < dim; j++)
				printf("  %f", cluster_center[i*dim+j]);
			printf("\n\n");
		}
		printf("------------------------------------------\n\n");
		for(i = 0; i < k; i++)
			printf("cluster_size[%d] = %d\n\n", i, cluster_size[i]);
		printf("------------------------------------------\n");

		for(i = 0; i < n; i++){
			flag = cluster_assign[i];
			for(j = 0; j < 8; j++)
				sse += (data[i*dim+j]-cluster_center[flag*dim+j])*(data[i*dim+j]-cluster_center[flag*dim+j]);
		}

	}
	temp_barrier();
	xbrtime_free( data );
	xbrtime_free( cluster_center );
	xbrtime_free( cluster_size );
	xbrtime_free( cluster_assign );
	xbrtime_close();

	return 0;
}
