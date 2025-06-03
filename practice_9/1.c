#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

#define BUFFER_SIZE 512
#define MIN_USER_UID 1000

int main() {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char *token, *saveptr;
    int uid, current_uid, count = 0;
    
    current_uid = getuid();
    struct passwd *pw = getpwuid(current_uid);
    if (!pw) {
        perror("getpwuid");
        return 1;
    }
    
    printf("Current user: %s (UID: %d)\n\n", pw->pw_name, current_uid);
    
    fp = popen("getent passwd", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }
    
    printf("Regular users (excluding current):\n");
    printf("%-16s %-6s %-20s %s\n", "Username", "UID", "Name", "Home");
    printf("%-16s %-6s %-20s %s\n", "--------", "---", "----", "----");
    
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        
        char *username = strtok_r(buffer, ":", &saveptr);
        strtok_r(NULL, ":", &saveptr); 
        char *uid_str = strtok_r(NULL, ":", &saveptr);
        strtok_r(NULL, ":", &saveptr);
        char *gecos = strtok_r(NULL, ":", &saveptr);
        char *home = strtok_r(NULL, ":", &saveptr);
        
        if (!username || !uid_str) continue;
        
        uid = atoi(uid_str);
        
        if (uid >= MIN_USER_UID && strcmp(username, pw->pw_name)) {
            printf("%-16s %-6d %-20s %s\n", 
                   username, uid, 
                   gecos ? gecos : "-",
                   home ? home : "-");
            count++;
        }
    }
    
    pclose(fp);
    
    printf("\nTotal regular users found: %d\n", count);
    return 0;
}
