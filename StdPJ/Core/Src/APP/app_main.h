#ifndef __APP_MAIN_H__
#define __APP_MAIN_H__

/****************************************************************/
/* コンパイルスイッチ */
/****************************************************************/
#define USE_WIFI
#define SENSOR
// #define NET_ENABLE
// #define RFU
// #define FIREWALL_MBEDLIB
/****************************************************************/
/* STD Lib */
/****************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
/****************************************************************/
/* DRV */
/****************************************************************/
#include "main.h"

#include "stm32l4xx_hal.h"
//#include "stm32l4xx_hal_iwdg.h"

//#include "version.h"

/****************************************************************/
/* BSP */
/****************************************************************/
#include "../APP/BSP/stm32l475e_iot01.h"

#ifdef RFU
#include "../Common/Shared/rfu.h"
#endif

#ifdef SENSOR
#include "../APP/BSP/stm32l475e_iot01_accelero.h"
#include "../APP/BSP/stm32l475e_iot01_psensor.h"
#include "../APP/BSP/stm32l475e_iot01_gyro.h"
#include "../APP/BSP/stm32l475e_iot01_hsensor.h"
#include "../APP/BSP/stm32l475e_iot01_tsensor.h"
#include "../APP/BSP/stm32l475e_iot01_magneto.h"
#include "../APP/BSP/vl53l0x/vl53l0x_proximity.h"
#endif
/****************************************************************/
/* BSP APP */
/****************************************************************/
#include "flash.h"

#include "../Common/Shared/version.h"
#include "../Common/Shared/sensors_data.h"
#include "../Common/Shared/cloud.h"
#include "../Common/Shared/timedate.h"
#include "../Common/Shared/msg.h"
#include "../Common/Shared/net.h"
#include "../Common/Shared/iot_flash_config.h"
#include "../Common/Exosite/Inc//exositehttp.h"

#ifdef FIREWALL_MBEDLIB
#include "firewall_wrapper.h"
#include "firewall.h"
#endif /* FIREWALL_MBEDLIB */

/****************************************************************/
/* FreeRTOS */
/****************************************************************/
#include "cmsis_os.h"

#ifndef configUSE_TRACE_FACILITY
#define configUSE_TRACE_FACILITY    1   /* vTaskList()のため */
#endif
/****************************************************************/
/* APP */
/****************************************************************/
// F/Wバージョン
#define FW_VERSION_NAME     "B-L475E-IOT01A1"
#if 0
#define FW_VERSION_MAJOR    0
#define FW_VERSION_MINOR    1
#define FW_VERSION_PATCH    0
#define FW_VERSION_DATE     "27-February-2021 00:00:0 AM"
#endif

#if defined(USE_WIFI)
#define NET_IF  NET_IF_WLAN
#elif defined(USE_LWIP)
#define NET_IF  NET_IF_ETH
#elif defined(USE_C2C)
#define NET_IF  NET_IF_C2C
#endif

// 真
#ifndef TRUE
#define TRUE    0x01
#endif

// 偽真真
#ifndef FALSE
#define FALSE   0x00
#endif

// UARTタイムアウト
#define UART_TIME_OUT   10

// 円周率　繰り返し精度
#define PI_ACCURACY     64
// 円周率　有効数字
#define PI_DIGIT        14
/****************************************************************/
// ボタン押し種別
typedef enum
{
    BP_NOT_PUSHED = 0,
    BP_SINGLE_PUSH,
    BP_MULTIPLE_PUSH
} BTN_E;

typedef enum
{
    CLOUD_DEMO_WIFI_INITIALIZATION_ERROR      = -2,
    CLOUD_DEMO_MAC_ADDRESS_ERROR              = -3,
    CLOUD_DEMO_WIFI_CONNECTION_ERROR          = -4,
    CLOUD_DEMO_IP_ADDRESS_ERROR               = -5,
    CLOUD_DEMO_CONNECTION_ERROR               = -6,
    CLOUD_DEMO_TIMEDATE_ERROR                 = -7,
    CLOUD_DEMO_C2C_INITIALIZATION_ERROR       = -8
} CLOUD_DEMO_Error_t;

#ifdef NET_ENABLE
extern int net_if_init(void * if_ctxt);
extern int net_if_deinit(void * if_ctxt);
extern int net_init(net_hnd_t * nethnd, net_if_t interface, net_if_init_t *f_netinit);
extern int net_deinit(net_hnd_t nethnd, net_if_deinit_t *f_netdeinit);

extern int platform_init(void);
#endif

#ifdef SENSOR
extern int init_sensors(void);
#endif

void APP_BSP_Init(void);
void APP_Init(void);
void APP_Main(void);
void App_Drv_Main(void);

/**
 * @brief 円周率計算（ガウス＝ルジャンドルのアルゴリズム）
 * 
 * @return float [OUT] : 円周率
 */
static inline double App_Math_PI( void )
{
    int i;
    double a,b,t,p,tmp,pi;

    a = 1.0F;
    b = 1.0F / sqrt(2.0F);
    t = 1.0F / 4;
    p = 1.0F;
    tmp = 0;

    for (i = 0; i < PI_ACCURACY; i++)
    {
        tmp = a;
        a = (tmp + b) / 2;
        b = sqrt(tmp * b);
        t = t - (p * (a - tmp) * (a - tmp));
        p = 2 * p;
    }

    pi = (a + b) * (a + b) / (4 * t);

    return pi;
}

#endif
