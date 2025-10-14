# millis-for-AVR128DB48
This library uses a timer to implement the well known millis() function from the arduino framework on the AVR128DB48 microcontroller. The library uses the TCA0 timer to implement this functionality.

## How to use
1. Copy `millis.c` and `millis.h` into your project.
2. `#include <millis.h>` in your `main.c`.
3. Call `millis_init()` once, and make sure global interrupts is enabled: `sei();`
4. Call `millis()` to get a milliseconds timestamp (`uint32_t`).  
