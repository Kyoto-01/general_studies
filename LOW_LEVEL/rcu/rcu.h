#include <time.h>

time_t last_rcu_enter;
time_t grace_period;

void rcu_enter() {
	last_rcu_enter = time(NULL);
}

void rcu_exit() {
	grace_period = time(NULL) - last_rcu_enter;
}
