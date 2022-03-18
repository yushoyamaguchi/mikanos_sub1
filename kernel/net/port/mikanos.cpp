#include <cstdio>
#include <ctime>
#include <cctype>
#include <cerrno>
#include <sys/time.h>

#include "task.hpp"
#include "timer.hpp"
#include "logger.hpp"

#include "net/util.h"

void
flockfile(FILE *fp)
{
    // ignore
}

void
funlockfile(FILE *fp)
{
    // ignore
}

int
gettimeofday(struct timeval *tv, void *tz)
{
    unsigned long tick = timer_manager->CurrentTick();

    tv->tv_sec = tick / kTimerFreq;
    tv->tv_usec = tick % kTimerFreq * (1000000 / kTimerFreq);
    return 0;
}

int
lprintf(FILE *fp, int level, const char *file, int line, const char *func, const char *fmt, ...)
{
    struct timeval tv;
    struct tm tm;
    char timestamp[32];
    char buf[1024];
    int n = 0;
    va_list ap;

    gettimeofday(&tv, NULL);
    strftime(timestamp, sizeof(timestamp), "%T", localtime_r(&tv.tv_sec, &tm));
    n += sprintf(buf, "%s.%03d [%c] %s: ", timestamp, (int)(tv.tv_usec / 1000), level, func);
    va_start(ap, fmt);
    n += vsprintf(buf + n, fmt, ap);
    va_end(ap);
    n += sprintf(buf + n, " (%s:%d)\n", file, line);
    flockfile(fp);
    Log(kWarn, "%s", buf);
    funlockfile(fp);
    return n;
}

void
hexdump(FILE *fp, const void *data, size_t size)
{
    unsigned char *src;
    int offset, index;

    flockfile(fp);
    src = (unsigned char *)data;
    fprintf(fp, "+------+-------------------------------------------------+------------------+\n");
    for(offset = 0; offset < (int)size; offset += 16) {
        fprintf(fp, "| %04x | ", offset);
        for(index = 0; index < 16; index++) {
            if(offset + index < (int)size) {
                fprintf(fp, "%02x ", 0xff & src[offset + index]);
            } else {
                fprintf(fp, "   ");
            }
        }
        fprintf(fp, "| ");
        for(index = 0; index < 16; index++) {
            if(offset + index < (int)size) {
                if(isascii(src[offset + index]) && isprint(src[offset + index])) {
                    fprintf(fp, "%c", src[offset + index]);
                } else {
                    fprintf(fp, ".");
                }
            } else {
                fprintf(fp, " ");
            }
        }
        fprintf(fp, " |\n");
    }
    fprintf(fp, "+------+-------------------------------------------------+------------------+\n");
    funlockfile(fp);
}

int
mutex_init(mutex_t *mutex, const void *attr)
{
    return 0;
}

int
mutex_lock(mutex_t *mutex)
{
    return 0;
}

int
mutex_unlock(mutex_t *mutex)
{
    return 0;
}

int
cond_init(cond_t *cond, const void *attr)
{
    cond->taskid = 0;
    cond->num = 0;
    return 0;
}

int
cond_wait(cond_t *cond, mutex_t *mutex)
{
    cond->taskid = task_manager->CurrentTask().ID();
    cond->num++;
    task_manager->Sleep(cond->taskid);
    cond->num--;
    return 0;
}

int
cond_broadcast(cond_t *cond)
{
    task_manager->Wakeup(cond->taskid);
    return 0;
}

int
cond_destroy(cond_t *cond)
{
    if (cond->num) {
        return EBUSY;
    }
    cond->taskid = 0;
    cond->num = 0;
    return 0;
}

void
softirq(void)
{
    // TODO: implement
}