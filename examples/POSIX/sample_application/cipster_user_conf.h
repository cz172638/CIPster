/*******************************************************************************
 * Copyright (c) 2009, Rockwell Automation, Inc.
 * All rights reserved.
 *
 ******************************************************************************/
#ifndef CIPSTER_USER_CONF_H_
#define CIPSTER_USER_CONF_H_

/** @file cipster_user_conf.h
 * @brief CIPster configuration setup
 *
 * This file contains the general application specific configuration for CIPster.
 *
 * Furthermore you have to specific platform specific network include files.
 * CIPster needs definitions for the following data-types
 * and functions:
 *    - struct sockaddr_in
 *    - AF_INET
 *    - INADDR_ANY
 *    - htons
 *    - ntohl
 *    - inet_addr
 */

/// Identity configuration of the device
#define CIPSTER_DEVICE_VENDOR_ID         60000
#define CIPSTER_DEVICE_TYPE              12
#define CIPSTER_DEVICE_PRODUCT_CODE      65001
#define CIPSTER_DEVICE_MAJOR_REVISION    1
#define CIPSTER_DEVICE_MINOR_REVISION    2
#define CIPSTER_DEVICE_NAME              "amphibius goodie"


/** @brief Define the number of supported explicit connections.
 *  According to ODVA's PUB 70 this number should be greater than 6.
 */
#define CIPSTER_CIP_NUM_EXPLICIT_CONNS 6

/** @brief Define the number of supported exclusive owner connections.
 *  Each of these connections has to be configured with the function
 *  void configureExclusiveOwnerConnectionPoint(unsigned int pa_unConnNum,
 *   unsigned int pa_unOutputAssembly, unsigned int pa_unInputAssembly,
 *   unsigned int pa_unConfigAssembly )
 */
#define CIPSTER_CIP_NUM_EXCLUSIVE_OWNER_CONNS 5

/** @brief  Define the number of supported input only connections.
 *  Each of these connections has to be configured with the function
 *  void configureInputOnlyConnectionPoint(unsigned int pa_unConnNum,
 *   unsigned int pa_unOutputAssembly, unsigned int pa_unInputAssembly,
 *   unsigned int pa_unConfigAssembly)
 */
#define CIPSTER_CIP_NUM_INPUT_ONLY_CONNS 5

/** @brief Define the number of supported input only connections per connection path
 */
#define CIPSTER_CIP_NUM_INPUT_ONLY_CONNS_PER_CON_PATH 3

/** @brief Define the number of supported listen only connections.
 *  Each of these connections has to be configured with the function
 *  void configureListenOnlyConnectionPoint(unsigned int pa_unConnNum,
 *    unsigned int pa_unOutputAssembly, unsigned int pa_unInputAssembly,
 *    unsigned int pa_unConfigAssembly)
 *
 */
#define CIPSTER_CIP_NUM_LISTEN_ONLY_CONNS 5

/** @brief Define the number of supported Listen only connections per connection path
 */
#define CIPSTER_CIP_NUM_LISTEN_ONLY_CONNS_PER_CON_PATH   3

/**
 * The number of bytes used for the Ethernet message buffer.
 *
 * This buffer size will be used for any received message.
 */
#define CIPSTER_ETHERNET_BUFFER_SIZE        1800

/**
 *  The number of bytes used for the buffer that will be used for generating any
 *  reply data of messages. There are two uses in CIPster:
 *    1. Explicit messages will use this buffer to store the data generated by the request
 *    2. I/O Connections will use this buffer for the produced data
 */
#define CIPSTER_MESSAGE_DATA_REPLY_BUFFER    1600


/** @brief Number of sessions that can be handled at the same time
 */
#define CIPSTER_NUMBER_OF_SUPPORTED_SESSIONS 20

/**
 * The clock period in usecs of the timer used in this implementation.
 * It should be a multiple of milliseconds expressed in microseconds,
 * i.e. the last 3 digits *should* be zero because of
 * Vol1 3-4.4.9 Expected_packet_rate is expressed
 * in milliseconds.  However, whether this is mandatory given the jitter
 * associated with the call frequency to NetworkHandlerProcessOnce()
 * seems questionable.
 */
const unsigned kCIPsterTimerTickInMicroSeconds = 10000;

/**
 * The setting of this affects the real time format of
 * the consuming half of a kConnTransportClass0 or kConnTransportClass1
 * I/O connection.
 * Tells whether the 32 bit RUN IDLE dword is expected in consumed data.
 * When this is set to true, then the real time format is
 * 32-bit header format.  When false then modeless.  You may change these
 * settings for every IO connection separately using
 * ConnectionData::SetConsumingFmt() and ConnectionData::SetProducingRTFmt() if
 * the defaults controlled by this constant do not meet your needs.  But that
 * would make what the EDS file advertises as being inconsistent.
 * @see Vol1 3-6.1
 */
const bool kCIPsterConsumedDataHasRunIdleHeader = true;

/**
 * The setting of this affects the real time format of
 * the consuming half of a kConnTransportClass0 or kConnTransportClass1
 * I/O connection.
 * Tells whether the 32 bit RUN IDLE dword is expected in consumed data.
 * When this is set to true, then the real time format is
 * 32-bit header format.  When false then modeless.  You may change these
 * settings for every IO connection separately using
 * ConnectionData::SetConsumingFmt() and ConnectionData::SetProducingRTFmt() if
 * the defaults controlled by this constant do not meet your needs.  But that
 * would make what the EDS file advertises as being inconsistent.
 * @see Vol1 3-6.1
 */
const bool kCIPsterProducedDataHasRunIdleHeader = false;

#ifdef CIPSTER_WITH_TRACES
// If we have tracing enabled provide print tracing macro
#include <stdio.h>

#define LOG_TRACE(...)  printf(__VA_ARGS__)

#ifndef NDEBUG      // for "Debug" builds

#if 0
#define CIPSTER_ASSERT(assertion) \
    do { \
      if(!(assertion)) { \
        LOG_TRACE("Assertion \"%s\" failed: file \"%s\", line %d\n", #assertion, __FILE__, __LINE__); \
        while(1){;} \
      } \
    } while(0)
#else
#include <assert.h>
#define CIPSTER_ASSERT(assertion)   assert(assertion)
#endif

// could use standard assert()
//#include <assert.h>
//#define CIPSTER_ASSERT(assertion) assert(assertion)

#else   // for "Release" builds

#define CIPSTER_ASSERT(x)   // nothing
#endif  // NDEBUG

#else   // no CIPSTER_WITH_TRACES
#define LOG_TRACE(x)        // nothing
#define CIPSTER_ASSERT(x)   // nothing
#endif

#endif  // CIPSTER_USER_CONF_H_
