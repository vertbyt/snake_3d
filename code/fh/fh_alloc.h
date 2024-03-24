
#ifndef FH_ALLOC_H
#define FH_ALLOC_H

#include "fh_base.h"

#define M_ARENA_DEFAULT_ALIGNMENT (2*sizeof(void*))
#define SizeAligned(s, a) ((a)*((s)/(a)) + (a))

// Memory Arena
struct M_Arena {
	void* base;
	s64 size;
	s64 pos;
};

struct M_Arena_Frame {
	M_Arena* arena;
	s64 pos;
};


M_Arena m_arena(void* base, s64 size);
void*   m_arena_alloc(M_Arena* arena, s64 size, s64 alignment = M_ARENA_DEFAULT_ALIGNMENT);
void    m_arena_reset(M_Arena* arena);

M_Arena_Frame m_arena_start_frame(M_Arena* arena);
void          m_arena_end_frame(M_Arena* arena, M_Arena_Frame frame);

// General Memory Stuff
void* m_alloc(s64 size);
void* m_realloc(void* ptr, s64 size);

void* m_alloc(M_Arena* arena, s64 size);
void m_free(void* ptr);

#endif
