#ifndef SRC_UTILS_PACK2_H_
#define SRC_UTILS_PACK2_H_

unsigned int pack(unsigned char *buf, const char *format, ...);
void unpack(unsigned char *buf, const char *format, ...);

#endif /* SRC_UTILS_PACK2_H_ */
