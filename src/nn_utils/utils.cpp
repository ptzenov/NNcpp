#include "utils.hpp"

void log_msg(FILE *fp, const char* message,const char* file,int line){

	fprintf(fp, "PROGRAM LOG:\n FILE: %s; LINE: %d\n  %s \n",file,line,message);
}


