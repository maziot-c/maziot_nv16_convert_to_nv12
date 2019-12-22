#ifndef _MAZ_ERRORS_H
#define _MAZ_ERRORS_H

#define MAZIOT_NOERR        0

#define MAZIOT_EPERM        1       /* Operation not permitted */
#define MAZIOT_ENOENT       2       /* No such file or directory */
#define MAZIOT_ESRCH        3       /* No such process */
#define MAZIOT_EINTR        4       /* Interrupted system call */
#define MAZIOT_EIO          5       /* I/O error */
#define MAZIOT_ENXIO        6       /* No such device or address */
#define MAZIOT_E2BIG        7       /* Argument list too long */
#define MAZIOT_ENOEXEC      8       /* Exec format error */
#define MAZIOT_EBADF        9       /* Bad file number */
#define MAZIOT_ECHILD       10      /* No child processes */
#define MAZIOT_EAGAIN       11      /* Try again */
#define MAZIOT_ENOMEM       12      /* Out of memory */
#define MAZIOT_EACCES       13      /* Permission denied */
#define MAZIOT_EFAULT       14      /* Bad address */
#define MAZIOT_ENOTBLK      15      /* Block device required */
#define MAZIOT_EBUSY        16      /* Device or resource busy */
#define MAZIOT_EEXIST       17      /* File exists */
#define MAZIOT_EXDEV        18      /* Cross-device link */
#define MAZIOT_ENODEV       19      /* No such device */
#define MAZIOT_ENOTDIR      20      /* Not a directory */
#define MAZIOT_EISDIR       21      /* Is a directory */
#define MAZIOT_EINVAL       22      /* Invalid argument */
#define MAZIOT_ENFILE       23      /* File table overflow */
#define MAZIOT_EMFILE       24      /* Too many open files */
#define MAZIOT_ENOTTY       25      /* Not a typewriter */
#define MAZIOT_ETXTBSY      26      /* Text file busy */
#define MAZIOT_EFBIG        27      /* File too large */
#define MAZIOT_ENOSPC       28      /* No space left on device */
#define MAZIOT_ESPIPE       29      /* Illegal seek */
#define MAZIOT_EROFS        30      /* Read-only file system */
#define MAZIOT_EMLINK       31      /* Too many links */
#define MAZIOT_EPIPE        32      /* Broken pipe */
#define MAZIOT_EDOM         33      /* Math argument out of domain of func */
#define MAZIOT_ERANGE       34      /* Math result not representable */

#endif /* _MAZ_ERRORS_H */
