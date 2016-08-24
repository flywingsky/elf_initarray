/*
  Code By:无名侠
*/
#include <stdio.h>
#include <elf.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
Elf32_Addr VaToFa(int fd,Elf32_Addr rva)
{
  /*顾名思义
    fd - 打开的so文件句柄
    rva - 欲转换的地址
    return - rva的文件偏移
  */
  int old;
  int pnum;
  Elf32_Ehdr ehdr;
  Elf32_Addr result;
  old = lseek(fd,0,SEEK_CUR);
  lseek(fd,0,SEEK_SET);
  read(fd,&ehdr,sizeof(Elf32_Ehdr));
  pnum = ehdr.e_phnum;
  result = rva;
  for(int i = 0;i<pnum;i++)
  {
    Elf32_Phdr phdr;
    read(fd,&phdr,sizeof(Elf32_Phdr));
    if(rva>=phdr.p_vaddr && rva<phdr.p_vaddr+phdr.p_memsz)
      result =  rva-phdr.p_vaddr+phdr.p_offset;
  }
  lseek(fd,old,SEEK_SET);
  return result;
}
int main(int argc, char const *argv[]) {
  int  fp;
  Elf32_Ehdr ehdr;
  int phnum;
  if(argc!=2)
  {
    printf("Please input elf file!\n");
    return -1;
  }
  fp = open(argv[1],O_RDONLY);
  if(!fp)
  {
    printf("error:can't open %s \n",argv[1] );
    return -1;
  }
 read(fp,&ehdr,sizeof(Elf32_Ehdr));
 //verify magic
 if(memcmp(ehdr.e_ident,ELFMAG,SELFMAG))
 {
   printf("bad magic.\n");
   close(fp);
   return -1;
 }
 phnum = ehdr.e_phnum;
 for(int i =0;i<phnum;i++)
 {
   Elf32_Phdr phdr;
   read(fp,&phdr,sizeof(Elf32_Phdr));
   if(phdr.p_type==PT_DYNAMIC)
   {
     Elf32_Dyn dyn;
     Elf32_Addr initaddr;
     Elf32_Word initsize;

     int cnt = 0;
     printf("offset : %x\n",phdr.p_offset);
     lseek(fp,phdr.p_offset,SEEK_SET);
     do {
       read(fp,&dyn,sizeof(Elf32_Dyn));
       if(dyn.d_tag==DT_INIT_ARRAY)
        initaddr = dyn.d_un.d_ptr;
       else if(dyn.d_tag==DT_INIT_ARRAYSZ)
        initsize = dyn.d_un.d_val;
     } while(dyn.d_tag!=DT_NULL);
     initsize/=4;
     initsize-=1;
     printf("INIT ARRAY OFFSET:%x(RVA)\nINTI NUM:%d\ninit table:\n",initaddr,initsize);
     initaddr=VaToFa(fp,initaddr);
     lseek(fp,initaddr,SEEK_SET);
     for(int i = 0;i<initsize;i++)
     {
        Elf32_Addr fun;
        read(fp,&fun,4);
        printf("fun %d :%x\n",i,fun);
     }
     break;
   }
 }
  return 0;
}
