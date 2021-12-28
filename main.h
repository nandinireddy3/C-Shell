#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct jobs
{
    char jnames[10000];
    pid_t pid;
};


char* home_directory;
char* token[100000];
char cwd[100000];
long long int pseudohomepid;
//jobs
int njobs;
int sigkill_flag;
long long int pids[1000];
char names[10000][1000];
struct jobs arr_jobs[100000];
struct jobs current_foreground;



void Prompt();
void cd(char* token[],long long int nargs);
void ls(char* token[],long long int nargs);
void pinfo(char* token[],long long int nargs);
void foreground(char* token[]);
void background(char* token[],long long int n);
void echo(char* token[],long long int n);
void pwd();
void repeat(char* token[],long long int nargs);
void print_status();
void redirection(char* command);
void PIPE(char* comm);
void Printjobs(char* command[],long long int nargs);
void fg(char* command[],long long int nargs);
void bg(char* command[],long long int nargs);
void sig(char* command[],long long int nargs);


#endif