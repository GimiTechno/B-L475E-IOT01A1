#include "app_main.h"

// センサバッファサイズ
#define SENSOR_BUF_SIZE     1024

// RTC_HandleTypeDef hrtc;
// RNG_HandleTypeDef hrng;

static void uart_1_Init(void);
static int BSP_Init_Sensor(void);
static void APP_IoT_Init(void);
static void APP_Sensor_Read(char* sensor_val_buf ,uint32_t size);

// ネットワークハンドラ
net_hnd_t hnet;
// UARTハンドラ
static UART_HandleTypeDef uart_1;
// センサバッファ
static char s_sensor_buf[SENSOR_BUF_SIZE] = {0};

// F/W バージョン
const firmware_version_t version =
{
    FW_VERSION_NAME,
    FW_VERSION_MAJOR,
    FW_VERSION_MINOR,
    FW_VERSION_PATCH,
    FW_VERSION_DATE
};

/**
 * @brief For getchar() Porting
 * 
 * @return int 
 */
int __io_getchar(void)
{
    HAL_StatusTypeDef Status = HAL_BUSY;
    uint8_t Data;

    while(Status != HAL_OK)
    Status = HAL_UART_Receive(&uart_1, &Data, 1, 10);

    return(Data);
}
/**
 * @brief For getchar() Porting
 * 
 * @param file 
 * @param ptr 
 * @param len 
 * @return int 
 */
__attribute__((weak)) int _read(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		*ptr++ = __io_getchar();
	}

    return len;
}

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
 * @brief For printf() Porting
 * 
 * @param ch 
 */
void __io_putchar(uint8_t ch)
{
    HAL_UART_Transmit(&uart_1, &ch, 1, 1);
}

/**
 * @brief  For printf() Porting
 * 
 * @param file 
 * @param ptr 
 * @param len 
 * @return int 
 */
__attribute__((weak)) int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		__io_putchar(*ptr++);
	}

	return len;
}

/**
  * @brief UART console init function
  */
static void uart_1_Init(void)
{
    uart_1.Instance = USART1;
    uart_1.Init.BaudRate = 115200;
    uart_1.Init.WordLength = UART_WORDLENGTH_8B;
    uart_1.Init.StopBits = UART_STOPBITS_1;
    uart_1.Init.Parity = UART_PARITY_NONE;
    uart_1.Init.Mode = UART_MODE_TX_RX;
    uart_1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart_1.Init.OverSampling = UART_OVERSAMPLING_16;

#ifdef UART_ONE_BIT_SAMPLE_DISABLE
    uart_1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    uart_1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
#endif

    BSP_COM_Init(COM1,&uart_1);
}


/**
 * @brief IoT メイン　初期化
 * 
 */
void APP_IoT_Init(void)
{
    const firmware_version_t  *fw_version=&version;;
#ifdef NET_ENABLE
    net_ipaddr_t ipAddr;
    net_macaddr_t macAddr;
    unsigned int random_number = 0;
    bool skip_reconf = false;
#endif

    #ifdef HEAP_DEBUG
    stack_measure_prologue();
    #endif

#if 0
    /* Initialize the seed of the stdlib rand() SW implementation from the RNG. */
    if (HAL_RNG_GenerateRandomNumber(&hrng, (uint32_t *) &random_number) == HAL_OK)
    {
        srand(random_number);
    }
#endif
    printf("\r\n");
    printf("*************************************************************\r\n");
    printf("***   STM32 IoT Discovery kit for                         \r\n");
    printf("***   STM32F413/STM32F769/STM32L475/STM32L496 MCU      \r\n");
    printf("***   %s Cloud Connectivity Demonstration                 \r\n",fw_version->name);
    printf("***   F/W version %d.%d.%d - %s      \r\n",
            fw_version->major, fw_version->minor, fw_version->patch, fw_version->packaged_date);
    printf("*************************************************************\r\n");

#ifdef NET_ENABLE
    /* Network initialization */
    if (net_init(&hnet, NET_IF, (net_if_init)) != NET_OK)
    {
    #ifdef USE_C2C
        CLOUD_Error_Handler(CLOUD_DEMO_C2C_INITIALIZATION_ERROR);
    #else
        CLOUD_Error_Handler(CLOUD_DEMO_IP_ADDRESS_ERROR);
    #endif
        return -1;
    }

    if (net_get_mac_address(hnet, &macAddr) == NET_OK)
    {
        msg_info("Mac address: %02x:%02x:%02x:%02x:%02x:%02x\n",
                macAddr.mac[0], macAddr.mac[1], macAddr.mac[2], macAddr.mac[3], macAddr.mac[4], macAddr.mac[5]);
    }
    else
    {
        CLOUD_Error_Handler(CLOUD_DEMO_MAC_ADDRESS_ERROR);
        return -1;
    }

    /* Slight delay since the netif seems to take some time prior to being able
    to retrieve its IP address after a connection. */
    HAL_Delay(500);

    msg_info("Retrieving the IP address.\r\n");

    if (net_get_ip_address(hnet, &ipAddr) != NET_OK)
    {
        CLOUD_Error_Handler(CLOUD_DEMO_IP_ADDRESS_ERROR);
        return -1;
    }
    else
    {
        switch(ipAddr.ipv)
        {
        case NET_IP_V4:
            msg_info("IP address: %d.%d.%d.%d\r\n", ipAddr.ip[12], ipAddr.ip[13], ipAddr.ip[14], ipAddr.ip[15]);
            break;
        case NET_IP_V6:
        default:
            CLOUD_Error_Handler(CLOUD_DEMO_IP_ADDRESS_ERROR);
            return -1;
        }
    }
    /* End of network initialisation */

    /* Security and cloud parameters definition */
    /* Define, or allow to update if the user button is pushed. */
    skip_reconf = (checkTLSRootCA() == 0)
        && ( (checkTLSDeviceConfig() == 0) || !app_needs_device_keypair() )
        && (checkIoTDeviceConfig() == 0);

    if (skip_reconf == true)
    {
        printf("Push the User button (Blue) within the next 5 seconds if you want to update "
            "the device security parameters or credentials.\n\n");
        skip_reconf = (Button_WaitForPush(5000) == BP_NOT_PUSHED);
    }

    if (skip_reconf == false)
    {
        if ((checkIoTDeviceConfig() != 0) || dialog_ask("Do you want to update your IoT device connection parameters? (y/n)\n"))
        {
        if (cloud_device_enter_credentials() != 0)
        {
            msg_error("Failed configuring the IoT device.\n");
        }
        }
    #if defined(USE_MBED_TLS) || (!defined(USE_CLEAR_TIMEDATE))
        updateTLSCredentials();
    #endif
    }
    /* End of security and cloud parameters definition */

    msg_info("Setting the RTC from the network time.\n");
    #ifdef CLOUD_TIMEDATE_TLS_VERIFICATION_IGNORE
    if (setRTCTimeDateFromNetwork(true) != TD_OK)
    #else   /* CLOUD_TIMEDATE_TLS_VERIFICATION_IGNORE */
        if ( (setRTCTimeDateFromNetwork(false) != TD_OK) && (setRTCTimeDateFromNetwork(true) != TD_OK) )
    #endif  /* CLOUD_TIMEDATE_TLS_VERIFICATION_IGNORE */

    {
        CLOUD_Error_Handler(CLOUD_DEMO_TIMEDATE_ERROR);
        return -1;
    }

    #if defined(RFU) && !defined(FIREWALL_MBEDLIB)
        updateFirmwareVersion();
    #endif  /* RFU */
#endif  /* NET_ENABLE */

#ifdef SENSOR
    // int res = init_sensors();
    int res = BSP_Init_Sensor();

    if(0 != res)
    {
        msg_error("init_sensors returned error : %d\r\n", res);
    }
#endif /* SENSOR */
}

static int BSP_Init_Sensor(void)
{
    int ret = 0;
    
    if (HSENSOR_OK != BSP_HSENSOR_Init())
    {
        msg_error("BSP_HSENSOR_Init() returns %d\r\n", ret);
        ret = -1;
    }
    
    if (TSENSOR_OK != BSP_TSENSOR_Init())
    {
        msg_error("BSP_TSENSOR_Init() returns %d\r\n", ret);
        ret = -1;
    }
    
    if (PSENSOR_OK != BSP_PSENSOR_Init())
    {
        msg_error("BSP_PSENSOR_Init() returns %d\r\n", ret);
        ret = -1;
    }
    
    if (MAGNETO_OK != BSP_MAGNETO_Init())
    {
        msg_error("BSP_MAGNETO_Init() returns %d\r\n", ret);
        ret = -1;
    }

    if (GYRO_OK != BSP_GYRO_Init())
    {
        msg_error("BSP_GYRO_Init() returns %d\r\n", ret);
        ret = -1;
    }
    
    if (ACCELERO_OK != BSP_ACCELERO_Init())
    {
        msg_error("BSP_ACCELERO_Init() returns %d\r\n", ret);
        ret = -1;
    }
    
    VL53L0X_PROXIMITY_Init();
    
    return ret;
}

/**
 * @brief センサ取得
 * 
 */
static void APP_Sensor_Read(char* sensor_val_buf ,uint32_t size)
{
    float    temp_val;
    float    humdity_val;
    float    pressure_val;
    int16_t  ACC_Value[3];
    float    GYR_Value[3];
    int16_t  MAG_Value[3];
    uint16_t tof_val;

    char * Buff = sensor_val_buf;

    // 温度
    temp_val = BSP_TSENSOR_ReadTemp();
    // 湿度
    humdity_val = BSP_HSENSOR_ReadHumidity();
    // 気圧
    pressure_val = BSP_PSENSOR_ReadPressure();
    // ToFセンサ 測距
    tof_val = VL53L0X_PROXIMITY_GetDistance();
    // 加速度
    BSP_ACCELERO_AccGetXYZ(ACC_Value);
    // ジャイロ
    BSP_GYRO_GetXYZ(GYR_Value);
    // 地磁気
    BSP_MAGNETO_GetXYZ(MAG_Value);

    snprintf( Buff, size,
            "Tempe : %.2fC, Humidity : %.2f%%, Pressure : %.2fhPa\r\n"
            "ToF : %dmm\r\n"
            "ACC_X : %d, ACC_Y : %d, ACC_Z : %d\r\n"
            "GYR_X : %.0f, GYR_Y : %.0f, GYR_Z : %.0f\r\n"
            "MAG_X : %d, MAG_Y : %d, MAG_Z : %d\r\n",
            temp_val, humdity_val, pressure_val, tof_val,
            ACC_Value[0], ACC_Value[1], ACC_Value[2],
            GYR_Value[0], GYR_Value[1], GYR_Value[2],
            MAG_Value[0], MAG_Value[1], MAG_Value[2] );
}

/**
 * @brief BSP Init
 *
 */
void APP_BSP_Init(void)
{
    BSP_LED_Init(LED2);
    BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

    uart_1_Init();

    // センサ初期化
    // void genericmqtt_client_XCube_sample_run();
}

/**
 * @brief APP Init
 *
 */
void APP_Init(void)
{
    // センサデータバッファ初期化
    memset(s_sensor_buf,0x00,sizeof(s_sensor_buf));

    // For getchcar(), scanf()
    setbuf( stdin, NULL );
    // For printf() Porting
    setbuf(stdout, NULL);

    APP_IoT_Init();
#ifdef NET_ENABLE
    exosite_main(0);
    platform_deinit();
#endif
}

/**
 * @brief ドライバメイン
 *
 */
void App_Drv_Main(void)
{
    double pi;

    pi = App_Math_PI();

    // 円周率計算
    printf("PI = %1.14f\r\n", pi);

    BSP_LED_Toggle(LED_GREEN);
    osDelay(100);
}

/**
 * @brief APP Main
 * 
 */
void APP_Main(void)
{
    // センサデータ読み出し
    APP_Sensor_Read(s_sensor_buf,
                    sizeof(s_sensor_buf)-1);
    printf("%s\r\n", s_sensor_buf);
}
