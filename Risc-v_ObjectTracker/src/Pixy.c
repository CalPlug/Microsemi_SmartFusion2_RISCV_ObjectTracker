/*
 * Pixy.c
 *
 *  Created on: Nov 9, 2017
 *      Author: Yutian Ren
 *
 * Extended from the Pixy Init Guide
 * Originial code is available here:
 * http://cmucam.org/projects/cmucam5/wiki/Porting_Guide
*/


#include "src/Pixy.h"
#include "drivers/CoreSPI/core_spi.h"


// data types

// communication routines


// SPI sends as it receives so we need a getByte routine that
// takes an output data argument

// variables for a little circular queue



uint8_t getByte( spi_instance_t * this_spi, uint8_t out)
{
	uint32_t buffer;
	SPI_set_slave_select( this_spi, SPI_SLAVE_0) ;
	buffer=SPI_transfer_frame(this_spi,out);
	SPI_clear_slave_select( this_spi, SPI_SLAVE_0 );
	uint8_t byte=0;
	//byte &=buffer>>24;
	byte = (uint8_t)buffer;
	return byte;
}

static uint8_t g_outBuf[PIXY_OUTBUF_SIZE];
static uint8_t g_outLen = 0;
static uint8_t g_outWriteIndex = 0;
static uint8_t g_outReadIndex = 0;

uint16_t getWord(spi_instance_t * this_spi)
{
  // ordering is big endian because Pixy is sending 16 bits through SPI
  uint16_t w;
  uint8_t c, cout = 0;

  if (g_outLen)
  {
    w = getByte(this_spi,PIXY_SYNC_BYTE_DATA);
    cout = g_outBuf[g_outReadIndex++];
    g_outLen--;
    if (g_outReadIndex==PIXY_OUTBUF_SIZE)
      g_outReadIndex = 0;
  }
  else
    w = getByte(this_spi,PIXY_SYNC_BYTE); // send out sync byte
  w <<= 8;
  c = getByte(this_spi,cout); // send out data byte
  w |= c;

  return w;
}


int send(uint8_t *data, int len)
{
  int i;

  // check to see if we have enough space in our circular queue
  if (g_outLen+len>PIXY_OUTBUF_SIZE)
    return -1;

  g_outLen += len;
  for (i=0; i<len; i++)
  {
    g_outBuf[g_outWriteIndex++] = data[i];
    if (g_outWriteIndex==PIXY_OUTBUF_SIZE)
      g_outWriteIndex = 0;
  }
  return len;
}


static int g_skipStart = 0;
static BlockType g_blockType;
static Block *g_blocks;

int getStart(spi_instance_t * this_spi)
{
  uint16_t w, lastw;

  lastw = 0xffff;

  while(1)
  {
    w = getWord(this_spi);
    if (w==0 && lastw==0)
      return 0; // no start code
    else if (w==PIXY_START_WORD && lastw==PIXY_START_WORD)
    {
      g_blockType = NORMAL_BLOCK;
      return 1; // code found!
    }
    else if (w==PIXY_START_WORD_CC && lastw==PIXY_START_WORD)
    {
      g_blockType = CC_BLOCK; // found color code block
      return 1;
    }
    else if (w==PIXY_START_WORDX)
#ifdef SPI
      getByte(this_spi,0); // we're out of sync! (backwards)
#else
      getByte(this_spi,0); // we're out of sync! (backwards)
#endif
    lastw = w;
  }
}

uint16_t getBlocks(spi_instance_t * this_spi,uint16_t maxBlocks, uint16_t block[])
{
  uint8_t i;
  uint16_t w, blockCount, checksum, sum;
  block[0]=0;
  block[1]=0;
  block[2]=0;
  block[3]=0;
  block[4]=0;
  block[5]=0;
//  Block *block;
//  uint16_t block[6];

  if (!g_skipStart)
  {
    if (getStart(this_spi)==0)
    {
    	return 0;
    }

  }
  else
    g_skipStart = 0;

  for(blockCount=0; blockCount<maxBlocks && blockCount<PIXY_ARRAYSIZE;)
  {
    checksum = getWord(this_spi);
    if (checksum==PIXY_START_WORD) // we've reached the beginning of the next frame
    {
      g_skipStart = 1;
      g_blockType = NORMAL_BLOCK;

      return blockCount;
    }
    else if (checksum==PIXY_START_WORD_CC)
    {
      g_skipStart = 1;
      g_blockType = CC_BLOCK;
      return blockCount;
    }
    else if (checksum==0)
    {

        return blockCount;
    }


//    block = g_blocks + blockCount;
    //i<sizeof(Block)/sizeof(uint16_t)

    for (i=0, sum=0; i<6; i++)
    {
      if (g_blockType==NORMAL_BLOCK && i>=5) // no angle for normal block
      {
        //block->angle = 0;
    	  block[5]=0;
        break;
      }
      w = getWord(this_spi);
      sum += w;
      //*((uint16_t *)block + i) = w;
      block[i]=w;
    }

    // check checksum
    if (checksum==sum)
      blockCount++;


    w = getWord(this_spi);
    if (w==PIXY_START_WORD)
      g_blockType = NORMAL_BLOCK;
    else if (w==PIXY_START_WORD_CC)
      g_blockType = CC_BLOCK;
    else
      return blockCount;
  }
}

int setServos(uint16_t s0, uint16_t s1)
{
  uint8_t outBuf[6];

  outBuf[0] = 0x00;
  outBuf[1] = PIXY_SERVO_SYNC;
  *(uint16_t *)(outBuf + 2) = s0;
  *(uint16_t *)(outBuf + 4) = s1;

  return send(outBuf, 6);
}

