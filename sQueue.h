#include <stddef.h>
#include <stdint.h>

typedef struct {
    //TODO
} Handle_t;
typedef Handle_t * sQueueH_t;

typedef enum {
    //TODO
} sQueueReturn_t;

sQueueH_t queue_NEW(const size_t elementSize, const size_t queueSize, const char *ptrQueue);   //tutto const - secondo me
sQueueReturn_t queue_PUT(sQueueH_t queue_x, void *ptrElm);  // conviene const???
sQueueReturn_t queue_FULL(sQueueH_t queue_x);
sQueueReturn_t queue_GET(sQueueH_t queue_x, void *ptrElm);  // conviene const???
sQueueReturn_t queue_EMPTY(sQueueH_t queue_x);
sQueueReturn_t queue_DELETE(sQueueH_t queue_x);