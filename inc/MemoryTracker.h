#ifndef MEMORYTRACKER_H
#define MEMORYTRACKER_H

#include <list>

  #ifdef _DEBUG
  inline void * __cdecl operator new(unsigned int size,
                                     const char *file, int line)
  {
      void *ptr = (void *)malloc(size);
      AddTrack((DWORD)ptr, size, file, line);
      return(ptr);
  };
  inline void __cdecl operator delete(void *p)
  {
      RemoveTrack((DWORD)p);
      free(p);
  };
  #endif

    typedef struct {
      DWORD	address;
      DWORD	size;
      char	file[64];
      DWORD	line;
  } ALLOC_INFO;

  typedef list<ALLOC_INFO*> AllocList;

  AllocList *allocList;

  void AddTrack(DWORD addr,  DWORD asize,  const char *fname, DWORD lnum)
  {
      ALLOC_INFO *info;

      if(!allocList) {
          allocList = new(AllocList);
      }

      info = new(ALLOC_INFO);
      info->address = addr;
      strncpy(info->file, fname, 63);
      info->line = lnum;
      info->size = asize;
      allocList->insert(allocList->begin(), info);
  };

  void RemoveTrack(DWORD addr)
  {
      AllocList::iterator i;

      if(!allocList)
          return;
      for(i = allocList->begin(); i != allocList->end(); i++)
      {
          if((*i)->address == addr)
          {
              allocList->remove((*i));
              break;
          }
      }
  };

void DumpUnfreed()
{
  AllocList::iterator i;
  DWORD totalSize = 0;
  char buf[1024];

  if(!allocList)
      return;

  for(i = allocList->begin(); i != allocList->end(); i++) {
      sprintf(buf, "%-50s:\t\tLINE %d,\t\tADDRESS %d\t%d unfreed\n",
          (*i)->file, (*i)->line, (*i)->address, (*i)->size);
      OutputDebugString(buf);
      totalSize += (*i)->size;
  }
  sprintf(buf, "-----------------------------------------------------------\n");
  OutputDebugString(buf);
  sprintf(buf, "Total Unfreed: %d bytes\n", totalSize);
  OutputDebugString(buf);
};

#endif
