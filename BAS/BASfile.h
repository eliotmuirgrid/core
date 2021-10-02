#ifndef _BAS_FILE_H_
#define _BAS_FILE_H_
//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASfile
// 
// Basic file object.
//-------------------------------------------------------

#include "BASsink.h"
#include "BASstring.h"
#include "BAStypes.h"

class BASstring;

void BASwriteFile(const BASstring& Name, const BASstring& Content);
void BASreadFile(const BASstring& Name, BASstring* pContent);

class BASfile : public BASsink{
public:
   enum BASmode{Read, Write, Append, Rewrite};
   BASfile();
   virtual ~BASfile();

   bool open(const BASstring& FileName, BASmode Mode);

   int write(const BASstring& Data) { return write(Data.data(), Data.size());}
   virtual int write(const char* pData, int Size);

   int read(void* pBuffer, int SizeOfBuffer);

   int read(BASstring* pBuffer);

   void close();

   virtual void flush();

   int lastError() const;

   BASint64 position();

   BASint64 size();
private:
   int m_FileHandle;
   int m_LastError;
   BASfile(const BASfile& Orig); // not allowed
   BASfile& operator=(const BASfile& Orig); // not allowed.
};

#endif
