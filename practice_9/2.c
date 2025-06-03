#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    setuid(0);  
    system("cat /etc/master.passwd");
    return 0;
}
