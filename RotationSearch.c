#include <stdio.h>
#include <stdlib.h>

int midFind(int first, int last);
int nextFind(int mid, int end, int increment);
int maxSearch(int *arr, int left, int right, int length);
int binSearch(int *arr, int left, int right, int value, int length);

int main(int argc, char *argv[])
{
    /*Initialize values*/
    int size, value, min, max, loc, *arr;
    char temp;
    /*Scan for values*/
    scanf("%d", &size);
    arr = malloc(size*sizeof(int));
    if(arr == NULL)
    {
        printf("Error: You ran out of RAM.\n");
        exit(0);
    }
    for(min = 0; min < size; min++) //min being used to save space
    {
        scanf("%d", arr+min);
        scanf("%c", &temp);
    }
    scanf("%d", &value);
    /*Find maximum point*/
    if(*(arr) < *(arr+size-1))
    {
        max = size-1;
        min = 0;
    }
    else
    {    
        max = maxSearch(arr, 0, size-1, size);
        min = max+1;
    }
    /*Find sought point*/
    if(value == *(arr+max))
        loc = max;
    else if(max == size-1)
        loc = binSearch(arr, 0, size-1, value, size);
    else if(max == 0)
        loc = binSearch(arr, 1, size-1, value, size);
    else if(value > *(arr+(size-1)))
        loc = binSearch(arr, 0, max-1, value, size);
    else if(value < *(arr))
        loc = binSearch(arr, max+1, size-1, value, size);
    /*Print location of value (based 1)*/
    if(loc == -1)
    {
        printf("Error: %d not found\n", value);
        free(arr);
        exit(0);
    }
    printf("Position of %d in the rotated sequence = %d.\n", value, loc+1);
    printf("Position of %d in the sorted sequence = %d.\n", value, (nextFind(loc, size, (size-1)-max)+1));
    printf("Min = %d\nMax = %d\n", *(arr+min), *(arr+max));
    /*Free the memory*/
    free(arr);
    return 0;
}

/* Recursive binary search for maximum value in rotated array
 */
int maxSearch(int *arr, int left, int right, int length)
{

    /*Set values*/
    int mid;
    mid = midFind(left, right);
    /*Perform search*/
    if(*(arr+mid) > *(arr+(nextFind(mid, length, 1)))) // maximum
        return mid;
    else if(*(arr+mid) < *(arr+(mid-1))) //mainly a quickfix for the min being in the middle
        return (mid-1);
    else if(left > right)
        return -1;
    else if(*(arr+mid) > *(arr+left))
        return maxSearch(arr, mid+1, right, length);
    else if(*(arr+mid) < *(arr+left))
        return maxSearch(arr, left, mid-1, length);
}

/* Recursive binary search
 */
int binSearch(int *arr, int left, int right, int value, int length)
{
    if(left > right)
        return -1;
    /*Set values*/
    int mid;
    mid = midFind(left, right);
    /*Perform search*/
    if(*(arr+mid) == value)
        return mid;
    else if(*(arr+mid) > value)
        return binSearch(arr, left, mid-1, value, length);
    else if(*(arr+mid) < value)
        return binSearch(arr, mid+1, right, value, length);
}
/* Helper function to determine the proper midpoint
   midpoint set on high side to aid maxSearch
 */
int midFind(int first, int last) {
    int mid = (first+last)/2;
    return mid;
}

/* Helper function to determine a rotated value, or find the next over
 */
int nextFind(int val, int end, int increment) {
    int q = val + increment;
    while(q >= end)
        q -= end;
    return q;
}
