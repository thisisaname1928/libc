// Copyright (c) 2026 Quoc Trung (https://github.com/thisisaname1928)
// This software is released under the GNU General Public License v3.0. See
// LICENSE file for details. This header needs to maintain in any file it is
// present in, as per the GPL license terms.
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

/*
 * --- UNSUPPORTED POSIX SEMAPHORE FEATURES --
 * 1. Functions: sem_open(), sem_close(), sem_timedwait(), sem_unlink()
 */

typedef struct {
  _Atomic uint32_t value;
  int32_t pshared;
  _Atomic uint32_t waiter;
} sem_t;

#define SEM_FAILED ((sem_t *)-1)
#define SEM_VALUE_MAX 2147483647

int sem_close(sem_t *);
int sem_destroy(sem_t *);
int sem_getvalue(sem_t *restrict, int *);
int sem_init(sem_t *, int, unsigned);
sem_t *sem_open(const char *, int, ...);
int sem_post(sem_t *);
int sem_timedwait(sem_t *restrict, const struct timespec *restrict);
int sem_trywait(sem_t *);
int sem_unlink(const char *);
int sem_wait(sem_t *);

#endif