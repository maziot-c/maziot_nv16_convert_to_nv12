#ifndef _MAZ_IMAGE_H
#define _MAZ_IMAGE_H

/* 枚举定义 */
typedef enum _MAZ_MOD_IMAGE_FORMAT_
{
    /* RAW */
    MAZ_IMAGE_FORMAT_RAW8 = 0,
    MAZ_IMAGE_FORMAT_RAW10,
    MAZ_IMAGE_FORMAT_RAW12,
    MAZ_IMAGE_FORMAT_RAW14,
    MAZ_IMAGE_FORMAT_RAW16,

    /* RGB with alpha */
    MAZ_IMAGE_FORMAT_ARGB1555 = 20,
    MAZ_IMAGE_FORMAT_ARGB4444,
    MAZ_IMAGE_FORMAT_ARGB8888,

    /* RGB without alpha */
    MAZ_IMAGE_FORMAT_RGB565 = 40,
    MAZ_IMAGE_FORMAT_RGB888,

    /* YUV planar */                            // 2x2 image in memory
    MAZ_IMAGE_FORMAT_YUV_PLANAR_444 = 60,       // YYYYUUUUVVVV
    MAZ_IMAGE_FORMAT_YUV_PLANAR_422,            // YYYYUUVV
    MAZ_IMAGE_FORMAT_YUV_PLANAR_420,            // YYYYUV           I420
    MAZ_IMAGE_FORMAT_YVU_PLANAR_444,            // YYYYVVVVUUUU
    MAZ_IMAGE_FORMAT_YVU_PLANAR_422,            // YYYYVVUU
    MAZ_IMAGE_FORMAT_YVU_PLANAR_420,            // YYYYVU

    /* YUV Y planar UV pack */                  // 2x2 image in memory
    MAZ_IMAGE_FORMAT_Y_PLANAR_UV_PACK_444 = 70, // YYYYUVUVUVUV
    MAZ_IMAGE_FORMAT_Y_PLANAR_UV_PACK_422,      // YYYYUVUV         NV16
    MAZ_IMAGE_FORMAT_Y_PLANAR_UV_PACK_420,      // YYYYUV           NV12
    MAZ_IMAGE_FORMAT_Y_PLANAR_VU_PACK_444,      // YYYYVUVUVUVU
    MAZ_IMAGE_FORMAT_Y_PLANAR_VU_PACK_422,      // YYYYVUVU         YV16
    MAZ_IMAGE_FORMAT_Y_PLANAR_VU_PACK_420,      // YYYYVU           NV21

    /* YUV pack */                              // 2x2 image in memory
    MAZ_IMAGE_FORMAT_YUV_PACK_444  = 80,        // YUVYUVYUVYUV
    MAZ_IMAGE_FORMAT_YVU_PACK_444,              // YVUYVUYVUYVU
    MAZ_IMAGE_FORMAT_YUYV_PACK_422,             // YUYVYUYV
    MAZ_IMAGE_FORMAT_UYVY_PACK_422,             // UYVYUYVY
    MAZ_IMAGE_FORMAT_YVYU_PACK_422,             // YVYUYVYU
    MAZ_IMAGE_FORMAT_VYUY_PACK_422,             // VYUYVYUY

    /* YUV Y only */                            // 2x2 image in memory
    MAZ_IMAGE_FORMAT_Y_ONLY,                    // YYYY

    MAZ_IMAGE_FORMAT_MAX,
} MAZ_MOD_IMAGE_FORMAT;

/* 结构体定义 */
typedef struct _MAZ_MOD_IMAGE_
{
    uint32_t        width;
    uint32_t        height;
    uint32_t        format;
    uint8_t         *addr[4];
    uint32_t        pitch[4];
} MAZ_MOD_IMAGE;

#endif /* _MAZ_IMAGE_H */
