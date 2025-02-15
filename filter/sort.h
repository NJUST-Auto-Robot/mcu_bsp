#ifndef SORT_H
#define SORT_H

typedef enum
{
    SORT_Ascending = 0, //升序
    SORT_Descending,
} SORT_ORDER;

void bubble_Sort(float *arr, uint8_t len, SORT_ORDER order);

#endif
