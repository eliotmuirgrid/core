//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASfile
// 
// Implementation
//-------------------------------------------------------

#include "BASfile.h"
#include "BASfileImp.h"
#include "BASstring.h"
#include "BAStrace.h"
BAS_TRACE_INIT;

#include <errno.h>

#ifndef _WIN32
   #include <fcntl.h>
#endif


#ifndef O_BINARY
#  define O_BINARY 0
#endif

BASfile::BASfile() : m_FileHandle(-1) {
   BAS_METHOD(BASfile::BASfile);
}

BASfile::~BASfile(){
   BAS_METHOD(BASfile::~BASfile);
   close();
}

bool BASfile::open(const BASstring& FileName, BASmode Mode){
   switch (Mode)
   {
   case BASmode::Read:    m_FileHandle=BASopen(FileName.data(), O_BINARY | O_RDONLY);                                        break;
   case BASmode::Write:   m_FileHandle=BASopen(FileName.data(), O_BINARY | O_RDWR                     , S_IREAD | S_IWRITE); break;
   case BASmode::Append:  m_FileHandle=BASopen(FileName.data(), O_BINARY | O_RDWR | O_CREAT | O_APPEND, S_IREAD | S_IWRITE); break;
   case BASmode::Rewrite: m_FileHandle=BASopen(FileName.data(), O_BINARY | O_RDWR | O_CREAT | O_TRUNC , S_IREAD | S_IWRITE); break;
   }
   if (m_FileHandle == -1){
      m_LastError = errno;
   }
   return m_FileHandle != -1;
}

int BASfile::write(const char* pData, int Size){
   BAS_METHOD(BASfile::write);
   int AmountWritten = BASwrite(m_FileHandle, pData, Size);
   if (AmountWritten == -1){
      m_LastError = errno;    
   }
   BAS_VAR(AmountWritten);
   return AmountWritten;
}

int BASfile::read(void* pBuffer, int SizeOfBuffer){
   BAS_METHOD(BASfile::read);
   int AmountRead = ::read(m_FileHandle, pBuffer, SizeOfBuffer);
   if (AmountRead == -1){
      m_LastError = errno;        
   }
   BAS_VAR(AmountRead);
   return AmountRead;
}

int BASfile::read(BASstring* pBuffer){
   BAS_METHOD(BASfile::read - BASstring);
   pBuffer->setCapacity(size());
   pBuffer->setSize(pBuffer->capacity());
   int AmountRead = BASfile::read(pBuffer->data(), pBuffer->capacity());
   return AmountRead;
}


void BASfile::close(){
   BAS_METHOD(BASfile::close);
   if(m_FileHandle !=-1){
      ::close(m_FileHandle);
      m_FileHandle = -1;
   }
}

void BASfile::flush(){
   BAS_METHOD(BASfile::close);
   BASfsync(m_FileHandle);
}

BASint64 BASfile::size() {
   BAS_METHOD(BASfile::size);
   BASint64 Position = BASseek(m_FileHandle, 0, SEEK_CUR);
   BASint64 Size = BASseek(m_FileHandle, 0, SEEK_END);
   int Result = BASseek(m_FileHandle, Position, SEEK_SET);
   if (Result == -1){
      m_LastError = errno;
   }
   BAS_VAR(Size);
   return Size;
}

BASint64 BASfile::position() {
   BAS_METHOD(BASfile::position);
   BASint64 Position = BASseek(m_FileHandle, 0, SEEK_CUR);
   if (Position == -1){
      m_LastError = errno;
   }
   return Position;
}
