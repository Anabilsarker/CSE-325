#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

bool is_dentistawake = false;
bool *is_treated;

sem_t syn;

void *getTreated(void *arg)
{
    sem_wait(&syn);

    int index = (intptr_t)arg;
    if (is_dentistawake == false)
    {
        is_dentistawake = true;
    }
    if (is_dentistawake == true)
    {
        sleep(1);
        is_treated[index] = true;
        printf("\nPatient %d is treated", index);
    }

    sem_post(&syn);
}

void main(int argc, char *argv[])
{
    int num_patients = atoi(argv[1]);
    int num_chairs = atoi(argv[2]);
    pthread_t patient_thread[num_patients];

    is_treated = malloc(num_patients * sizeof(is_treated));
    if ((num_chairs <= 0) || (num_patients < 0))
    {
        printf("Invalid Number of Patients or chairs.\n");
        return;
    }
    if ((num_patients > num_chairs))
    {
        printf("%d Patients left due to seat shortage", (num_patients - num_chairs));
        num_patients = num_chairs;
    }
    

    if (sem_init(&syn, 0, 1) == -1)
    {
        perror("Could not initialize mylock semaphore");
        exit(2);
    }
    for (int i = 0; i < num_patients; i++)
    {
        if (pthread_create(&patient_thread[i], NULL, getTreated, (void *) (intptr_t) i) < 0)
        {
            perror("Error: thread cannot be created");
            exit(1);
        }
    }

    for (int i = 0; i < num_patients; i++)
    {
        pthread_join(patient_thread[i], NULL);
        pthread_exit(0);
    }

    sem_destroy(&syn);
    exit(0);
}
