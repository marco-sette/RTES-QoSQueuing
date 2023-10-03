#include "testDataStr.h"
#include <stdio.h>

DS_buffer_t *DS_Init(const char *name_Init, const size_t numMaxElements, const size_t sizeElement) {

    if(sizeElement < 1 || numMaxElements < 2) {
        return NULL;
    }

    DS_buffer_t *temp_ret = (DS_buffer_t*) malloc (sizeof(DS_buffer_t));
    uint8_t *buff = (uint8_t*) malloc (numMaxElements * sizeElement);

    temp_ret -> sem = sem_init(name_Init, 0, 1);	// gli viene passato - ovvio
    temp_ret -> ptrBfr_start = buff;
    temp_ret -> ind_head = 0;
    temp_ret -> ind_tail = 0;
    temp_ret -> max_elements = numMaxElements;	// gli viene passata da fuori
    temp_ret -> num_elements = 0;
    temp_ret -> size_elements = sizeElement; //gli viene passata da fuori

    return temp_ret;

}


statesDS_t DS_Full(DS_buffer_t *buffer) {
    statesDS_t temp_ret = false_DS;     //intanto lo imposto a false

    int temp_ret_sem = sem_wait(buffer->sem);

    if (temp_ret_sem != 1 || buffer == NULL) {      //  controllo...
        return error_DS;                            // e in caso esco
    }

    uint32_t temp_ind = (buffer->ind_head+1) % buffer->max_elements;  
    if ( temp_ind == buffer->ind_tail ) {
        temp_ret = true_DS;
    }

    sem_post(buffer->sem);
    return temp_ret;
}

statesDS_t DS_Empty(DS_buffer_t *buffer){
    //nuovamente controlli conteggiom, (circa) come sopra
    statesDS_t temp_ret = false_DS;		// uguale a full

    int temp_ret_sem = sem_wait(buffer->sem);		// uguale a full

    if (temp_ret_sem != 1 || buffer == NULL) {
        return error_DS;
    }
    if ( buffer->ind_head == buffer->ind_tail ) {		// non servono conti -> siamo gia' in head, non dobbiamo calcolare come per full
        temp_ret = true_DS;
    }

    sem_post(buffer->sem);
    return temp_ret;
}


statesDS_t DS_Delete(DS_buffer_t *buffer){
    statesDS_t temp_ret = false_DS;

    int temp_ret_sem = sem_wait(buffer->sem);

    DS_sem_t temp_sem = buffer->sem;

    //controlli -> free or exit
    if (buffer == NULL) {
        temp_ret = true_DS;
    } else {
        free(buffer);
    } 
    if (buffer->ptrBfr_start != NULL) {
        free (buffer->ptrBfr_start);
    }
    if (temp_ret_sem != 1) {
        return error_DS;
    }

    sem_post(temp_sem);
    sem_close(temp_sem);
    return temp_ret;
}


void DS_GetHead(DS_buffer_t *buffer){
    if(buffer == NULL){
        return NULL;
    }
    if (DS_Full(buffer) == true_DS || DS_Full(buffer) == error_DS) {        //full buffer
        return NULL;
    }

    int temp_ret_sem = sem_wait(buffer->sem);
    if(temp_ret_sem != 1) {
        return NULL;
    }

    void *temp_ret = (uint8_t*)buffer->ptrBfr_start + (buffer->ind_head * buffer->size_elements);

    buffer->ind_head = (buffer->ind_head + 1) % buffer->max_elements;
    buffer->num_elements++;

    if (buffer->num_elements > buffer->max_elements) {          // error
        temp_ret = NULL;
    }

    sem_post(buffer->sem);
    return temp_ret;
}

void DS_GetTail(DS_buffer_t *buffer){
    if(buffer == NULL){
        return NULL;
    }
    if (DS_Empty(buffer) == true_DS || DS_Empty(buffer) == error_DS) {              //buffer empty
        return NULL;
    }

    int temp_ret_sem = sem_wait(buffer->sem);

    if (temp_ret_sem != 1) {
        return NULL;
    }

    void *temp_ret = (uint8_t*)buffer->ptrBfr_start + (buffer->ind_tail * buffer->size_elements);

    buffer->ind_tail = (buffer->ind_tail + 1) % buffer->max_elements;
    buffer->num_elements--;
    if (buffer->num_elements < 0){          //zero elements
        temp_ret = NULL;
    }
    sem_post(buffer->sem);
    return temp_ret;
}

size_t DS_GetRemainingSpace(DS_buffer_t *buffer) {

    size_t temp_ret = 0;
    int temp_ret_sem = sem_wait(buffer->sem);

    //casi limite
    if(buffer == NULL || temp_ret_sem != 1){	//esco subito
        return 0;
    }

    //calcolo
    if(buffer->max_elements >= buffer->num_elements) {
        temp_ret = buffer->max_elements - buffer->num_elements;
    }

    sem_post(buffer->sem);
    return temp_ret;
}



