#include "ringbuf.h"

int main()
{
    ringbuf_create(128);
    int i = 0;
    for( ;i < rcv_buf.size - 1; i++){
        ringbuf_put(&rcv_buf, i);
    }

    for(i = 0;i < rcv_buf.size - 1; i++){
        printf("%X\n",rcv_buf.buf[i]);            
    }
    
    uint8_t data;
    while(1)
    {
        if(ringbuf_get(&rcv_buf,&data)){
            printf("get data: %X\n",data);
        }else{
            printf("put data: %X\n",++i);
            ringbuf_put(&rcv_buf,i);
        }
        usleep(100000);
    }
}
