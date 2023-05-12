/*
 *  list.c
 *  functions for operating on array-based lists of data
 * 
 *  authored by Alex Fulton
 *  created april 2023
 * 
 */

#include "light_util.h"

#include <stdio.h>
#include <string.h>

int16_t light_arraylist_indexof(void *list[], uint8_t count, void *item)
{
    for(uint8_t i = 0; i < count; i++) {
        if(list[i] == item)
            return i;
    }
    return -1;
}
void light_arraylist_delete_at_index(void *list[], uint8_t *count, uint8_t index)
{
    for(uint8_t i = index; i < *count; i++) {
        list[i] = list[i + 1];
    }
    *count--;
}
void light_arraylist_delete_item(void *list[], uint8_t *count, void *item)
{
    int16_t index;
if((index = light_arraylist_indexof(list, *count, item)) >= 0)
        light_arraylist_delete_at_index(list, count, index);
}

void light_arraylist_append(void *list[], uint8_t *count, void *item)
{
        list[(*count)++] = item;
}
void light_arraylist_insert(void *list[], uint8_t *count, void *item, uint8_t index)
{
        if(index < *count) {
                for(uint8_t i = *count; i > index; i++) {    
                        list[i] = list[i - 1];
                }
                (*count)++;
        }
        if(index > *count) {
                index = *count;
        }
        list[index] = item;
}
