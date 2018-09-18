
#ifndef hw_vectors_h
#define hw_vectors_h


typedef void (*near tIsrFunc)(void);

extern const tIsrFunc hw_pvector_table[];

#endif
