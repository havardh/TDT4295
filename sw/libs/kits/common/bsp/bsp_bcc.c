/***************************************************************************//**
 * @file
 * @brief Board Controller Communications (BCC) definitions
 * @author Energy Micro AS
 * @version 3.20.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2013 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 4. The source and compiled code may only be used on Energy Micro "EFM32"
 *    microcontrollers and "EFR4" radios.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
#include <string.h>
#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"

#include "bsp.h"

#if defined( BSP_STK )

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/* Module local variables */
static USART_InitAsync_TypeDef usartInit = USART_INITASYNC_DEFAULT;
static uint32_t rxByteCount;
static uint32_t txByteCount;

/* Module local prototypes */
static void    TxByte( uint8_t data );
static uint8_t RxByte( void );

/** @endcond */

/***************************************************************************//**
 * @addtogroup BSP
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup BSP_STK API for STK's
 * @{
 ******************************************************************************/

/**************************************************************************//**
 * @brief Deinitialize board controller communication support (BCC)
 *        functionality. Reverse actions performed by @ref BSP_BccInit().
 *
 * @return @ref BSP_STATUS_OK.
 *****************************************************************************/
int BSP_BccDeInit( void )
{
  /* Reset counters */
  rxByteCount = 0xFFFFFFFFUL;
  txByteCount = 0xFFFFFFFFUL;

  /* Set USART TX GPIO pin mode to input. */
  GPIO_PinModeSet( BSP_BCC_USART_TXPORT, BSP_BCC_USART_TXPIN,
                   gpioModeInput, 0 );

  /* Set USART RX GPIO pin mode to input. */
  GPIO_PinModeSet( BSP_BCC_USART_RXPORT, BSP_BCC_USART_RXPIN,
                   gpioModeInput, 0 );

  /* Disable switch U602A "VMCU switch" - to disable USART communication. */
  /* See board schematics for details. */
  GPIO_PinModeSet( BSP_BCC_U602A_PORT, BSP_BCC_U602A_PIN,
                   gpioModeInput, 0 );

  /* Reset USART */
  USART_Reset( BSP_BCC_USART );

  /* Disable clock */
  CMU_ClockEnable( BSP_BCC_USART_CLK, false );

  return BSP_STATUS_OK;
}

/**************************************************************************//**
 * @brief Initialize board controller communication support (BCC)
 *        functionality.
 *
 * @return @ref BSP_STATUS_OK.
 *****************************************************************************/
int BSP_BccInit( void )
{
  rxByteCount = 0;
  txByteCount = 0;

  /* Enable High Frequency Peripherals */
  CMU_ClockEnable(cmuClock_HFPER, true);

  /* Enable clocks to GPIO */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure GPIO pin for USART TX */
  /* To avoid false start, configure output as high. */
  GPIO_PinModeSet( BSP_BCC_USART_TXPORT, BSP_BCC_USART_TXPIN,
                   gpioModePushPull, 1 );

  /* Configure GPIO pin for USART RX */
  GPIO_PinModeSet( BSP_BCC_USART_RXPORT, BSP_BCC_USART_RXPIN,
                   gpioModeInput, 1 );

  /* Enable switch U602A "VMCU switch" - to enable USART communication. */
  /* See board schematics for details. */
  GPIO_PinModeSet( BSP_BCC_U602A_PORT, BSP_BCC_U602A_PIN,
                   gpioModePushPull, 1 );

  CMU_ClockEnable( BSP_BCC_USART_CLK, true );

  /* Initialize USART */
  USART_InitAsync( BSP_BCC_USART, &usartInit );

  /* Enable correct USART location. */
  BSP_BCC_USART->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN |
                         BSP_BCC_USART_LOCATION;

  return BSP_STATUS_OK;
}

/**************************************************************************//**
 * @brief Get a packet from the board controller.
 *
 * @param[in] pkt Pointer to a @ref BCP_Packet instance.
 *
 * @return True if packet received without errors, false otherwise.
 *****************************************************************************/
bool BSP_BccPacketReceive( BCP_Packet *pkt )
{
  int i;
  int length;
  uint8_t *bptr;

  /* Setup a byte pointer to start of packet buffer */
  bptr   = (uint8_t *) pkt;

  /* Receive packet magic */
  *bptr++ = RxByte();
  if (pkt->magic != BSP_BCP_MAGIC)
  {
     return false;
  }

  /* Receive packet type */
  *bptr++ = RxByte();
  if ( (pkt->type < BSP_BCP_FIRST) || (pkt->type > BSP_BCP_LAST) )
  {
     return false;
  }

  /* Receive packet length */
  *bptr++ = RxByte();
  if (pkt->payloadLength > BSP_BCP_PACKET_SIZE)
  {
     return false;
  }

#if ( BSP_BCP_VERSION == 2 )
   /* Receive reserved byte */
   *bptr++ = RxByte();
#endif

  /* Receive packet data length field and sanity check it */
  length  = pkt->payloadLength;
  if (length > BSP_BCP_PACKET_SIZE)
  {
     length = BSP_BCP_PACKET_SIZE;
  }

  /* Receive packet payload */
  for( i=0; i<length; i++ )
  {
     *bptr++ = RxByte();
  }

  return true;
}

/**************************************************************************//**
 * @brief Send a packet to the board controller.
 *
 * @param[in] pkt Pointer to a @ref BCP_Packet instance.
 *
 * @return @ref BSP_STATUS_OK.
 *****************************************************************************/
int BSP_BccPacketSend( BCP_Packet *pkt )
{
  int i;

  /* Apply magic */
  pkt->magic = BSP_BCP_MAGIC;

  /* Transmit packet magic */
  TxByte( pkt->magic );

  /* Transmit packet type */
  TxByte( pkt->type );

  /* Transmit packet length */
  TxByte( pkt->payloadLength );

#if ( BSP_BCP_VERSION == 2 )
  /* Transmit reserved byte */
  TxByte( pkt->reserved );
#endif

  /* Transmit packet payload */
  for ( i=0; i<pkt->payloadLength; i++ )
  {
    TxByte( pkt->data[i] );
  }

  return BSP_STATUS_OK;
}

/**************************************************************************//**
 * @brief Get pointer to current USART instance used for board controller
 *        communication (BCC).
 *
 * @return Pointer to a USART_TypeDef instance.
 *****************************************************************************/
USART_TypeDef *BSP_BccUsartGet( void )
{
  return BSP_BCC_USART;
}

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

static uint8_t RxByte( void )
{
  uint8_t byte;

  /* Poll RX data available flag and return a character when one is available */
  while (!(BSP_BCC_USART->STATUS & USART_STATUS_RXDATAV)) ;
  byte = BSP_BCC_USART->RXDATA;
  rxByteCount++;
  return byte;
}

static void TxByte( uint8_t data )
{
  /* Check TX buffer and allow for a pending transfer to complete */
  while (!(BSP_BCC_USART->STATUS & USART_STATUS_TXBL)) ;
  BSP_BCC_USART->TXDATA = (uint32_t) data;
  txByteCount++;
}

/** @endcond */

/** @} (end group BSP_STK) */
/** @} (end group BSP) */

#endif /* BSP_STK */
