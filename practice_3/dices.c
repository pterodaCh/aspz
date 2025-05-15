    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>



    int main(int argc, char **argv) {
        FILE *file = fopen("dicelogs.txt", "w");
        if(!file)
        {
                perror("fopen");
                return 1;
        }
        int n, i;
        scanf("%d", &n);
        for (i = 0; i < n; i++)
        {       
                int roll = (rand() % 6) + 1;    
                 printf("You rolled %d \n", roll);
                 fprintf(file, "You rolled %d \n", roll);
        }

        fclose(file);
        return 0;

    }





