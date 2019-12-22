### 程序说明

将NV16图片转化为NV12格式

### 编译执行

    paul@maziot:~/work/maziot/maziot_nv16_convert_to_nv12$ make
    gcc -o app main.c
    paul@maziot:~/work/maziot/maziot_nv16_convert_to_nv12$ ./app nv16.yuv 64 64 nv12.yuv

### 附加说明

由于 ffmpeg 和 7yuv 均不支持 NV16 格式, 因此才编写了此程序.
以后有 NV16 的图片, 先通过此程序转化为 NV12 再用 7yuv 查看, 再使用 ffmpeg 做处理.

测试图片分辨率为 64x64, 内容为田字格显示红绿蓝白4中颜色, 颜色分布如下:

    -----------------
    |       |       |
    |  RED  | GREEN |
    |       |       |
    -----------------
    |       |       |
    |  BLUE | WHITE |
    |       |       |
    -----------------


