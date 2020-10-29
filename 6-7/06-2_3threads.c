#include <pthread.h>
#include <stdio.h>
int a = 0;

void *mythread(void *dummy)
{
    pthread_t mythid;
    mythid = pthread_self();
    a = a + 1;
    printf("Thread %d, Calculation result = %d\n", mythid, a);
    return NULL;
}

void createThread_1(pthread_t thid)
{
    int res = pthread_create(&thid, (pthread_attr_t *) NULL, mythread, NULL);
    if (res != 0)
    {
        printf("Error on thread create, return value = %d\n", res);
        exit(-1);
    }
    printf("2nd thread created, thid = %d\n", thid);
}

void createThread_2(pthread_t thid2)
{
    int res = pthread_create(&thid2, (pthread_attr_t *) NULL, mythread, NULL);
    if (res != 0)
    {
        printf("Error on thread create, return value = %d\n", res);
        exit(-1);
    }
    printf("3nd thread created, thid = %d\n", thid2);
}


int main()
{
    pthread_t thid, thid2, mythid;
    int result;

    createThread_1(thid);
    createThread_2(thid2);
    
//    result = pthread_create( &thid, (pthread_attr_t *)NULL, mythread, NULL);
//    if (result != 0) {
//        printf ("Error on thread create, return value = %d\n", result);
//        exit(-1);
//    }
//    printf("2nd thread created, thid = %d\n", thid);
//
//    result = pthread_create( &thid2, (pthread_attr_t *)NULL, mythread, NULL);
//    if (result != 0) {
//        printf ("Error on thread create, return value = %d\n", result);
//        exit(-1);
//    }
//    printf("3rd thread created, thid = %d\n", thid2);

    mythid = pthread_self();
    a = a + 1;
    printf("Thread %d, Calculation result = %d\n", mythid, a);

    pthread_join(thid, (void **)NULL);
    pthread_join(thid2, (void **)NULL);
    return 0;
}
