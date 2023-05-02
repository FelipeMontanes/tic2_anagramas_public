// hacer funciones declaradas en anagramas-hash.h
#include "anagramas-hash.h"
#include "wrappers.h"
#include <stdio.h>
#include <string.h>

extern struct list *list_create(void){
    struct list *l = malloc_or_exit (sizeof (struct list));
    
    l->first = NULL;
    l->last = NULL;

    return l;
}
    // crea una lista vacía, retorna puntero a la misma

//crea listnode
struct listnode *create_listnode(char *word){

    struct listnode *nodo = malloc_or_exit (sizeof (struct listnode));
    nodo->word = strdup_or_exit(word);
    //nodo->next = malloc_or_exit (sizeof (struct listnode));
    nodo->next = NULL;

    return nodo;
}

extern struct list *list_insert_last_word(struct list *l, char *word){
    if (l== NULL){
        l = list_create();
        l->first = create_listnode(word);
        l->last = l->first;
    }else{
        //if (l->last == l->first){ //tengo 1 elemento solo

        l->last->next = create_listnode(word);
        l->last = l->last->next;
        //}
    }
    return l;

}
    // inserta una palabra al final de la lista l, retorna el puntero a la lista
    // si la lista es NULL, crea una nueva

//crea hashnode
struct hashnode *create_hashnode(char *key, char *word){

    struct hashnode *nodo = malloc_or_exit(sizeof (struct hashnode));
    nodo->key = strdup_or_exit(key);
    //si estoy creando el nodo es porque es la primer palabra con esa clave
    nodo->wlist = list_insert_last_word(NULL, word);
    //nodo->next = malloc_or_exit (sizeof (struct hashnode));
    nodo->next = NULL;

    return nodo;
}

extern struct hashnode *hash_insert_word(struct hashnode *node, char *key, char *word){
    //unsigned int h = hash(key);
    //struct hashnode *hash_de_esa_clave = anagrams[h]; // posicion del anagrams
    // node = anagrams[h]
    struct hashnode *temp = node;

    if (node == NULL){
        return create_hashnode(key,word);
    }else{
         //hash de esa clave tiene claves distintas pero que al hashearlas colisionan
        while ((node) != NULL ){ //busco key en hash

            if (strcmp(node->key, key) == 0){ //si encuentro la clave

                node->wlist = list_insert_last_word(node->wlist, word);
                //inserto al final de la lista
                return node;
            }
            node = node->next;
        }
        //si llega hasta aca no encontro la key
       
        struct hashnode *nuevo = create_hashnode(key,word);
        nuevo->next = temp;
        return nuevo;

    }
    
}
    // busca key en el hash (y si no encuentra inserta key al inicio en lista simple)
    // luego agrega palabra al final de la lista de anagramas asociadas a la key
    // retorna siempre el primero de la lista: node si key estaba o el nuevo nodo si se insertó

extern char *sort_word(char *word){

    char temp;
    //bubblesort
    for (int j = 0; j < strlen(word); j++){
        for (int i=0; i < strlen(word)-1; i++){
            if (word[i] > word[i+1]){
                temp = word[i+1];
                word[i+1] = word[i];
                word[i] = temp;
            }
        }
    }
    return word;
}
    // ordena EN EL LUGAR la palabra 'word' según código ASCII en forma ascendente

extern void print_anagrams(struct hashnode *hn){
    printf("Clave: %s | ", hn->key);

    struct listnode *lista_actual = hn->wlist->first;
    while (lista_actual->next != NULL){
        printf("| %s ", lista_actual->word );
        lista_actual= lista_actual->next;
    }
    printf("\n");
}
    // escribe (printf) la lista de anagramas para ese hashnode
