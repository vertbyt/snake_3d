
#include "fh_array.h"
#include "fh_alloc.h"
#include "string.h" // for memcpy

void* fh_arr_for_real(s64 element_size, s64 capacity, Arr_Type type) {
	Arr_Info info = {};
	info.magic = FH_ARRAY_MAGIC;
	info.size = 0;
	info.capacity = capacity;
	info.increase_ammount = capacity;
	info.element_size = element_size;
	info.type = type;
	
	void* mem = m_alloc(sizeof(Arr_Info) + element_size*capacity);
	Arr_Info* h = (Arr_Info*)mem;
	*h = info;
	
	void* first = (void*)((u8*)mem + sizeof(Arr_Info));
	return first;
}



internal Arr_Info* fh_arr_get_info(void* arr) {
	Arr_Info* r = (Arr_Info*)((u8*)arr - sizeof(Arr_Info));
	return r;
}


internal void fh_arr_check(void* arr) {
	Assert(arr != NULL);
	
	Arr_Info* info = fh_arr_get_info(arr);
	Assert(info->magic == FH_ARRAY_MAGIC);
}


void fh_arr_increase_size(void** arr) {
	fh_arr_check(*arr);
	Arr_Info* info = fh_arr_get_info(*arr);
	info->size += 1;
	
	if(info->size > info->capacity) {
		switch(info->type) {
			case Arr_Type_Fixed: {
				Assert(!"Fixed array overflow!");
			}break;
			case Arr_Type_Dynamic: {
				info->capacity += info->increase_ammount;
				void* mem = m_realloc((void*)info, sizeof(Arr_Info) + info->element_size*info->capacity);
				*arr = (u8*)mem + sizeof(Arr_Info);
			}break;
		}
	}
}

void fh_arr_free_for_real(void** arr) {
	fh_arr_check(*arr);
	u8* ptr = (u8*)*arr - sizeof(Arr_Info);
	m_free(ptr);
	*arr = NULL;
}

s64 fh_arr_size(void* arr) {
	fh_arr_check(arr);
	Arr_Info* info = fh_arr_get_info(arr);
	return info->size;
}

void fh_arr_reset(void* arr) {
	fh_arr_check(arr);
	Arr_Info* info = fh_arr_get_info(arr);
	info->size = 0;
}


void* fh_arr_at(void* arr, s64 at) {
	Assert(at < fh_arr_size(arr));
	Assert(at >= 0);
	fh_arr_check(arr);

	Arr_Info* info = fh_arr_get_info(arr);
	void* element = (u8*)arr + at*info->element_size;
	return element;
}

void fh_arr_remove(void* arr, void* element) {
	fh_arr_check(arr);

	Arr_Info* info = fh_arr_get_info(arr);
	Assert(info->size > 0);
	
	s64 address_diff = (u8*)element - (u8*)arr;
	
	Assert(address_diff >= 0);
	Assert(address_diff%info->element_size == 0);
	
	s64 at = address_diff/info->element_size;
	Assert(at < info->size);
	
	if(info->size > 1) {
		u8* at_ptr   = (u8*)arr + at*info->element_size;
		u8* last_ptr = (u8*)arr + (info->size - 1)*info->element_size;
		memcpy(at_ptr, last_ptr, info->element_size);
	}
	
	info->size -= 1;
}

void fh_arr_remove_at(void* arr, s64 at) {
	fh_arr_check(arr);

	Arr_Info* info = fh_arr_get_info(arr);
	Assert(info->size > 0);
	
	Assert(at < info->size);
	
	u8* at_ptr   = (u8*)arr + at*info->element_size;
	u8* last_ptr = (u8*)arr + (info->size - 1)*info->element_size;
	memcpy(at_ptr, last_ptr, info->element_size);
	
	info->size -= 1;
}



s64 fh_arr_find(void* arr, void* target, b32 (*check)(void* target, void* element)) {
	fh_arr_check(arr);
	
	s64 r = -1;
	Loop(i, fh_arr_size(arr)) {
		void* element = fh_arr_at(arr, i);
		if(check(target, element)) {
			r = i;
			break;
		}
	}
	
	return r;
}
