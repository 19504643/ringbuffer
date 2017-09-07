#include "ringbuf.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/param.h>
#include <assert.h>


ringbuf_t rcv_buf;

void ringbuf_create(int size)
{
    rcv_buf.size = size;
    rcv_buf.buf = (uint8_t *)malloc(rcv_buf.size);
    ringbuf_reset(&rcv_buf);
}


int ringbuf_reset(ringbuf_t *buf)
{
    int res = -1;

    if(buf)
    {
        memset(buf->buf,0,buf->size);
        buf->head = 0;
        buf->tail = 0;
        res = 0;
    }

    return res;
}

bool ringbuf_empty(ringbuf_t buf)
{
    // We define empty as head == tail
    return (buf.head == buf.tail);
}

bool ringbuf_full(ringbuf_t buf)
{
    // We determine "full" case by head being one position behind the tail
    // Note that this means we are wasting one space in the buffer!
    // Instead, you could have an "empty" flag and determine buffer full that way
    return ((buf.head + 1) % buf.size) == buf.tail;
}

int ringbuf_put(ringbuf_t *buf, uint8_t data)
{
    int res = -1;

    if(buf)
    {
        buf->buf[buf->head] = data;
        buf->head = (buf->head + 1) % buf->size;

        if(buf->head == buf->tail)
        {
            buf->tail = (buf->tail + 1) % buf->size;
        }

        res = 0;
    }

    return res;
}

int ringbuf_get(ringbuf_t *buf, uint8_t *data)
{
    int res = false;

    if(buf && data && !ringbuf_empty(*buf))
    {
        *data = buf->buf[buf->tail];
        buf->tail = (buf->tail + 1) % buf->size;

        res = true;
    }

    return res;
}




