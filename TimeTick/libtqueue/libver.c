/*************************************************
* ���ƣ�libver.c
* ���ܣ��汾�Ź���
* ���أ�    
* ��ע�����ļ�
***************************************************/

#include <stdio.h>

void get_version(const char *filename)
{
    #define SYSTEM_VER "V1.0.0.0"
    fprintf(stderr, "���ײ㺯����%-17s�汾�� %-17s���� %s\n", filename, SYSTEM_VER, __DATE__);
    return;
}