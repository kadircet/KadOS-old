#ifndef KadOS_Port
#define KadOS_Port

inline void outportb(unsigned short port, unsigned char data);
inline unsigned char inportb(unsigned short port);
inline void outportw(unsigned short port, unsigned short data);
inline unsigned short inportw(unsigned short port);
inline void enable();
inline void disable();
inline void halt();

#endif