#ifdef DEBUG


#define CONCAT_(A, B) A ## B
#define CONCAT(A, B) CONCAT_(A, B)

#define LOG_UNIQUE_LABEL CONCAT(LOG_, __COUNTER__)

// Log a message to the BGB console
#define BGB_LOG(MESSAGE)  \
__asm                 \
    LOG_UNIQUE_LABEL: \
    .db 0x52          \
    jr 1$             \
    .dw 0x6464        \
    .dw 0x0000        \
    .str MESSAGE      \
    1$:               \
__endasm;

// Break in the BGB debugger
#define BGB_BREAK     \
__asm                 \
    .db 0x40          \
__endasm;


#else


#define BGB_LOG(MESSAGE)
#define BGB_BREAK


#endif
