#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <sqlite3.h>
#include <string.h>
#include <errno.h>

#define DB_PATH "/aspz/crash_monitor.db"

static sqlite3 *db = NULL;
static volatile int running = 1;

void signal_handler(int sig) {
    running = 0;
}

int init_db() {
    if (sqlite3_open(DB_PATH, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    
    const char *sql = "CREATE TABLE IF NOT EXISTS crashes ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "pid INTEGER,"
                      "signal_name TEXT,"
                      "timestamp TEXT);";
    
    if (sqlite3_exec(db, sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Cannot create table: %s\n", sqlite3_errmsg(db));
        return -1;
    }
    return 0;
}

void log_crash(pid_t pid, int sig) {
    char sql[256];
    char timestamp[32];
    const char *sig_name;
    
    switch (sig) {
        case SIGFPE:  sig_name = "SIGFPE"; break;
        case SIGILL:  sig_name = "SIGILL"; break;
        case SIGSEGV: sig_name = "SIGSEGV"; break;
        default: return; 
    }
    
    time_t now = time(NULL);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    
    snprintf(sql, sizeof(sql),
             "INSERT INTO crashes (pid, signal_name, timestamp) VALUES (%d, '%s', '%s');",
             pid, sig_name, timestamp);
    
    if (sqlite3_exec(db, sql, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to log crash: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Logged crash: PID=%d, Signal=%s\n", pid, sig_name);
    }
}

int should_monitor(int sig) {
    return (sig == SIGFPE || sig == SIGILL || sig == SIGSEGV);
}

void daemonize() {
    pid_t pid = fork();
    if (pid < 0) exit(1);
    if (pid > 0) exit(0);
    
    setsid();
    chdir("/");
    
    close(0);
    close(1);
    close(2);
}

int main() {
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    
    daemonize();
    
    if (init_db() < 0) {
        exit(1);
    }
    
    while (running) {
        pid_t pid = fork();
        
        if (pid == 0) {
            int *p = NULL;
            *p = 42; // SIGSEGV
            exit(0);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);
            
            if (WIFSIGNALED(status)) {
                int sig = WTERMSIG(status);
                if (should_monitor(sig)) {
                    log_crash(pid, sig);
                }
            }
        }
        
        sleep(5); 
    }
    
    if (db) {
        sqlite3_close(db);
    }
    
    return 0;
}
