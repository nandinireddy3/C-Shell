
To run the shell :
                  make
                  ./a.out


* main.c:
         a while loop will be running 
         1. prompt
         2. input via stdin
         3. tokenize the input with strtok
         4. compare the token[0] with the commands
         5. execute the respected command
        

* main.h: 
         A header file

* prompt.c:
           Prompt()
           displayPrompt() - dispalys the prompt

* cd.c:
        cd()
        - if token[0] after tokinizing is "cd" 
           - cd ~
           - cd .
           - cd ..
           - cd path
           - cd - 

* ls.c:
        ls()
        ls_eachfile()
        printls() 
        - if token[0] after tokinizing is "ls"
           ls
           ls -a
           ls -l
           ls .
           ls ..
           ls ~
           ls -a -l
           ls -la / ls -al
           ls <Directory/File_name>
           ls -<flags> <Directory/File_name> 

* echo.c:
         echo()

* pwd.c:
        pwd()

* foreground.c:
               foreground()
               -if token[0] after tokinizing is "gedit" or "vi" or "emacs" or "sleep"
               -In child process using execvp change the process and parent waits 
               until its status is changed using wait(NULL)

* background.c:
              background()
               -if token[nargs-1] after tokinizing is "&"
               prints <pid>
               -In child process using execvp change the process

* signal.c:
           print_status()
           if background process turns into zombie then 
           picture of child process is stored then according to exit status msg is printed

* repeat.c:
           repeat()
               -if token[0] after tokinizing is "repeat"
               -a for loop will be running and by comparing duplicate[][] with respective commands 
               it will be executed

* pinfo.c:
          pinfo()
            if token[0] after tokinizing is "pinfo"

* redirection.c :
        1. void redirection(char* command) : 
        The input and output files are found by parsing and if any error occurs in opening of input and output files Error msg printed
        else they are redirected to STDOUT_FILENO, STDIN_FILENO
        2. void execute(char* list_command) :
           if no >, >>, < are found , based on parsing of 'command' with delim (" \n\r\t") we get subcommands
           if (subcommand[0],"commands") are performed and execute the commands accordingly

* pipe.c:
         void PIPE(char* comm):
         a. first parse comm with delim "|"  to char* commando[]
         b. initially input = 0
         c. for each commando[] , fork it then in child process redirect input to 0 , fd[1] to 1 , 
         finally in parent process input = fd[0]
         d. if any redirection exists redirection() is used else execute them.

* jobs.c:
         struct jobs is created for storing the pids, names of background processes
         Printjobs():
         A duplicate struct Asc_Names INFO[1000]; is defined and for each job INFO[i].jobno = i , INFO[i].Fnames = arr_jobs[i].jnames;

         INFO[i].Fnames are sorted lexigraphically

         then for each i = 1 to njobs
         pid = INFO[i].pid;
         fd = fopen("/proc/pid/stat","r") is calculated

         fscanf() is performed , if status = 'T' stopped else Running 


* sig.c:  
         sig():
         kill(arr_jobs[atoi(command[1])].pid,atoi(command[2])) is used.


* fgbg.c:
         fg() : pids, names of background processes are stored in current_foreground info and background process is deleted from jobs.
         And initially signals for ignoring SIGTTIN, SIGTTOU are performed finally they are made to default(SIG_DFL).

         bg() : SIGCONT is used to make stopped processes run


* CTRL-C: 
         using signal(SIGINT,CTRL_C) , if interrupt occurs then if it is a foreground process then process is terminated using 
          kill(pid,SIGINT)

* CTRL-Z:
         using signal(SIGSTP,CTRL_Z) , if ctrl - Z is given then we SIGSTP foreground process and adds the information of foreground process to jobs.

* CTRL-D: 
         if fgets(input,100000,stdin) == NULL then by return function main is exited
          as CTRL-D default value is EOF. 
        

