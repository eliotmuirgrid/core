#ifndef _BAS_FILE_IMP_H_
#define _BAS_FILE_IMP_H_
//-------------------------------------------------------
// Copyright (C) 2021 Eliot Muir.  All Rights Reserved
//
// BASfileImp
// 
// Defines for file implementation
//-------------------------------------------------------

#ifdef _WIN32
   #include <io.h>
   #define BASfsync _commit
   #define BASwrite _write
   #define BASopen _open
#else
   #include <unistd.h>
   #define BASfsync ::fsync
   #define BASwrite ::write
   #define BASopen  ::open
#endif

#endif
