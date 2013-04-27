// TODO
// -rf when removing gives seg fault
// does it save a folder(mkdir) when you exit shell?
// & background function when it is at the end of the line
// maybe some more parsing stuff for other controls

/*
Shervin Shaikh & Ramon Rovirosa
CS 170
Project 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXLINE 1024

//#define DEBUG
#ifdef DEBUG
    #define    debug(f,...)    fprintf(stderr,f,##__VA_ARGS__)
#else
    #define    debug(f,...)
#endif


void error(char inputString[]){
  printf("ERROR: %s: command not found\n", inputString);
  exit(1);
}


// TODO: handle quotes as one arguement & don't break whitespaces
void runCommand(char* command, int ampersand){
  char *args[MAXLINE];
  pid_t pid;
  int count = 1;
  args[0] = strtok(command, " ");
  debug("SINGLE COMMAND/ARGS: %s\n", args[0]);
  while(args[count-1] != NULL){
    args[count] = strtok(NULL, " ");
    debug("SINGLE COMMAND/ARGS: %s\n", args[count]);
    count++;
  }

  // change directory
  if(strcmp(args[0], "cd") == 0){
    int work;
    //debug("changing DIRECTORY: %s\n", args[1]);
    if(args[1] == NULL){
      debug("going home\n");
      work = chdir(getenv("HOME"));
      if(work == -1) perror("ERROR: chdir was unsucessful \n");
      return;
    }
    if(args[1][0] == '~'){
      debug("going home\n");
      work = chdir(getenv("HOME"));
      args[1]++;
      if(args[1][0] == '/'){
        debug("changing DIRECTORY: %s\n", args[1]++);
        const char *path = args[1];
        work = chdir(path); 
        if(work == -1) perror("ERROR: chdir was unsucessful \n");
        return;
      }
      else{
        return;
      }
    }
    debug("changing DIRECTORY: %s\n", args[1]);
    const char *path = args[1];
    work = chdir(path); 
    if(work == -1) perror("chdir was unsucessful \n");
    return;
  }

  // forking
  pid = fork();
  if (pid == -1){
    perror("Fork failed");
    exit(0);
  }
  // child process
  else if(pid == 0){
    int proper_cmd = execvp(args[0], args); 
    if(proper_cmd<0) error(command);
    exit(1);
  }
  // parent process
  else{
    if(ampersand == 0)
       wait(NULL);
  }
}

int checkRedirects(int nredirects,int npipes, char redirects[], int ampersands){
   if(redirects[0] == '>' && nredirects > 1){
      perror("ERROR: wrong use of > \n");
      return 0;
      //exit(0);
   }
   if(redirects[nredirects -1] == '<' && nredirects > 1){
      perror("ERROR: wrong use of <\n");
      return 0;
      //exit(0);
   }
   if(nredirects>1){
      int i = 1;
      for(i=1;i<nredirects-1;i++){
         if(redirects[i] != '|'){
            perror("ERROR: wrong use of |\n");
	    //exit(0);
	    return 0;
	 }  
       }
     } 
   if(ampersands > 1){
     perror("ERROR: more than one ampersand\n");
     //exit(1);
     return 0;
   }
   //int for returning if it was an error or not.
   return 1;
}

int main()
{
  char inputString[MAXLINE] = {0};
  //pid_t pid;
  int inc = 0;
  //int amp = 0;

  // char *cat_args[] = {"cat", "scores", NULL};
  // char *grep_args[] = {"grep", "shervin", NULL};
  // char *cut_args[] = {"wc", NULL};
  //int mypipe[2];

  while(1){
    if(isatty(fileno(stdin)) == 1)
      printf("ssih:>");
    fgets(inputString, MAXLINE, stdin);

    int slen = 0, nredirects = 0, npipes = 0, ampersand = 0;
    while(inputString[slen] != '\n'){
      if(inputString[slen] == '<' || inputString [slen] == '>'){
        nredirects++;
      }
      else if(inputString[slen] == '|'){
        npipes++;
        nredirects++;
      }
      else if(inputString[slen] == '&'){
        ampersand++;
        //inputString[slen] = '\0';
      }
      slen++;
    }
    debug("Number of commands: %d \n", nredirects+1);
    debug("Number of pipes: %d \n", npipes);

    // replaces newline with null
    if(ampersand == 1){
       slen = strlen(inputString) - 2;
    }
    else{
        slen = strlen(inputString) - 1;
    }
    inputString[slen] = 0;

    // exits the shell
    if((!strcmp(inputString, "exit")) || feof(stdin)) exit(0);

    // place redirect characters into a char array
    // TODO: count # of |
    char redirects[nredirects];
    int i, j;
    for(i=0, j=0; i<slen && j<nredirects; i++){
      if(inputString[i] == '|' || inputString[i] == '<' || inputString [i] == '>'){
        redirects[j] = inputString[i];
        debug("Redirect %d value: %c \n", j+1, redirects[j]);
        j++;
      }
    }

    //check make sure correct number of redirects & ampersands
    if(checkRedirects(nredirects, npipes, redirects,ampersand) != 0){
      

      // place each command into a string array
      char *cmd[nredirects+1];
      i = 1;
      cmd[0] = strtok(inputString, "<|>");
      debug("Command 1 is: %s \n", cmd[0]);
      while(i <= nredirects){
	cmd[i] = strtok(NULL, "<|>");
	debug("Command %d is: %s \n", i+1, cmd[i]);
	i++;
      }
      debug("Number of redirects: %d\n", nredirects);
      // TODO: fix cd to actually move you around
      // TODO: revmoe extra stuff because its only 1 command that needs to be runmd;


      // if its a "cd" command
      // if(cmd[0][0] == 'c' && cmd[0][1] == 'd'){
      //   char *args[MAXLINE];
      //   int count = 1;
      //   args[0] = strtok(cmd[0], " ");
      //   while(args[count-1] != NULL){
      //     args[count] = strtok(NULL, " ");
      //     count++;
      //   }
      //   // forking
      //   pid = fork();
      //   if (pid == -1){
      //     perror("Fork failed");
      //     exit(0);
      //   }
      //   // child process
      //   else if(pid == 0){
      //     debug("changing the DIRECTORY: %s\n", "..");
      //     int work = chdir(".."); 
      //     if(work == -1) perror("chdir was unsucessful \n");
      //     exit(1);
      //   }
      //   // parent process
      //   else{
      //     wait(NULL);
      //   }
      // }

      if(nredirects == 0){
	runCommand(inputString,ampersand);
      }

      // either pipelining or I/O redirection
      else{
	// Note that the code in each if is basically identical, so you
	// could set up a loop to handle it.  The differences are in the
	// indicies into pipes used for the dup2 system call
	// and that the 1st and last only deal with the end of one pipe.

	//BEGIN parser.c code
	char *args[nredirects+1][1024];
	for(inc=0;inc<=nredirects;inc++){
	  int dascount = 1;
	  args[inc][0] = strtok(cmd[inc], " ");
	  //printf("args[0]: %s\n", args[0]);
	  while(args[inc][dascount-1] != NULL){
	    args[inc][dascount] = strtok(NULL, " ");
	    //printf("args[%d]: %s\n",dascount, args[dascount]);
	    dascount++;
	  }
	  //parsedArray[inc] = args;
	  // printf("first %s \n", args[inc]);
	}

	//printf("first %s \n", args[2][0]);

	char **command[nredirects+1];
	//commands = {args[0],args[1],args[2],args[3]};
	for(inc=0;inc<=nredirects;inc++){
	  command[inc] = args[inc]; 
	}

	// END parser.c code

	// pipes[0] = read end
	// pipes[1] = write end
      

	// BEGIN shell2.c code
	int status;
        int e, u, commandCounter = 0;
        // setting up pipes
        int pipes[npipes*2];
        for(u=0; u<npipes; u++){
          pipe(pipes + u*2);
        }
        commandCounter=0;

        // fork, dup, close, exec, wait

        int input = 0, output = 0;
        if(redirects[0] == '<') input = 1;
        if(redirects[nredirects-1] == '>') output = 1;

        debug("INPUT: %d, OUTPUT: %d\n", input, output);
        debug("Npipes: %d, Nredirects: %d\n", npipes, nredirects);

        // loop to run all of the executions
        for(; commandCounter <= nredirects; commandCounter++){
          
          if(fork() == 0){
            debug("entering FOR loop, commandCounter: %d\n", commandCounter);

            // exit if its a file name, we dont want to execute them as commands
            if(input == 1 && commandCounter == 1){ exit(0);}
            if(commandCounter == nredirects && output == 1){ exit(0); }

            // if beginning & infile - READ
            if(commandCounter == 0 && input == 1){
              char *filename = *command[1];
              FILE *infile = fopen(filename, "r");
              debug("INPUT filename: %s\n", filename);
              dup2(fileno(infile),0);
              if(npipes > 0){
                dup2(pipes[1], 1);
                debug("in-write pipe for %s->%s\n", *command[commandCounter], *command[commandCounter+2]);
              }
              // close everything
              fclose(infile);
              for(e=0; e<npipes*2; e++){ close(pipes[e]); }
              //commandCounter = 2;
              debug("INFILE execute command: %s, #%d\n", *command[commandCounter], commandCounter);
              execvp(*command[commandCounter], command[commandCounter]);
              exit(0);
            }

            // if not the beginning,  READ-end of pipe
            if(commandCounter !=0 && npipes>0){
              if(commandCounter == 2 && input == 1){
                debug("read pipe for %s<-%s\n", *command[commandCounter], *command[commandCounter-2]); // - input
                dup2(pipes[(commandCounter-1)*2 -2], 0);
              }
              else{
                debug("read pipe for %s<-%s\n", *command[commandCounter], *command[commandCounter-1]); // - input
                dup2(pipes[(commandCounter-1)*2], 0); // - input*2
              }

            }

            // if right before end & outfile exists - WRITE
            if((commandCounter+1) == nredirects && output == 1){
              char* filename = *command[nredirects];
              FILE *outfile = fopen(filename, "w");
              debug("OUTPUT filename: %s \n", filename);
              dup2(fileno(outfile), 1);
              fclose(outfile);
              if(npipes > 0){
                dup2(pipes[npipes*2-2], 0);
                debug("out-read pipe for %s<-%s\n", *command[commandCounter], *command[commandCounter-1]);
              }
              for (e=0; e<npipes*2; e++){ close(pipes[e]); }
              debug("OUTFILE execute command: %s \n", *command[commandCounter]);
              commandCounter++;
              execvp(*command[commandCounter-1], command[commandCounter-1]);
              exit(0);
            }

            // if not the end,  WRITE-end of pipe
            if(commandCounter != nredirects && npipes>0){
              if(!(input == 1 && commandCounter < 2) || output == 1){
                debug("write pipe for %s->%s\n", *command[commandCounter], *command[commandCounter+1]);
                dup2(pipes[commandCounter*2+1 - input*2], 1);
              }
            }

            // close pipes
            for (e=0; e<npipes*2; e++){ close(pipes[e]); }
            
            debug("about to execute command: %s\n", *command[commandCounter]);
            execvp(*command[commandCounter], command[commandCounter]);
            debug("ERROR: Command %s not found\n", *command[commandCounter]);
            exit(1);
          }
          //else wait(&status);
        }
        
        // close all pipes
        for(e=0; e<npipes*2; e++){ close(pipes[e]); }

        // parent waits for all children to finish
        for(e=0; e<nredirects+1; e++){
	  if(ampersand == 0){
	    wait(&status);
	    debug("status: %d completed\n", status);
	  }
        }

	// END shell2.c code
      }
    }
  }
  return 0;
}
