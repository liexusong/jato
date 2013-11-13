/*
 * Copyright (c) 2008  Pekka Enberg
 * 
 * This file is released under the 2-clause BSD license. Please refer to the
 * file LICENSE for details.
 */

#include "jit/stack-slot.h"

#include "arch/registers.h"
#include "vm/stdlib.h"

#include <stdlib.h>

struct stack_frame *alloc_stack_frame(unsigned long nr_args,
				      unsigned long nr_local_slots)
{
	struct stack_frame *frame;
	unsigned long i;

	frame = zalloc(sizeof *frame);
	if (!frame)
		return NULL;

	frame->local_slots = calloc(nr_local_slots, sizeof(struct stack_slot));
	if (!frame->local_slots) {
		free(frame);
		return NULL;
	}
	for (i = 0; i < nr_local_slots; i++) {
		struct stack_slot *slot = get_local_slot(frame, i);

		slot->index  = i;
		slot->parent = frame;
	}
	frame->nr_local_slots = nr_local_slots;
	frame->nr_args = nr_args;

	return frame;
}

void free_stack_frame(struct stack_frame *frame)
{
	struct stack_slot *s = frame->spill_slots;

	while (s != NULL) {
		struct stack_slot *p = s;

		s = s->next;
		free(p);
	}

	free(frame->local_slots);
	free(frame);
}

struct stack_slot *get_local_slot(struct stack_frame *frame, unsigned long index)
{
	return &frame->local_slots[index];
}

static struct stack_slot *
__get_spill_slot(struct stack_frame *frame, unsigned long size)
{
	struct stack_slot *slot;

	slot = zalloc(sizeof *slot);
	if (!slot)
		return NULL;

	slot->index = frame->nr_local_slots + frame->nr_spill_slots;
	slot->parent = frame;
	frame->nr_spill_slots += size;

	slot->next = frame->spill_slots;
	frame->spill_slots = slot;

	return slot;
}

struct stack_slot *get_spill_slot_32(struct stack_frame *frame)
{
	return __get_spill_slot(frame, 1);
}

struct stack_slot *get_spill_slot_64(struct stack_frame *frame)
{
	return __get_spill_slot(frame, 2);
}

struct stack_slot *get_spill_slot(struct stack_frame *frame, enum vm_type type)
{
	return __get_spill_slot(frame, vm_type_slot_size(type));
}

struct stack_slot *get_next_slot(struct stack_slot *slot)
{
	return get_local_slot(slot->parent, slot->index + 1);
}
