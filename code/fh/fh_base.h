
#ifndef FH_BASE_H
#define FH_BASE_H

#include "stdint.h"

typedef int8_t   s8;
typedef uint8_t  u8;
typedef int16_t  s16;
typedef uint16_t u16;
typedef int32_t  s32;
typedef uint32_t u32;
typedef int64_t  s64;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef s32 b32;

#define global_var static
#define local_persist static
#define internal static

#define Stmnt(x) do{ x; }while(0)

#if defined(PLATFORM_WEB)
#define Assert(ext)
#else
#define Assert(exp) Stmnt(if(!(exp)){ *(int *)0 = 0; })
#endif

#define Loop(v, n) for(s64 v = 0; v < n; v += 1)
#define For(v, s, e) for(s64 v = s; v != e; v += FH_Sign(e - s))

#define ArrayCount(arr) (sizeof(arr)/sizeof(arr[0]))

#define U32FromPtr(ptr) (u32)((char *)ptr - (char *)0)
#define U64FromPtr(ptr) (u64)((char *)ptr - (char *)0)

#define IntFromPtr(ptr) U32FromPtr(ptr)
#define PtrFromInt(n) (void *)((char *)0 + (n))

#define _Member(T, m) (((T*)0)->m)
#define MemberOffset(T, m) IntFromPtr(&_Member(T, m))

#define FH_Min(a, b) ((a) < (b) ? (a) : (b))
#define FH_Max(a, b) ((a) > (b) ? (a) : (b))

#define FH_Abs(v)  ((v) >= 0 ? (v) : (-(v)))
#define FH_Sign(v) ((v) > 0 ? 1 : (v) < 0 ? -1 : 0)

#define FH_Clamp(a, min, max) (((a) < (min)) ? (min) : ((a) > (max)) ? (max) : (a))
#define FH_Wrap(a, min, max)  (((a) < (min)) ? (max) : ((a) > (max)) ? (min) : (a))

#define FH_Ceil(v)   ((s32)((v) + 0.99999))
#define FH_Floor(v)  ((s32)(v))

#define KB(n) (n*1024ULL)
#define MB(n) (KB(n)*1024ULL)
#define GB(n) (MB(n)*1024ULL)
#define TB(n) (GB(n)*1024ULL)

#endif

