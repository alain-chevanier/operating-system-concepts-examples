
/**
 * This program forks a separate process using the fork()/exec() system calls.
 *
 * Figure 3.09
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t pid;

  // let p_0 be the parent process and p_1 the child process of p_0

	/* fork a child process */
	pid = fork();

	// p_0, p_1
	// if fork fails then
	//   p_0: pid < 0
	// else then (fork succeed, p_1 is created as a clone of p_0)
	//   p_0: pid > 0
	//   p_1: pid = 0

	if (pid < 0) { /* error occurred */
		fprintf(stderr, "p_0: Fork Failed\n");
		return 1;
	} else if (pid == 0) { /* child process */
		// p_1
		printf("p_1: I'm the child process %d\n", getpid());
		execlp("/bin/ls","ls",NULL);
	} else { /* parent process */
		// p_0
		pid_t parent_pid = getpid();
		/* parent will wait for the child to complete */
		printf("p_0: I am the parent %d\n", parent_pid);
		printf("p_0: Child process pid: %d\n", pid);
		int child_status = 0;
		pid_t child_pid = wait (&child_status);
		
		printf("p_0: Child %d Complete with %d\n", child_pid, child_status);
	}
    
  return 0;
}
