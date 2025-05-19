#include "types.h"

extern uint64 kbd_int_count;

uint64
sys_kbdint(){

return kbd_int_count;
}
