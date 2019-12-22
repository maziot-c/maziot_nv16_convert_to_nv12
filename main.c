#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "maz_errors.h"
#include "maz_types.h"

/* 宏定义 */
#define DEBUG

#if defined(DEBUG)
#define debug_msg printf
#else
#define debug_msg
#endif

#define debug_log(fmt, arg...) printf("[%s][%d] "fmt"\n", __FUNCTION__, __LINE__, ##arg);
#define print_msg printf
#define error_msg printf

#define MAZIOT_ASSERT_RET(ret, maziot_ret, fmt, msg...)     \
    if (ret)                                                \
    {                                                       \
        error_msg("err: "fmt"! ret = %d\r\n", ##msg, ret);  \
        return maziot_ret;                                  \
    }

/* 结构体定义 */
typedef struct _MAZ_MOD_FRAME_
{
    uint32_t        width;
    uint32_t        height;
    uint32_t        format;
    uint8_t         *addr[4];
    uint32_t        pitch[4];
} MAZ_MOD_FRAME;

typedef struct _USER_APP_FRAME_
{
    int8_t          name[32];       // 文件名
    FILE            *file;          // 文件句柄
    MAZ_MOD_FRAME   frame;
} MAZ_APP_FRAME;

/* 函数声明 */
int MAZ_APP_FRAME_parsing_main_arguments(int argc, char const *argv[]);

/* 全局变量定义 */
MAZ_APP_FRAME nv16_frame;           // 输入图像帧
MAZ_APP_FRAME nv12_frame;           // 输出图像帧

int main(int argc, char const *argv[])
{
    int ret = 0;

    ret = MAZ_APP_FRAME_parsing_main_arguments(argc, argv);
    MAZIOT_ASSERT_RET(ret, MAZIOT_EINVAL, "parsing main arguments failed");

    return MAZIOT_NOERR;
}

/**
 * @Description 解析命令行参数到全局变量，并验证参数的有效性
 */
int MAZ_APP_FRAME_parsing_main_arguments(int argc, char const *argv[])
{
    /* 打印函数使用方法 */
    if (argc != 5)
    {
        print_msg("usage: ./app nv16.yuv width height nv12.yuv\r\n");
        print_msg("eg   : ./app nv16.yuv 1280 720 nv12.yuv\r\n");
        return MAZIOT_EINVAL;
    }

    /* 解析输出参数 */
    strcpy(nv16_frame.name, argv[1]);
    strcpy(nv12_frame.name, argv[4]);
    nv16_frame.frame.width  = (uint32_t)strtol(argv[2], NULL, 0);
    nv16_frame.frame.height = (uint32_t)strtol(argv[3], NULL, 0);
    debug_msg("nv16_frame.frame.width   = %u\r\n", nv16_frame.frame.width);
    debug_msg("nv16_frame.frame.height  = %u\r\n", nv16_frame.frame.height);
    debug_msg("nv16_frame.name          = %s\r\n", nv16_frame.name);
    debug_msg("nv12_frame.name          = %s\r\n", nv12_frame.name);

    return MAZIOT_NOERR;
}

