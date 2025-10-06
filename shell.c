#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void make_toks(char *s, char *tok[]) {
    int i = 0;
    char *p;
    p = strtok(s, " \t");
    while (p != NULL) {
        tok[i++] = p;
        p = strtok(NULL, " \t");
    }
    tok[i] = NULL;
}

void typeline(char *fn, char *op) {
    int fh, i = 0, j = 0, lines = 0;
    char c;

    fh = open(fn, O_RDONLY);
    if (fh == -1) {
        printf("file %s not found\n", fn);
        return;
    }

    if (strcmp(op, "a") == 0) {
        while (read(fh, &c, 1) > 0)
            printf("%c", c);
        close(fh);
        return;
    }
   int n=atoi(op);

    if (n > 0) {
        i = 0;
        while (read(fh, &c, 1) > 0) {
            printf("%c", c);
            if (c == '\n') i++;
            if (i == n) break;
        }
    }

    if (n < 0) {
        i = 0;
        while (read(fh, &c, 1) > 0) {
            if (c == '\n') i++;
        }

        lseek(fh, 0, SEEK_SET);
        j = 0;
        while (read(fh, &c, 1) > 0) {
            if (c == '\n') j++;
            if (j == i + n) break;
        }

        while (read(fh, &c, 1) > 0) {
            printf("%c", c);
        }
    }

    close(fh);
}

int main() {
    char buff[80], *args[10];
    int pid;

    while (1) {
        printf("Myshell$ ");
        fflush(stdout);

        if (fgets(buff, sizeof(buff), stdin) == NULL)
            continue;

        if (buff[strlen(buff) - 1] == '\n')
            buff[strlen(buff) - 1] = '\0';

        make_toks(buff, args);

        if (args[0] == NULL)
            continue;

        if (strcmp(args[0], "typeline") == 0) {
            if (args[1] && args[2])
                typeline(args[2], args[1]);
            else
                printf("Usage: typeline <n|a> <filename>\n");
        } else {
            pid = fork();
            if (pid > 0) {
                wait(NULL);
            } else {
                if (execvp(args[0], args) == -1)
                    printf("Bad Command\n");
                exit(1);
            }
        }
    }

    return 0;
}

