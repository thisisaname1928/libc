#include <errno.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>

static inline void do_a_yield(void) {
#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) ||             \
    defined(_M_IX86)
  __asm__ __volatile__("pause" ::: "memory");
#elif defined(__aarch64__) || defined(_M_ARM64)
  __asm__ __volatile__("yield" ::: "memory");
#else
  sleep(20); // just sleep a little bit on strange arch
#endif
}

static void internal_lock(sem_t *sem) {
  // do a atomic set
  while (atomic_flag_test_and_set_explicit(&sem->internal_spinlock,
                                           memory_order_acquire)) {
    do_a_yield();
  }
  return;
}

static void internal_unlock(sem_t *sem) {
  atomic_flag_clear_explicit(&sem->internal_spinlock, memory_order_release);
}

int sem_init(sem_t *sem, int pshared, unsigned int val) {
  if (!sem) {
    errno = EINVAL;
    return -1;
  }

  // sem_t already init
  if (sem->sem_init_magic == SEM_INIT_MAGIC) {
    errno = EBUSY;
    return -1;
  }

  if (val > SEM_VALUE_MAX) {
    errno = EINVAL;
    return -1;
  }

  sem->value = val;
  sem->initial_value = val;
  sem->pshared = pshared;
  sem->sem_init_magic = SEM_INIT_MAGIC; // use this magic to avoid double init or doing some stuffs on a uninitialized semaphore
  atomic_flag_clear_explicit(&sem->internal_spinlock, memory_order_release);

  // I'll not implement this...
  if (pshared == 1) {
    errno = ENOSYS;
    return -1;
  }

  return 0;
}

int sem_destroy(sem_t *sem) {
  if (!sem) {
    errno = EINVAL;
    return -1;
  }

  // just set the init magic to zero
  if (sem->sem_init_magic != SEM_INIT_MAGIC) {
    errno = EINVAL;
    return -1;
  }

    // wait for permission to modify the semaphore
  internal_lock(sem);
  sem->sem_init_magic = 0;
  sem->value = 0;
  internal_unlock(sem);

  return 0;
}

int sem_wait(sem_t *sem) {
  if (!sem) {
    errno = EINVAL;
    return -1;
  }

  if (sem->sem_init_magic != SEM_INIT_MAGIC) {
    errno = EINVAL;
    return -1;
  }

  // wait for resource
  while (true) {
    internal_lock(sem);
    if (sem->value != 0) { // find a free spot
      sem->value--;
      internal_unlock(sem);
      return 0;
    }

    internal_unlock(sem);
    do_a_yield(); // let cpu be relax a little bit
  }

  return 0;
}

int sem_trywait(sem_t *sem) {
  if (!sem) {
    errno = EINVAL;
    return -1;
  }

  if (sem->sem_init_magic != SEM_INIT_MAGIC) {
    errno = EINVAL;
    return -1;
  }

    // wait for permission to modify the semaphore
  internal_lock(sem);
  if (sem->value == 0) {
    errno = EAGAIN; // tell the caller that semaphore value is ran out, try again later
    internal_unlock(sem);
    return -1;
  }

  sem->value--;
  internal_unlock(sem);
  return 0;
}

// increment a semaphore
int sem_post(sem_t *sem) {
  if (!sem) {
    errno = EINVAL;
    return -1;
  }

  if (sem->sem_init_magic != SEM_INIT_MAGIC) {
    errno = EINVAL;
    return -1;
  }

  // wait for permission to modify the semaphore
  internal_lock(sem);
  if (sem->value < SEM_VALUE_MAX)
    sem->value++;
  else {
    errno = EOVERFLOW;
    internal_unlock(sem);
    return -1;
  }
  internal_unlock(sem);

  return 0;
}

// get the sem_t's current value
int sem_getvalue(sem_t *restrict sem, int *v) {
  if (!sem || !v || sem->sem_init_magic != SEM_INIT_MAGIC) {
    errno = EINVAL;
    return -1;
  }
  
  *v = sem->value;

  return 0;
}

// not supported functions

sem_t *sem_open(const char *name, int oflag, ...) {
  errno = ENOSYS;
  return SEM_FAILED;
}

int sem_timedwait(sem_t *restrict sem, const struct timespec ts) {
  errno = ENOSYS;
  return -1;
}

int sem_unlink(const char * name) {
  errno = ENOSYS;
  return -1;
}

int sem_close(sem_t * sem) { 
  errno = ENOSYS;
  return -1;
}