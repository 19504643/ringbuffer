#ifndef _RINGBUF_H_
#define _RINGBUF_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>


extern "C" {

typedef struct
{
    uint8_t *buf;
    size_t head; 
    size_t tail;
    size_t size;
} ringbuf_t;


extern ringbuf_t rcv_buf;

void ringbuf_create(int size);
int ringbuf_reset(ringbuf_t *buf);
int ringbuf_put(ringbuf_t *buf, uint8_t data);
int ringbuf_get(ringbuf_t *buf, uint8_t *data);
bool ringbuf_empty(ringbuf_t buf);
bool ringbuf_full(ringbuf_t buf);


}

#endif /* INCLUDED_RINGBUF_H */

