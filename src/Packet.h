#ifndef Packet_H
#define Packet_H

char *gdbCreateMsgPacket(char *data);
void destroyPacket(char *packet);

char *createdHexToString(unsigned int regVal, int bits);
void destroyHexToString(char *asciiString);

#endif // Packet_H
