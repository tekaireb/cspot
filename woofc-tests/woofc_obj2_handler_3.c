#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "woofc.h"
#include "woofc-obj2.h"

int woofc_obj2_handler_3(WOOF *wf, unsigned long seq_no, void *ptr)
{

	OBJ2_EL el;
	FILE *fd;


	fd = fopen("/cspot/log-obj2","a");
        if(fd == NULL) {
                fprintf(stderr,"handler3 couldn't open log\n");
                fflush(stderr);
                return(0);
        }

	memcpy(&el,ptr,sizeof(el));
	fprintf(fd,"handler3 called, counter: %lu seq_no: %lu\n",el.counter,seq_no);
	fflush(fd);


	if(el.counter < 5) {
		el.counter++;
		fprintf(fd,"handler3, calling put counter: %lu seq_no: %lu\n",el.counter,seq_no);
		fflush(fd);
		WooFPut(wf->filename,"woofc_obj2_handler_2",&el);
	} else {
	fprintf(fd,"handler3 done, counter: %lu seq_no: %lu\n",el.counter,seq_no);
	fflush(fd);
	
	}

	fclose(fd);

	return(1);

}
