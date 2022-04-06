#include <cstdio>
#include <ctime>
#include <cctype>
#include <cerrno>
#include <sys/time.h>

#include "variable.hpp"
#include "../net/util.h"
#include "../net/port/mikanos.hpp"




static int variable=0;

static mutex_t mutex={0};

int var_set(int val){
    variable+=val;
    return 1;
}

int var_get(){
    infof("var=%d",variable);
    return variable;
}


int var_plus_big(){
    int i=0;
    for(i=0;i<BIG;i++){
        mutex_lock(&mutex);
        variable+=1;
        mutex_unlock(&mutex);
    }
    return variable;
}

unsigned long create_timer_var(unsigned int type, int timer_value_param, unsigned long timeout_ms){
    const unsigned int mode = type;
    const int timer_value = timer_value_param;
    if (timer_value <= 0) {
        return  0;
    }

    __asm__("cli");
    const uint64_t task_id = task_manager->CurrentTask().ID();
    __asm__("sti");

    unsigned long timeout = timeout_ms * kTimerFreq / 1000;
    if (mode & 1) { // relative
        timeout += timer_manager->CurrentTick();
    }

    __asm__("cli");
    timer_manager->AddTimer(Timer{timeout, -timer_value, task_id});
    __asm__("sti");
    return  timeout * 1000 / kTimerFreq;
}

size_t read_event_var(struct AppEvent* events, size_t len_param){
    /*if ((uintptr_t)events < 0x8000'0000'0000'0000) {
        infof("read event mem error\n");
        return  0;
    }*/
    const auto app_events = reinterpret_cast<AppEvent*>(events);
    const size_t len = len_param;

    __asm__("cli");
    auto& task = task_manager->CurrentTask();
    __asm__("sti");
    size_t i = 0;

    while (i < len) {
        __asm__("cli");
        auto msg = task.ReceiveMessage();
        if (!msg && i == 0) {
            task.Sleep();
            continue;
        }
        __asm__("sti");

        if (!msg) {
            break;
        }

        switch (msg->type) {
        case Message::kKeyPush:
            if (msg->arg.keyboard.keycode == 20 /* Q key */ &&
                msg->arg.keyboard.modifier & (kLControlBitMask | kRControlBitMask)) {
            app_events[i].type = AppEvent::kQuit;
            ++i;
            } else {
            app_events[i].type = AppEvent::kKeyPush;
            app_events[i].arg.keypush.modifier = msg->arg.keyboard.modifier;
            app_events[i].arg.keypush.keycode = msg->arg.keyboard.keycode;
            app_events[i].arg.keypush.ascii = msg->arg.keyboard.ascii;
            app_events[i].arg.keypush.press = msg->arg.keyboard.press;
            ++i;
            }
            break;
        case Message::kMouseMove:
            app_events[i].type = AppEvent::kMouseMove;
            app_events[i].arg.mouse_move.x = msg->arg.mouse_move.x;
            app_events[i].arg.mouse_move.y = msg->arg.mouse_move.y;
            app_events[i].arg.mouse_move.dx = msg->arg.mouse_move.dx;
            app_events[i].arg.mouse_move.dy = msg->arg.mouse_move.dy;
            app_events[i].arg.mouse_move.buttons = msg->arg.mouse_move.buttons;
            ++i;
            break;
        case Message::kMouseButton:
            app_events[i].type = AppEvent::kMouseButton;
            app_events[i].arg.mouse_button.x = msg->arg.mouse_button.x;
            app_events[i].arg.mouse_button.y = msg->arg.mouse_button.y;
            app_events[i].arg.mouse_button.press = msg->arg.mouse_button.press;
            app_events[i].arg.mouse_button.button = msg->arg.mouse_button.button;
            ++i;
            break;
        case Message::kTimerTimeout:
            if (msg->arg.timer.value < 0) {
            app_events[i].type = AppEvent::kTimerTimeout;
            app_events[i].arg.timer.timeout = msg->arg.timer.timeout;
            app_events[i].arg.timer.value = -msg->arg.timer.value;
            ++i;
            }
            break;
        case Message::kWindowClose:
            app_events[i].type = AppEvent::kQuit;
            ++i;
            break;
        default:
            Log(kInfo, "uncaught event type: %u\n", msg->type);
        }
    }

    return  i;
}

void
sleep_var(unsigned long ms){
    const unsigned long duration_ms = (const unsigned long)ms;
    const auto timeout = create_timer_var(TIMER_ONESHOT_REL, 1, duration_ms);
    AppEvent events[1];
    while (true) {
        //SyscallReadEvent(events, 1);
        read_event_var(events,1);
        if (events[0].type == AppEvent::kTimerTimeout) {
            //infof("%lu msecs elapsed!\n", duration_ms);
            break;
        } else {
            //infof("unknown event: type = %d\n", events[0].type);
        }
    }
    return;
}

int isPrimeNumber(long n) {

    long i;

    if (n < 2) {
        /* 2未満の場合は素数でない */
        return 0;
    }

    /* nが2〜n-1で割り切れるかどうかを確認 */
    for (i = 2; i < n; i++) {
        if (n % i == 0) {
            /* 2〜n-1で割り切れる場合はnは素数でない */
            return 0;
        }
    }

    return 1;
}

int var_plus_one(){
    int buf=0;
    //mutex_lock(&mutex);
    buf=variable;
    //sleep_var(10);
    long p=0;
    int arr[BIG];
    while(p<=BIG){
        if(isPrimeNumber(p)){
            arr[p]=1;
        }
        p++;
    }
    variable=buf+1;
    //mutex_unlock(&mutex);
    const auto time=timer_manager->CurrentTick();
    infof("%d",arr[time]);
    return variable;
}