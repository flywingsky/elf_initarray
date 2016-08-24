//type.h 头文件,类型定义


#pragma once

#ifndef __TYPE_H__
#define __TYPE_H__
#endif


typedef unsigned int   Elf32_Addr;   //无符号程序地址

typedef unsigned short Elf32_Half;   //无符号中等整数

typedef unsigned int   Elf32_Off;    //无符号文件偏移

typedef int            Elf32_SWord;  //有符号大整数

typedef unsigned int   Elf32_Word;   //无符号大整数

#define ELEMENTCOUNT 1
#define PAGESIZE     4096


#define ELF32_R_SYM(i) ((i)>>8) 

#define ELF32_R_TYPE(i) ((char)(i)) 

#define ELF32_R_INFO(s, t) (((s)<<8) + (char)(t))

#define INT4(n) ((n)-(n)%4)+4
#define INT8(n) ((n)-(n)%8)+8


