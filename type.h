//type.h ͷ�ļ�,���Ͷ���


#pragma once

#ifndef __TYPE_H__
#define __TYPE_H__
#endif


typedef unsigned int   Elf32_Addr;   //�޷��ų����ַ

typedef unsigned short Elf32_Half;   //�޷����е�����

typedef unsigned int   Elf32_Off;    //�޷����ļ�ƫ��

typedef int            Elf32_SWord;  //�з��Ŵ�����

typedef unsigned int   Elf32_Word;   //�޷��Ŵ�����

#define ELEMENTCOUNT 1
#define PAGESIZE     4096


#define ELF32_R_SYM(i) ((i)>>8) 

#define ELF32_R_TYPE(i) ((char)(i)) 

#define ELF32_R_INFO(s, t) (((s)<<8) + (char)(t))

#define INT4(n) ((n)-(n)%4)+4
#define INT8(n) ((n)-(n)%8)+8


