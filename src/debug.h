#ifndef __debug_h__
#define __debug_h__

#include <stdio.h>
#include <error.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M,...)
#else
#define debug(M,...)    fprintf(stderr, "[DEBUG]:file:%s line_no:%d " M "\n",\
                        __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define log_err(M,...)  fprintf(stderr, "[ERROR]:file:%s line_no:%d " M "\n",\
                        __FILE__, __LINE__, ##__VA_ARGS__);
#define log_info(M,...)  fprintf(stderr, "[INFO]:file:%s line_no:%d " M "\n",\
                        __FILE__, __LINE__, ##__VA_ARGS__)
#define check(A,M,...)  if(!(A)) {log_err(M,##__VA_ARGS__);\
                        goto error;}

#endif