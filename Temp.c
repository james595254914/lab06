#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ifttt.h"
int main(int argc, char *argv[])
{
 FILE *fd;    // file pointer
 int n,y,high,low,first,last; //y is current, first is boolean,last is last t
 char buf[101];
 char *temp;    // temp pointer
 char l[50], cur[50],h[50];    //different temp message store
 time_t start = time(NULL);  //current time
 int next = start+1;           // iterator in loop
 first =0;                       // boolean false
 while(start < next){
 if((fd = fopen("/sys/bus/w1/devices/28-0213133656aa/w1_slave", "r")) == (FILE *)NULL) {
 perror("Error: Failed to Open w1_slave file");
 (void) exit(1);
 }
 n = fread(buf, 1, 100, fd);
 if(n == 0) {
 perror("Error: No Arguments Found");
 exit(1);
 }
 buf[n] = '\0';          
 fprintf(stdout, "Read '%s'\n",buf+69);   //location after 69 is temp show in screen
 (void) fclose(fd);
 temp = buf+69;//temp print after t =29750 
 printf("Temp: %s",temp);
 y = atoi(temp);       //change from char to int
 printf("Integer Y: %d\n",y);
 if(first == 0){  //first temp read
	low = y;
	high = y;
	first =1;
	last = y;
	sprintf(l,"Lowest Temp: %d C",low/1000);
	sprintf(cur,"Current Temp: %d C",y/1000);
	sprintf(h,"Highest Temp: %d C",high/1000);
	ifttt("https://maker.ifttt.com/trigger/temp_change/with/key/qUjk5_1YTEvBRpXGUmjd4", l,cur, h);
	}
 else{
	if(y <low){low = y;}
	else if(y>high){high = y;}
	else if(((last-low)>=1000) ||((high-last)>=1000)){
	sprintf(l,"Lowest Temp: %d C",low/1000);
        sprintf(cur,"Current Temp: %d C",y/1000);
        sprintf(h,"Highest Temp: %d C",high/1000);
	  ifttt("https://maker.ifttt.com/trigger/temp_change/with/key/qUjk5_1YTEvBRpXGUmjd4", l,cur, h);
	  last = y;
	}
	
	}
 printf("High: %d Current: %d Low: %d\n",high,y,low);
 start = time(NULL);
 next = start+1;                    //reassign the next to make loop continue
}
 return 0;
}
