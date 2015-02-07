/*************************************************
* 名称：libver.c
* 功能：版本号工具
* 返回：    
* 备注：库文件
***************************************************/

#include <stdio.h>

void get_version(const char *filename)
{
    #define SYSTEM_VER "V1.0.0.0"
    fprintf(stderr, "【底层函数】%-17s版本号 %-17s日期 %s\n", filename, SYSTEM_VER, __DATE__);
    return;
}