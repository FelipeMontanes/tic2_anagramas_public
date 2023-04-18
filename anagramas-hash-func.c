// hacer funciones declaradas en anagramas-hash.h
#include <anagramas-hash.h>
#include <stdio.h>

extern struct list *list_create(void){
    struct list *l = malloc (sizeof (struct list));
    if (l== NULL){
        return NULL;
    }
    
    l->first = malloc (sizeof (struct listnode));
    l->last = malloc (sizeof (struct listnode));

    if ((l->first == NULL) || (l->last == NULL)){
        return NULL; // no tiene sentido hacer la lista si no hay espacio para sus nodos
    }

    return l;
}
    // crea una lista vacía, retorna puntero a la misma

//crea listnode
struct listnode *create_listnode(char *word){

    struct listnode *nodo = malloc (sizeof (struct listnode));
    nodo->word = strdup(word);
    nodo->next = malloc (sizeof (struct listnode));

    return nodo;
}

extern struct list *list_insert_last_word(struct list *l, char *word){
    if (l== NULL){
        l = list_create();
        l->first = create_listnode(word);
        l->last = l->first;
    }else{
        //if (l->last == l->first){ //tengo 1 elemento solo
        l->last->next = create__listnode(word);
        l->last = l->last->next;
        //}
    }
    return l;

}
    // inserta una palabra al final de la lista l, retorna el puntero a la lista
    // si la lista es NULL, crea una nueva

//crea hashnode
struct hashnode *create_hashnode(char *key, char *word){

    struct hashnode *nodo = malloc (sizeof (struct hashnode));
    nodo->key = strdup(key);
    //si estoy creando el nodo es porque es la primer palabra con esa clave
    nodo->wlist = list_insert_last_word(NULL, word);
    nodo->next = malloc (sizeof (struct hashnode));

    return nodo;
}

extern struct hashnode *hash_insert_word(struct hashnode *node, char *key, char *word){
    unsigned int h = hash(key);
    struct hashnode *hash_de_esa_clave = anagrams[h]; // posicion del anagrams
    
    //hash de esa clave tiene claves distintas pero que al hashearlas colisionan

    while ((hash_de_esa_clave->next) != NULL ){ //busco key en hash

        if (strcmp(hash_de_esa_clave->key, key) == 0){ //si encuentro la clave

            hash_de_esa_clave->wlist = list_insert_last_word(hash_de_esa_clave->wlist, word);
            //inserto al final de la lista
            return hash_de_esa_clave->wlist->first;
        }
        hash_de_esa_clave = hash_de_esa_clave->next;
    }
    //si llega hasta aca no encontro la key
    hash_de_esa_clave->next = create_hashnode(key, word);
    //agrego el nodo al final del hash ? esta bien?
}
    // busca key en el hash (y si no encuentra inserta key al inicio en lista simple)
    // luego agrega palabra al final de la lista de anagramas asociadas a la key
    // retorna siempre el primero de la lista: node si key estaba o el nuevo nodo si se insertó
