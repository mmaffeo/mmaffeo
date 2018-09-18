
#ifndef stdint_h
#define stdint_h


typedef   signed char   int8_t;    //  8-bit   signed value
typedef unsigned char  uint8_t;    //  8-bit unsigned value
typedef           int  int16_t;    // 16-bit   signed value
typedef unsigned  int uint16_t;    // 16-bit unsigned value
typedef          long  int32_t;    // 32-bit   signed value
typedef unsigned long uint32_t;    // 32-bit unsigned value



#define INT8_MIN    (-0x7f - 1)
#define INT16_MIN   (-0x7fff - 1)
#define INT32_MIN   (-0x7fffffff - 1)

#define INT8_MAX    0x7f
#define INT16_MAX   0x7fff
#define INT32_MAX   0x7fffffff


#define UINT8_MAX   0xff
#define UINT16_MAX  0xffff
#define UINT32_MAX  0xffffffff


#endif