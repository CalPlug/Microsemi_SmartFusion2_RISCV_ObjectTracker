/*

 * Pixy.h
 *
 *  Created on: Nov 9, 2017
 *      Author: REN
*/


#ifndef SRC_PIXY_H_
#define SRC_PIXY_H_

#include "drivers/CoreSPI/core_spi.h"


#define PIXY_ARRAYSIZE              130
#define PIXY_START_WORD             0xaa55
#define PIXY_START_WORD_CC          0xaa56
#define PIXY_START_WORDX            0x55aa
#define PIXY_SERVO_SYNC             0xff
#define PIXY_CAM_BRIGHTNESS_SYNC    0xfe
#define PIXY_LED_SYNC               0xfd
#define PIXY_OUTBUF_SIZE            16

#define PIXY_SYNC_BYTE              0x5a
#define PIXY_SYNC_BYTE_DATA         0x5b



typedef enum
{
    NORMAL_BLOCK,
    CC_BLOCK // color code block
} BlockType;

typedef struct
{
  uint16_t signature;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  uint16_t angle; // angle is only available for color coded blocks
} Block;


// the routines

int getStart(spi_instance_t * this_spi);
uint16_t getBlocks(spi_instance_t * this_spi,uint16_t maxBlocks, uint16_t block[]);
uint8_t getByte( spi_instance_t * this_spi, uint8_t out);
uint16_t getWord(spi_instance_t * this_spi);
int send(uint8_t *data, int len);
int setServos(uint16_t s0, uint16_t s1);
#endif  SRC_PIXY_H_