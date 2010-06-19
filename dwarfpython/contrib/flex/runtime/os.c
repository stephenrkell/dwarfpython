// posix_1str, 35 (-8) / 4 = 6.7
// posix_2str, 36 (-7) / 3 = 9.7
// +3 for method table
//
// +4 (-1) for each method for the method table

// process ids
int getpid(){}; // 11 : 2 : 11
int getppid(){}; // 11 : 2 : 11
int getpgid(int pid){}; // 29 (-5) : 5 : 24
int setpgid(int pid, int pgrp){}; // 29 (-5) : 8 : 24
int getpgrp(){}; // 14 (-3) : 2 : 11
int setpgrp(){}; // 12 : 2
int getsid(){}; // 28 (-5) : 2 : 23
int setsid(){}; // 15 (-5) : 2 : 23

// Process mgmt
void _exit(int status){}; // 20 : 5 : 20
int fork(){}; // 23 (-9) : 2 : 14
int kill(int pid, int sig){}; // 29 (-4) : 8 : 25
int killpg(int pgid, int str){}; // 29 (-4) : 8 : 25
void abort(); // 12 (-4) : 2 : 8

// Filesystem
int chdir(char * dir){}; // 12 @1 : 4 : 18.7
int chroot(char *dir){}; // 12 @1 : 4 : 18.7
int fchdir(int des){}; // 11 : 5
int link(char * old, char * new){}; // 12 @2 : 6 : 21.7
int rename(char * old, char * new){}; // 12 @2 : 6 : 21.7
int rmdir(char * dir){}; // 12 @1 : 4 : 18.7
int system(char * cmd){}; // 25 (-2) : 4 : 23
int umask(int mask){}; // 28 (-5) : 5 : 23
int unlink(char * path){}; // 12 @1 : 4 : 18.7
int symlink(char * src, char * dst){}; // 12 @1 : 6 : 21.7
int mkfifo(char* filename, int mode){}; // 38 (-7) : 7 : 31
int tempnam(char* directory, char* prefix){}; // 51 (-14) : 6 : 45

// Files
int open( char* name, int flags){}; // 44 (-8) : 7 : 36
int close(int fd){}; // 31 (-7) : 5 : 24
int dup(int fd){}; // 30 (-7) : 5 : 23
int dup2(int fd){}; // 34 (-7) : 5 : 27
int isatty(int fd){}; // 20 : 5 : 20

// User
unsigned int getuid(){}; // 11 : 3 : 11
int setuid(int uid){}; // 26 (-4) : 5 : 22
int setgid(int gid){}; // 26 (-4) : 5 : 22
int seteuid(int euid){}; // 27 (-5) : 5 : 22
int setegid(int euid){}; // 27 (-5) : 5 : 22
int setreuid(int ruid, int euid){}; // 29 (-5) : 8 : 24
int setregid(int rgid, int egid){}; // 29 (-5) : 8 : 24
char* getlogin(){}; // 35 (-11) : 2 : 26
int getegid(){}; // 11 : 2 : 11
int geteuid(){}; // 11 : 2 : 11
int getgid(){}; // 11 : 2 : 11

// Environment
char *getenv(char* name){}; // 13 : 4 : 13 
int unsetenv(char* name){}; // 29 : 4 : 29
int setenv(char* name, char* value){}; // 73 (-19) : 6 : 64

// Errors
char *strerror(int code){}; // 32 (-8) : 5 : 24

/*
a a(){}; // : 19 : 26
a b(){}; // : 20 : 34
a c(){}; // : 25 : 69
a d(){}; // : 21 : 56
a e(){}; // : 40 : 88
a f(){}; // : 3  : 33
a g(){}; // : 3  : 26
a h(){}; // : 3  : 13
a i(){}; // : 3  : 21


*/

// ttyname
// ctermid
// fchdir
// fdatasync
// chmod
// chown
// lchown
// getcwdu
// listdir
// nice
// uname
// exec...
// spawn...
// fork1
// ...pty
// plock?
// popen..
// char* readlink(char* path){}; // 40 (-6)
// ...time...
// tc...
