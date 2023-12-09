#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define ARGS_SIZE 2

void display_prompt(void)
{
printf("#cisfun$ ");
fflush(stdout);
}

int main(void)

{

char buffer[BUFFER_SIZE];
ssize_t read_bytes;
pid_t child_pid;
int status;

while (1)

{

display_prompt();

read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);

if (read_bytes == -1)

{

perror("read");
exit(EXIT_FAILURE);

}

if (read_bytes == 0)

{

printf("\n");
break;

}

buffer[read_bytes - 1] = '\0';

child_pid = fork();

if (child_pid == -1)

{

perror("fork");
exit(EXIT_FAILURE);

}

if (child_pid == 0)

{

char *args[ARGS_SIZE];
args[0] = buffer;
args[1] = NULL;

if (execve(buffer, args, NULL) == -1)

{

perror(buffer);
exit(EXIT_FAILURE);

}
}

else

{

waitpid(child_pid, &status, 0);

if (WIFEXITED(status) && WEXITSTATUS(status) == 127)

{

fprintf(stderr, "./shell: %s: not found\n", buffer);

}
}
}

return 0;
}

