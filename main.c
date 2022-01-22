#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include "function.h"
int main(){
    int temp;
    while(1)
    {
        system("cls");
        temp = menu();
        if(temp == 1)
            continue;
        else if(temp == 0)
            break;
        else if(temp == 2)
            continue;
    }
}