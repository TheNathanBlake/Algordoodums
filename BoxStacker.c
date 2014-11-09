#include <stdio.h>
#include <stdlib.h>

typedef struct box {
    int wth;
    int dth;
    int hgt;
}Box;

//uses a ternary operator to determine higher value
int max(int first, int second) {
    if(first > second)
        return first;
    return second;
}

//Dynamic program designed to provide the greatest height output
int stacker(Box *pile[], int size, int topBox, int thisBox, int h)
{
    if(thisBox == size)
        return h;
    if( h == 0 ||
    (( (*pile)[topBox].dth <= (*pile)[thisBox].dth )
    && ( (*pile)[topBox].wth <= (*pile)[thisBox].wth ))
     )
    {
        return max(stacker(pile, size, topBox, (thisBox+1), h),
                stacker(pile, size, thisBox, (thisBox+1), (h+(*pile)[thisBox].hgt)));
    }
    else
        return stacker(pile, size, topBox, ++thisBox, h);
}

//used with qsort as a compare function
int heightCheck(const void *first, const void *next)
{
    if(((Box *)first)->hgt > ((Box *)next)->hgt)
        return -1;
    return 0;
}

int main(int argc, char *argv[])
{
    //initialize arrays and values
    int count, h;
    scanf("%d", &count);
    Box *pile = (Box *)calloc(count, sizeof(Box));
    if(pile == NULL) {
        printf("Out of mem.\n");
        return -1;
    }
    //record box info from scanned file
    int width, depth, height, i;
    for(i = 0; i < count; i++) {
        scanf("%d\n%d\n%d\n", &width, &depth, &height);
        pile[i].wth = width;
        pile[i].dth = depth;
        pile[i].hgt = height;
    }
    //Built-in quicksort, because reasons
    qsort(pile, count, sizeof(Box), heightCheck);
    for(i = 0; i < count; i++)
    {
        printf("%d x %d x %d\n", pile[i].wth, pile[i].dth, pile[i].hgt);
    }
    //test loop to check the sort
    h = stacker(&pile, count, 0, 0, 0);
    printf("The best height found is %d\nEven then a %d-mile high stack of cardboard boxes?\n", h, h);
    free(pile);
    return 0;
}
