/*
 * Copyright (c) 2003 Roland McGrath <roland@redhat.com>
 * Copyright (c) 2003-2018 The strace developers.
 * All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#ifndef STRACE_IPC_DEFS_H
# define STRACE_IPC_DEFS_H

# ifdef HAVE_SYS_IPC_H
#  define USE_LIBC_IPC_DEFS 1
#  define USE_UAPI_IPC_DEFS 0
# elif defined HAVE_LINUX_IPC_H
#  define USE_UAPI_IPC_DEFS 1
#  define USE_LIBC_IPC_DEFS 0
# else
#  error Neither <sys/ipc.h> nor <linux/ipc.h> is available
# endif

# if USE_LIBC_IPC_DEFS
#  define IPC_H_PROVIDER <sys/ipc.h>
#  define MSG_H_PROVIDER <sys/msg.h>
#  define SEM_H_PROVIDER <sys/sem.h>
#  define SHM_H_PROVIDER <sys/shm.h>
#  define NAME_OF_STRUCT_MSQID_DS msqid_ds
#  define NAME_OF_STRUCT_SHMID_DS shmid_ds
# elif USE_UAPI_IPC_DEFS
#  define IPC_H_PROVIDER <linux/ipc.h>
#  define MSG_H_PROVIDER <linux/msg.h>
#  define SEM_H_PROVIDER <linux/sem.h>
#  define SHM_H_PROVIDER <linux/shm.h>
#  define NAME_OF_STRUCT_MSQID_DS msqid64_ds
#  define NAME_OF_STRUCT_SHMID_DS shmid64_ds
# endif

# include IPC_H_PROVIDER

# if USE_UAPI_IPC_DEFS
/* While glibc uses __key, the kernel uses key. */
#  define __key key
# endif

# if !defined IPC_64
#  define IPC_64 0x100
# endif

# define PRINTCTL(flagset, arg, dflt)				\
	do {							\
		if ((arg) & IPC_64) {				\
			print_xlat(IPC_64);			\
			tprints("|");				\
		}						\
		printxval((flagset), (arg) & ~IPC_64, dflt);	\
	} while (0)

#endif /* !STRACE_IPC_DEFS_H */
