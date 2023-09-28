#include "testDataStr.h"
#include <stdio.h>

DS_buffer_t *DS_Init(const char *name_Init, const size_t numMaxElements, const size_t sizeElement) {

    if(sizeElement < 1 || numMaxElements < 2) {
        return NULL;
    }

    DS_buffer_t *temp_ret = (DS_buffer_t*) malloc (sizeof(DS_buffer_t));
    uint8_t *buff = (uint8_t*) malloc (numMaxElements * sizeElement);

    temp_ret -> sem = sem_init(1, &name_Init);	// gli viene passato - ovvio
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
    //ricordarsi di lavorare sulla FREE prima di eliminare!!!
    ; //TODO
}


void DS_GetHead(DS_buffer_t *buffer){
    //wait
    //accesso, memorizzo
    //signal
    ; //TODO
}

void DS_GetTail(DS_buffer_t *buffer){
	//lo stesso di gethead
    ; //TODO
}

size_t DS_GetRemainingSpace(DS_buffer_t *buffer) {
    //post e wait per l'accesso in ME
    ; //TODO
}



