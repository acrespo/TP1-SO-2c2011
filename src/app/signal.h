#ifndef __APP_SIGNAL__
#define __APP_SIGNAL__

void register_exit_function(void (*onExit)(void));

void register_signal_handlers(void);

void redirect_signals(void);

#endif
