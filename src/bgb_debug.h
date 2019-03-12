#ifdef DEBUG


#define CONCAT_(A, B, C) A ## B ## C
#define CONCAT(A, B, C) CONCAT_(A, B, C)

#define LOG_UNIQUE_LABEL CONCAT(42424200, __COUNTER__, $)

// Log a message to the BGB console
#define BGB_LOG_(LABEL, MESSAGE)  \
__asm                 \
    .db 0x52          \
    jr LABEL          \
    .dw 0x6464        \
    .dw 0x0000        \
    .str MESSAGE      \
    LABEL:            \
__endasm;
#define BGB_LOG(MESSAGE) BGB_LOG_(LOG_UNIQUE_LABEL, MESSAGE)

// Break in the BGB debugger
#define BGB_BREAK     \
__asm                 \
    .db 0x40          \
__endasm;


#else


#define BGB_LOG(MESSAGE)
#define BGB_BREAK


#endif
