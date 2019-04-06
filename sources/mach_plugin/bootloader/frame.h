#ifndef FRAME_H
#define FRAME_H

int WriteFrame(void * handle, char * buf1, int cnt1 ,char * buf2 = NULL ,int cnt2 = 0);
int ReadFrame(void * handle, char * buf, int size);

#endif
