/* This file contains the table used to map system call numbers onto the
 * routines that perform them.
 */

#define _TABLE

#include <minix/callnr.h>
#include <signal.h>

int (*call_vec[])(void) = {
	no_sys,		/*  0 = unused	*/
	no_sys,	/*  1 = exit	*/
	no_sys,	/*  2 = fork	*/
	no_sys,		/*  3 = read	*/
	no_sys, 	/*  4 = write	*/
	no_sys,		/*  5 = open	*/
	no_sys,		/*  6 = close	*/
	no_sys,	/*  7 = wait	*/
	no_sys,		/*  8 = creat	*/
	no_sys,		/*  9 = link	*/
	no_sys,		/* 10 = unlink	*/
	no_sys,	/* 11 = waitpid	*/
	no_sys,		/* 12 = chdir	*/
	no_sys,	/* 13 = time	*/
	no_sys,		/* 14 = mknod	*/
	no_sys,		/* 15 = chmod	*/
	no_sys,		/* 16 = chown	*/
	no_sys,		/* 17 = break	*/
	no_sys,		/* 18 = stat	*/
	no_sys,		/* 19 = lseek	*/
	no_sys,		/* 20 = getpid	*/
	no_sys,		/* 21 = mount	*/
	no_sys,		/* 22 = umount	*/
	no_sys,		/* 23 = setuid	*/
	no_sys,		/* 24 = getuid	*/
	no_sys,	/* 25 = stime	*/
	no_sys,	/* 26 = ptrace	*/
	no_sys,	/* 27 = alarm	*/
	no_sys,		/* 28 = fstat	*/
	no_sys,	/* 29 = pause	*/
	no_sys,		/* 30 = utime	*/
	no_sys,	/* 31 = getepinfo */
	no_sys, 	/* 32 = setgroups */
	no_sys,		/* 33 = access	*/
	no_sys,		/* 34 = getgroups */
	no_sys,		/* 35 = unused	*/
	no_sys,		/* 36 = sync	*/
	no_sys,	/* 37 = kill	*/
	no_sys,		/* 38 = rename	*/
	no_sys,		/* 39 = mkdir	*/
	no_sys,		/* 40 = rmdir	*/
	no_sys,		/* 41 = dup	*/
	no_sys,		/* 42 = pipe	*/
	no_sys,	/* 43 = times	*/
	no_sys,		/* 44 = unused	*/
	no_sys,		/* 45 = unused	*/
	no_sys,		/* 46 = setgid	*/
	no_sys,		/* 47 = getgid	*/
	no_sys,		/* 48 = (signal)*/
	no_sys,		/* 49 = unused	*/
	no_sys,		/* 50 = lstat	*/
	no_sys,		/* 51 = (stat)	*/
	no_sys,		/* 52 = (fstat)	*/
	no_sys,		/* 53 = (lstat)	*/
	no_sys,		/* 54 = ioctl	*/
	no_sys,		/* 55 = fcntl	*/
	no_sys,		/* 56 = unused	*/
	no_sys,		/* 57 = unused	*/
	no_sys,		/* 58 = unused	*/
	no_sys,	/* 59 = execve	*/
	no_sys,		/* 60 = umask	*/
	no_sys,		/* 61 = chroot	*/
	no_sys,		/* 62 = setsid	*/
	no_sys,		/* 63 = getpgrp	*/
	no_sys,	/* 64 = itimer  */
	no_sys,		/* 65 = getgroups */
	no_sys, 	/* 66 = setgroups */
	no_sys,	/* 67 = getmcontext */
	no_sys,	/* 68 = setmcontext */
	do_sem_init,		/* 69 = semaphore	*/
	no_sys,		/* 70 = unused	*/
	no_sys,	/* 71 = sigaction   */
	no_sys,	/* 72 = sigsuspend  */
	no_sys,	/* 73 = sigpending  */
	no_sys,	/* 74 = sigprocmask */
	no_sys,	/* 75 = sigreturn   */
	no_sys,	/* 76 = reboot	*/
	no_sys,	/* 77 = svrctl	*/
	no_sys,	/* 78 = sysuname */
	no_sys,		/* 79 = unused */
	no_sys,		/* 80 = (getdents) */
	no_sys, 	/* 81 = unused */
	no_sys, 	/* 82 = (fstatfs) */
	no_sys, 	/* 83 = unused */
	no_sys, 	/* 84 = unused */
	no_sys,		/* 85 = (select) */
	no_sys,		/* 86 = (fchdir) */
	no_sys,		/* 87 = (fsync) */
	no_sys, /* 88 = getpriority */
	no_sys, /* 89 = setpriority */
	no_sys,	/* 90 = gettimeofday */
	no_sys,		/* 91 = seteuid	*/
	no_sys,		/* 92 = setegid	*/
	no_sys,		/* 93 = (truncate) */
	no_sys,		/* 94 = (ftruncate) */
	no_sys,		/* 95 = (fchmod) */
	no_sys,		/* 96 = (fchown) */
	no_sys,		/* 97 = unused */
	no_sys,	/* 98 = sprofile */
	no_sys,	/* 99 = cprofile */
	no_sys,	/* 100 = newexec */
	no_sys,	/* 101 = srv_fork */
	no_sys,	/* 102 = exec_restart */
	no_sys,		/* 103 = unused */
	no_sys,	/* 104 = getprocnr */
	no_sys,		/* 105 = unused */
	no_sys,		/* 106 = issetugid */
	no_sys,	/* 107 = getepinfo XXX: old implementation*/
	do_sem_down,		/* 108 = semaphore down */
	do_sem_up,		/* 109 = semaphore up */
	do_sem_release,		/* 110 = semaphore release */
	no_sys,	/* 111 = srv_kill */
 	no_sys, 	/* 112 = gcov_flush */
	no_sys,		/* 113 = getsid	*/
};
/* This should not fail with "array size is negative": */
extern int dummy[sizeof(call_vec) == NCALLS * sizeof(call_vec[0]) ? 1 : -1];
