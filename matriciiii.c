#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


int multi = 0;

void *multiscal(int* c)
{
    multi = multi + (*(c)) * (*(c+1));
    return 0;
}

// Comment
int main(void)
{
    int i;
    srand(time(NULL));
    int n = rand() % 10 + 2;
    int a[n], b[n];
    for (i = 0; i < n; i++)
    {
        a[i] = rand() % 16;
        b[i] = rand() % 16;
    }
    
    printf("N = %d\n", n);
    
    printf("Vector a = ");
    for(i = 0; i < n; i++)
        printf("%d, ", a[i]);
    printf("\n");
    
    printf("Vector b = ");
    for(i = 0; i < n; i++)
        printf("%d, ", b[i]);
    printf("\n");
    
    int c[2];
    pthread_t multithr[n];
    
    for(i = 0; i < n; i++)
    {
        c[0] = a[i];
        c[1] = b[i];
        int status = pthread_create( &(multithr[i]), (pthread_attr_t *) NULL, (void*) multiscal, &c);
        
        if (status != 0)
        {
            printf("Thread was not created! Error # %d\n", status);
            exit(-1);
        }
        
        int statusj = pthread_join(multithr[i], (void**) NULL);
        if (statusj != 0)
        {
            printf("Can't wait for the thread # %d\n", i);
            exit(-1);
        }
    }
    
    printf("The scalar multiply of vectors a and b is %d\n", multi);
    
}
