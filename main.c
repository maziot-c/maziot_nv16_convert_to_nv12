#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "maz_errors.h"
#include "maz_types.h"
#include "maz_image.h"

/* 宏定义 */
// #define DEBUG

#if defined(DEBUG)
#define debug_msg printf
#else
#define debug_msg
#endif

#define debug_log(fmt, arg...) printf("[%s][%d] "fmt"\n", __FUNCTION__, __LINE__, ##arg);
#define print_msg printf
#define error_msg printf

#define MAZIOT_ASSERT_RET_WITHOUT_MSG(condition, maziot_ret)        \
    if (condition)                                                  \
    {                                                               \
        return maziot_ret;                                          \
    }

#define MAZIOT_ASSERT_RET(condition, maziot_ret, fmt, msg...)       \
    if (condition)                                                  \
    {                                                               \
        error_msg("err: "fmt"! ret = %d\r\n", ##msg, condition);    \
        return maziot_ret;                                          \
    }

/* 结构体定义 */
typedef struct _USER_APP_FRAME_
{
    int8_t          name[32];       // 文件名
    FILE            *file;          // 文件句柄
    MAZ_MOD_IMAGE   image;
} MAZ_APP_FRAME;

/* 函数声明 */
int MAZ_APP_FRAME_parsing_main_arguments(int argc, char const *argv[]);
int MAZ_APP_FRAME_load_input_image(void);
int MAZ_APP_FRAME_save_output_image(void);
int MAZ_APP_FRAME_nv16_convert_to_nv12(void);

/* 全局变量定义 */
MAZ_APP_FRAME nv16_frame;           // 输入图像帧
MAZ_APP_FRAME nv12_frame;           // 输出图像帧

int main(int argc, char const *argv[])
{
    int ret = 0;

    ret = MAZ_APP_FRAME_parsing_main_arguments(argc, argv);
    MAZIOT_ASSERT_RET_WITHOUT_MSG(ret, ret);

    ret = MAZ_APP_FRAME_load_input_image();
    MAZIOT_ASSERT_RET(ret, ret, "MAZ_APP_FRAME_load_input_image");

    MAZ_APP_FRAME_nv16_convert_to_nv12();
    MAZIOT_ASSERT_RET(ret, ret, "MAZ_APP_FRAME_nv16_convert_to_nv12");

    MAZ_APP_FRAME_save_output_image();
    MAZIOT_ASSERT_RET(ret, ret, "MAZ_APP_FRAME_save_output_image");

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
        print_msg("eg   : ./app nv16.yuv 1280 720 nv12.yuv\r\n\r\n");
        return MAZIOT_EINVAL;
    }

    /* 解析输出参数 */
    strcpy(nv16_frame.name, argv[1]);
    strcpy(nv12_frame.name, argv[4]);
    nv16_frame.image.width  = (uint32_t)strtol(argv[2], NULL, 0);
    nv16_frame.image.height = (uint32_t)strtol(argv[3], NULL, 0);
    nv12_frame.image.width  = (uint32_t)strtol(argv[2], NULL, 0);
    nv12_frame.image.height = (uint32_t)strtol(argv[3], NULL, 0);
    debug_msg("nv16_frame.name          = %s\r\n", nv16_frame.name);
    debug_msg("nv16_frame.frame.width   = %u\r\n", nv16_frame.image.width);
    debug_msg("nv16_frame.frame.height  = %u\r\n", nv16_frame.image.height);
    debug_msg("nv12_frame.name          = %s\r\n", nv12_frame.name);
    debug_msg("nv12_frame.frame.width   = %u\r\n", nv12_frame.image.width);
    debug_msg("nv12_frame.frame.height  = %u\r\n", nv12_frame.image.height);

    return MAZIOT_NOERR;
}

/**
 * @Description 加载输入图像
 */
int MAZ_APP_FRAME_load_input_image(void)
{
    int ret = 0;
    int length = 0;
    size_t cnt = 0;

    /* 指定图像格式 */
    nv16_frame.image.format = MAZ_IMAGE_FORMAT_Y_PLANAR_UV_PACK_422;
    nv16_frame.image.pitch[0] = nv16_frame.image.width;
    nv16_frame.image.pitch[1] = nv16_frame.image.width;

    /* 申请图像内存 */
    length = nv16_frame.image.width * nv16_frame.image.height;

    nv16_frame.image.addr[0] = (uint8_t *)malloc(length);
    MAZIOT_ASSERT_RET(NULL == nv16_frame.image.addr[0], MAZIOT_ENOMEM, "nv16 addr[0] malloc failed");
    nv16_frame.image.addr[1] = (uint8_t *)malloc(length);
    MAZIOT_ASSERT_RET(NULL == nv16_frame.image.addr[1], MAZIOT_ENOMEM, "nv16 addr[1] malloc failed");

    /* 读取输入图像到内存 */
    nv16_frame.file = fopen(nv16_frame.name, "r");
    MAZIOT_ASSERT_RET(NULL == nv16_frame.file, MAZIOT_ENOENT, "%s file open failed", nv16_frame.name);

    cnt = fread(nv16_frame.image.addr[0], 1, length, nv16_frame.file);
    if(cnt != length)
    {
        error_msg("err: nv16 addr[0] read failed! cnt = %d, length = %d\r\n", (int)cnt, length);
        free(nv16_frame.image.addr[0]);
        free(nv16_frame.image.addr[1]);
        fclose(nv16_frame.file);
        return MAZIOT_EIO;
    }

    cnt = fread(nv16_frame.image.addr[1], 1, length, nv16_frame.file);
    if(cnt != length)
    {
        error_msg("err: nv16 addr[1] read failed! cnt = %d, length = %d\r\n", (int)cnt, length);
        free(nv16_frame.image.addr[0]);
        free(nv16_frame.image.addr[1]);
        fclose(nv16_frame.file);
        return MAZIOT_EIO;
    }

    fclose(nv16_frame.file);

    return MAZIOT_NOERR;
}

/**
 * @Description 加载输入图像
 */
int MAZ_APP_FRAME_nv16_convert_to_nv12(void)
{
    int ret = 0;
    int row = 0;
    int length = 0;
    uint8_t *psrc = NULL;
    uint8_t *pdst = NULL;

    /* 指定图像格式 */
    nv12_frame.image.format = MAZ_IMAGE_FORMAT_Y_PLANAR_UV_PACK_420;
    nv12_frame.image.pitch[0] = nv12_frame.image.width;
    nv12_frame.image.pitch[1] = nv12_frame.image.width;

    /* 申请图像内存 */
    length = nv12_frame.image.width * nv12_frame.image.height;

    nv12_frame.image.addr[0] = (uint8_t *)malloc(length);
    MAZIOT_ASSERT_RET(NULL == nv12_frame.image.addr[0], MAZIOT_ENOMEM, "nv12 addr[0] malloc failed");
    nv12_frame.image.addr[1] = (uint8_t *)malloc(length / 2);
    MAZIOT_ASSERT_RET(NULL == nv12_frame.image.addr[1], MAZIOT_ENOMEM, "nv12 addr[1] malloc failed");

    /* 拷贝 Y 分量 */
    memcpy(nv12_frame.image.addr[0], nv16_frame.image.addr[0], length);

    /* 拷贝 UV 分量 */
    psrc = nv16_frame.image.addr[1];
    pdst = nv12_frame.image.addr[1];
    for(row = 0; row < (nv16_frame.image.height / 2); row++)
    {
        memcpy(pdst, psrc, nv16_frame.image.width);
        psrc = psrc + nv16_frame.image.pitch[1] * 2;
        pdst = pdst + nv12_frame.image.pitch[1];
    }

    /* 释放输入图像内存 */
    free(nv16_frame.image.addr[0]);
    free(nv16_frame.image.addr[1]);

    return MAZIOT_NOERR;
}

/**
 * @Description 保存输出图像
 */
int MAZ_APP_FRAME_save_output_image(void)
{
    int ret = 0;
    int length = 0;
    size_t cnt = 0;

    /* 写入图像数据到输出图像 */
    nv12_frame.file = fopen(nv12_frame.name, "wb");
    MAZIOT_ASSERT_RET(NULL == nv12_frame.file, MAZIOT_ENOENT, "%s file open failed", nv12_frame.name);

    length = nv12_frame.image.width * nv12_frame.image.height;
    cnt = fwrite(nv12_frame.image.addr[0], 1, length, nv12_frame.file);
    if(cnt != length)
    {
        error_msg("err: nv12 addr[1] write failed! cnt = %d, length = %d\r\n", (int)cnt, length);
        free(nv12_frame.image.addr[0]);
        free(nv12_frame.image.addr[1]);
        fclose(nv12_frame.file);
        return MAZIOT_EIO;
    }

    length = nv12_frame.image.width * nv12_frame.image.height / 2;
    cnt = fwrite(nv12_frame.image.addr[1], 1, length, nv12_frame.file);
    if(cnt != length)
    {
        error_msg("err: nv12 addr[1] write failed! cnt = %d, length = %d\r\n", (int)cnt, length);
        free(nv12_frame.image.addr[0]);
        free(nv12_frame.image.addr[1]);
        fclose(nv12_frame.file);
        return MAZIOT_EIO;
    }

    fclose(nv12_frame.file);

    /* 释放输出图像内存 */
    free(nv12_frame.image.addr[0]);
    free(nv12_frame.image.addr[1]);

    return MAZIOT_NOERR;
}

