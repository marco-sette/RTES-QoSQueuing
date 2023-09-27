#include "testDataStr.h"
#include <stdio.h>

DS_buffer_t *DS_Init(const char *name_Init, const size_t numMaxElements, const size_t sizeElement) {
    //malloc per tutto + sem_init
    ; //TODO
}


statesDS_t DS_Full(DS_buffer_t *buffer) {
    //se buffer != 1 errore e lavoro sul conteggio elementi
    ; //TODO
}

statesDS_t DS_Empty(DS_buffer_t *buffer){
    //nuovamente controlli conteggiom, inverso da full
    ; //TODO
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



