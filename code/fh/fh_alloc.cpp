
#include "fh_alloc.h"
#include "stdlib.h" // for malloc and free

internal void zero_memory(void* ptr, s64 size) {
  u64* p64 = (u64*)ptr;
  s64 s0 = size/sizeof(u64);
  Loop(i, s0) p64[i] = 0;
  
  u8* p8 = (u8*)ptr + s0*sizeof(u64);
  s64 s1 = size - s0*sizeof(u64);
  Loop(i, s1) p8[i] = 0;
}

// ***********************
// General Memory Stuff
void* m_alloc(s64 size) { return malloc(size); }
void* m_realloc(void *ptr, s64 size) { return realloc(ptr, size); }

void* m_alloc(M_Arena* arena, s64 size) { return m_arena_alloc(arena, size); }

void m_free(void* ptr) { free(ptr); } 

// ********************
// Memory Arena
M_Arena m_arena(void* base, s64 size) {
	M_Arena r = {};
	r.base = base;
	r.size = size;
	return r;
}

void* m_arena_alloc(M_Arena* arena, s64 size, s64 alignment) {
	s64 size_aligned = SizeAligned(size, alignment);
	if(arena->pos + size_aligned > arena->size) Assert(!"Can't fit alloc size!!");
	
	void* r = (u8*)arena->base + arena->pos;
	arena->pos += size_aligned;
	
	zero_memory(r, size_aligned);
	
	return r;
}

void m_arena_reset(M_Arena* arena) {
	arena->pos = 0;
}

M_Arena_Frame m_arena_start_frame(M_Arena* arena) {
	M_Arena_Frame r = {arena, arena->pos};
	return r;
}

void m_arena_end_frame(M_Arena* arena, M_Arena_Frame frame) {
	Assert(frame.arena == arena);
	arena->pos = frame.pos;
}




