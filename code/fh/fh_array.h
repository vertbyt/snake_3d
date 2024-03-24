
#ifndef FH_ARRAY_H
#define FH_ARRAY_H

#include "fh_base.h"

#define FH_ARRAY_MAGIC 0xAABBCCDD69696969

enum Arr_Type {
	Arr_Type_Fixed,
	Arr_Type_Dynamic,
	Arr_Type_Circular,
	
	Arr_Type_Count
};

struct Arr_Info {
	u64 magic;
	s64 size;
	s64 capacity;
	s64 increase_ammount;
	s64 element_size;
	
	Arr_Type type;
};


#define fh_arr(T) T*

#define fh_fixed_arr(T, c)   (T*)fh_arr_for_real(sizeof(T), c, Arr_Type_Fixed)
#define fh_dynamic_arr(T, c) (T*)fh_arr_for_real(sizeof(T), c, Arr_Type_Dynamic)

#define fh_arr_add(arr, value) { fh_arr_increase_size((void**)&(arr)); (arr)[fh_arr_size(arr) - 1] = value; }

#define fh_arr_free(arr) fh_arr_free_for_real((void**)&(arr));

#define fh_arr_foreach(T, v, a) for(T* v = (T*)a; (s64)(v - (T*)a) < fh_arr_size(a); v += 1)

void* fh_arr_for_real(s64 element_size, s64 capacity, Arr_Type type);
void fh_arr_free_for_real(void** arr);

s64 fh_arr_size(void* arr);
void fh_arr_reset(void* arr);

void fh_arr_increase_size(void** arr);

void* fh_arr_at(void* arr, s64 at);
void fh_arr_remove(void* arr, void* element);
void fh_arr_remove_at(void* arr, s64 at);

s64 fh_arr_find(void* arr, void* target, b32 (*check)(void* target, void* element));

#endif

