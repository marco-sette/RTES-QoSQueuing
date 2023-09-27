#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <semaphore.h>


typedef sem_t* DS_sem_t;

typedef enum {
    true_DS,
    false_DS,
    error_DS = -1
} statesDS_t;

typedef struct DS_buffer_t {
    DS_sem_t sem;

    int8_t *ptrBfr_start;

    int32_t ind_head, ind_tail;

    size_t max_elements, num_elements, size_elements;

} DS_buffer_t;

DS_buffer_t *DS_Init(const char *name_Init, const size_t numMaxElements, const size_t sizeElement);

statesDS_t DS_Full(DS_buffer_t *buffer);    //const?
statesDS_t DS_Empty(DS_buffer_t *buffer);   //const?
statesDS_t DS_Delete(DS_buffer_t *buffer);

void DS_GetHead(DS_buffer_t *buffer);
void DS_GetTail(DS_buffer_t *buffer);

size_t DS_GetRemainingSpace(DS_buffer_t *buffer);
