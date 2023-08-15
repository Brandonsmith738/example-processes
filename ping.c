#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = getpid();
    printf("Ping PID: %d\n", pid);

    // Convert to int64_t
    int64_t pid_int64 = (int64_t)pid;

    // Open a file for writing
    FILE *file = fopen("benchmarking/pids/ping.pid", "wb");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Write the int64_t value to the file
    size_t num_written = fwrite(&pid_int64, sizeof(int64_t), 1, file);
    if (num_written != 1)
    {
        perror("Error writing to file");
        fclose(file);
        return 1;
    }

    fclose(file);

    printf("PID written to benchmarking/pids/ping.pid\n");

    const char *host = "google.com";
    const char *pingCommand = "ping -c 4 "; // Adjust the number of pings as needed

    while (1)
    {
        char fullCommand[100];
        strcpy(fullCommand, pingCommand);
        strcat(fullCommand, host);

        int result = system(fullCommand);

        if (result != 0)
        {
            printf("Ping failed.\n");
            break;
        }

        // Sleep for a while before the next ping
        // Adjust the sleep duration as needed
        // 1000000 microseconds = 1 second
        usleep(1000000);
    }

    return 0;
}
