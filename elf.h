//ELF.h 头文件，整个文件格式结构体描述

#pragma once

//#ifndef __ELF_H__
//#define __ELF_H__
//#endif

#include "type.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <assert.h> 
#include <stdio.h>
#include <cstring>
#include <malloc.h>
using namespace std;


#define EI_NIDENT 16

//ELF文件头信息
#pragma pack(push,1)

typedef struct{ 

	char  e_ident[EI_NIDENT];
	Elf32_Half     e_type;
	Elf32_Half     e_machine;
	Elf32_Word     e_version;
	Elf32_Addr     e_entry;
	Elf32_Off      e_phoff;
	Elf32_Off      e_shoff; 
	Elf32_Word     e_flags;
	Elf32_Half     e_ehsize;
	Elf32_Half     e_phentsize;
	Elf32_Half     e_phnum;
	Elf32_Half     e_shentsize;
	Elf32_Half     e_shnum;
	Elf32_Half     e_shstrndx; 

}Elf32_Ehdr,*PElf32_Ehdr;

typedef enum{

	ET_NONE    = 0,			//未知目标文件格式 
	ET_REL     = 1,			//可重定位文件 
	ET_EXEC    = 2,			//可执行文件 
	ET_DYN     = 3,			//共享目标文件 
	ET_CORE    = 4,			//Core 文件（转储格式） 
	ET_LOPROC  = 0xff00,	//特定处理器文件 
	ET_HIPROC  = 0xffff		//特定处理器文件 

}p_type32_e;

typedef enum{

	PS_EDIT   = 0,
	PS_INSERT = 1,
	PS_DELETE = 2

}p_type_program_section;

//程序头部信息
typedef struct{

	Elf32_Word p_type;
	Elf32_Off  p_offset;
	Elf32_Addr p_vaddr;
	Elf32_Addr p_paddr;
	Elf32_Word p_filesz;
	Elf32_Word p_memsz;
	Elf32_Word p_flags;
	Elf32_Word p_align;

}Elf32_Phdr, *PElf32_Phdr;

//节区头部信息
typedef struct{ 

	Elf32_Word sh_name;
	Elf32_Word sh_type;
	Elf32_Word sh_flags;
	Elf32_Addr sh_addr;
	Elf32_Off  sh_offset; 
	Elf32_Word sh_size;
	Elf32_Word sh_link;
	Elf32_Word sh_info;
	Elf32_Word sh_addralign;
	Elf32_Word sh_entsize; 

}Elf32_Shdr, *PElf32_Shdr;

//dynsym符号表
//#pragma pack(1)
typedef struct {
	Elf32_Word     st_name; 
	Elf32_Addr     st_value;
	Elf32_Word	   st_size; 
	char  st_info; 
	char  st_other; 
	Elf32_Half     st_shndx;
}Elf32_sym, *PElf32_sym;


typedef struct {

	Elf32_Addr r_offset;
	Elf32_Word r_info;

} Elf32_Rel;

typedef struct {

	Elf32_Addr r_offset;
	Elf32_Word r_info;
	Elf32_Word r_addend;

} Elf32_Rela;

//.dynamic
typedef struct{ 

	Elf32_Word d_tag;

	union{ 
		Elf32_Word  d_val;
		Elf32_Addr  d_ptr;
	} d_un; 

}Elf32_Dyn, *PElf32_Dyn;


typedef enum{
	DT_NULL			= 0,		/* last entry in list */
	DT_NEEDED		,			/* a needed object */
	DT_PLTRELSZ		,			/* size of relocations for the PLT */
	DT_PLTGOT		,			/* addresses used by procedure linkage table */
	DT_HASH			,			/* hash table */
	DT_STRTAB		,			/* string table */
	DT_SYMTAB		,			/* symbol table */
	DT_RELA			,			/* addr of relocation entries */
	DT_RELASZ		,			/* size of relocation table */
	DT_RELAENT		,			/* base size of relocation entry */
	DT_STRSZ		,			/* size of string table */
	DT_SYMENT		,			/* size of symbol table entry */
	DT_INIT			,			/* _init addr */
	DT_FINI			,			/* _fini addr */
	DT_SONAME		,			/* name of this shared object */
	DT_RPATH		,			/* run-time search path */
	DT_SYMBOLIC		,			/* shared object linked -Bsymbolic */
	DT_REL			,			/* addr of relocation entries */
	DT_RELSZ		,			/* size of relocation table */
	DT_RELENT		,			/* base size of relocation entry */
	DT_PLTREL		,			/* relocation type for PLT entry */
	DT_DEBUG		,			/* pointer to r_debug structure */
	DT_TEXTREL		,			/* text relocations remain for this object */
	DT_JMPREL		,			/* pointer to the PLT relocation entries */
	DT_BIND_NOW		,			/* perform all relocations at load of object */
	DT_INIT_ARRAY	,			/* pointer to .initarray */
	DT_FINI_ARRAY	,			/* pointer to .finiarray */
	DT_INIT_ARRAYSZ	,			/* size of .initarray */
	DT_FINI_ARRAYSZ	,			/* size of .finiarray */
	DT_RUNPATH		,			/* run-time search path */
	DT_FLAGS		,			/* state flags - see DF_* */
	DT_GUN_HASH   = 0x6ffffef5,
	DT_VERNEED    = 0x6ffffffe,
	DT_VERNEEDNUM =	0x6fffffff,
	DT_VERSYM     =	0x6ffffff0,
	DT_RELCOUNT   = 0x6ffffffa,
	DT_FLAGS_1	  = 0x6ffffffb
}p_type32_dyn_tag;

/* sh_type */
#define SHT_NULL			0		/* Section header table entry unused */
#define SHT_PROGBITS		1		/* Program data */
#define SHT_SYMTAB			2		/* Symbol table */
#define SHT_STRTAB			3		/* String table */
#define SHT_RELA			4		/* Relocation entries with addends */
#define SHT_HASH			5		/* Symbol hash table */
#define SHT_DYNAMIC			6		/* Dynamic linking information */
#define SHT_NOTE			7		/* Notes */
#define SHT_NOBITS			8		/* Program space with no data (bss) */
#define SHT_REL				9		/* Relocation entries, no addends */
#define SHT_SHLIB			10		/* Reserved */
#define SHT_DYNSYM			11		/* Dynamic linker symbol table */
#define SHT_INIT_ARRAY		14		/* Array of constructors */
#define SHT_FINI_ARRAY		15		/* Array of destructors */
#define SHT_PREINIT_ARRAY	16		/* Array of pre-constructors */
#define SHT_GROUP			17		/* Section group */
#define SHT_SYMTAB_SHNDX	18		/* Extended section indeces */
#define	SHT_NUM				19		/* Number of defined types.  */
#define SHT_LOOS			0x60000000	/* Start OS-specific.  */
#define SHT_GNU_ATTRIBUTES  0x6ffffff5	/* Object attributes.  */
#define SHT_GNU_HASH	    0x6ffffff6	/* GNU-style hash table.  */
#define SHT_GNU_LIBLIST	    0x6ffffff7	/* Prelink library list */
#define SHT_CHECKSUM	    0x6ffffff8	/* Checksum for DSO content.  */
#define SHT_LOSUNW			0x6ffffffa	/* Sun-specific low bound.  */
#define SHT_SUNW_move	    0x6ffffffa
#define SHT_SUNW_COMDAT     0x6ffffffb
#define SHT_SUNW_syminfo    0x6ffffffc
#define SHT_GNU_verdef	    0x6ffffffd	/* Version definition section.  */
#define SHT_GNU_verneed	    0x6ffffffe	/* Version needs section.  */
#define SHT_GNU_versym	    0x6fffffff	/* Version symbol table.  */
#define SHT_HISUNW			0x6fffffff	/* Sun-specific high bound.  */
#define SHT_HIOS			0x6fffffff	/* End OS-specific type */
#define SHT_LOPROC			0x70000000	/* Start of processor-specific */
#define SHT_HIPROC			0x7fffffff	/* End of processor-specific */
#define SHT_LOUSER			0x80000000	/* Start of application-specific */
#define SHT_HIUSER			0x8fffffff	/* End of application-specific */


#define R_ARM_NONE			0	/* No reloc */
#define R_ARM_PC24			1	/* PC relative 26 bit branch */
#define R_ARM_ABS32			2	/* Direct 32 bit  */
#define R_ARM_REL32			3	/* PC relative 32 bit */
#define R_ARM_PC13			4
#define R_ARM_ABS16			5	/* Direct 16 bit */
#define R_ARM_ABS12			6	/* Direct 12 bit */
#define R_ARM_THM_ABS5		7
#define R_ARM_ABS8			8	/* Direct 8 bit */
#define R_ARM_SBREL32		9
#define R_ARM_THM_PC22		10
#define R_ARM_THM_PC8		11
#define R_ARM_AMP_VCALL9	12
#define R_ARM_SWI24			13
#define R_ARM_THM_SWI8		14
#define R_ARM_XPC25			15
#define R_ARM_THM_XPC22		16
#define R_ARM_TLS_DTPMOD32	17	/* ID of module containing symbol */
#define R_ARM_TLS_DTPOFF32	18	/* Offset in TLS block */
#define R_ARM_TLS_TPOFF32	19	/* Offset in static TLS block */
#define R_ARM_COPY			20	/* Copy symbol at runtime */
#define R_ARM_GLOB_DAT		21	/* Create GOT entry */
#define R_ARM_JUMP_SLOT		22	/* Create PLT entry */
#define R_ARM_RELATIVE		23	/* Adjust by program base */
#define R_ARM_GOTOFF		24	/* 32 bit offset to GOT */
#define R_ARM_GOTPC			25	/* 32 bit PC relative offset to GOT */
#define R_ARM_GOT32			26	/* 32 bit GOT entry */
#define R_ARM_PLT32			27	/* 32 bit PLT address */
#define R_ARM_ALU_PCREL_7_0	32
#define R_ARM_ALU_PCREL_15_8	33
#define R_ARM_ALU_PCREL_23_15	34
#define R_ARM_LDR_SBREL_11_0	35
#define R_ARM_ALU_SBREL_19_12	36
#define R_ARM_ALU_SBREL_27_20	37
#define R_ARM_GNU_VTENTRY	100
#define R_ARM_GNU_VTINHERIT	101
#define R_ARM_THM_PC11		102	/* thumb unconditional branch */
#define R_ARM_THM_PC9		103	/* thumb conditional branch */
#define R_ARM_TLS_GD32		104	/* PC-rel 32 bit for global dynamic
					   thread local data */
#define R_ARM_TLS_LDM32		105	/* PC-rel 32 bit for local dynamic
					   thread local data */
#define R_ARM_TLS_LDO32		106	/* 32 bit offset relative to TLS
					   block */
#define R_ARM_TLS_IE32		107	/* PC-rel 32 bit for GOT entry of
					   static TLS block offset */
#define R_ARM_TLS_LE32		108	/* 32 bit offset relative to static
					   TLS block */
#define R_ARM_RXPC25		249
#define R_ARM_RSBREL32		250
#define R_ARM_THM_RPC22		251
#define R_ARM_RREL32		252
#define R_ARM_RABS22		253
#define R_ARM_RPC24			254
#define R_ARM_RBASE			255
/* Keep this the last entry.  */
#define R_ARM_NUM			256

#pragma pack(pop)
