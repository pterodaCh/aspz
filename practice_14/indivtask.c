#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

void log_time(const char *filename) {
    FILE *f = fopen(filename, "a");
    if (!f) {
        perror("fopen");
        return;
    }

    time_t now = time(NULL);
    fprintf(f, "[%s] Timer triggered\n", ctime(&now));
    fclose(f);
}

void handler(int sig, siginfo_t *si, void *uc) {
    if (sig == SIGRTMIN) {
        log_time("log1.txt");
    } else if (sig == SIGRTMIN + 1) {
        log_time("log2.txt");
    }
}

int main() {
    struct sigaction sa = {0};
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigaction(SIGRTMIN, &sa, NULL);
    sigaction(SIGRTMIN + 1, &sa, NULL);

    timer_t timer1, timer2;
    struct sigevent sev = {0};


    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    timer_create(CLOCK_REALTIME, &sev, &timer1);

    struct itimerspec its1 = {
        .it_value = {2, 0},
        .it_interval = {2, 0}
    };
    timer_settime(timer1, 0, &its1, NULL);

    sev.sigev_signo = SIGRTMIN + 1;
    timer_create(CLOCK_REALTIME, &sev, &timer2);

    struct itimerspec its2 = {
        .it_value = {3, 0},
        .it_interval = {3, 0}
    };
    timer_settime(timer2, 0, &its2, NULL);

    printf("Running timers. Press Ctrl+C to exit.\n");
    while (1)
        pause();

    return 0;
}
