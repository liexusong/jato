/*
 * cafebabe - the class loader library in C
 * Copyright (C) 2009  Tomasz Grabiec <tgrabiec@gmail.com>
 *
 * This file is released under the 2-clause BSD license. Please refer to the
 * file LICENSE for details.
 */

#include <stdio.h>
#include <stdlib.h>

#include "cafebabe/attribute_info.h"
#include "cafebabe/line_number_table_attribute.h"
#include "cafebabe/stream.h"

int cafebabe_line_number_table_attribute_init(
	struct cafebabe_line_number_table_attribute *a,
	struct cafebabe_stream *s)
{
	if (cafebabe_stream_read_uint16(s, &a->line_number_table_length))
		goto out;

	a->line_number_table = cafebabe_stream_malloc(s,
		sizeof(*a->line_number_table) * a->line_number_table_length);
	if (!a->line_number_table)
		goto out;

	for (uint16_t i = 0; i < a->line_number_table_length; ++i) {
		struct cafebabe_line_number_table_entry *e
			= &a->line_number_table[i];

		if (cafebabe_stream_read_uint16(s, &e->start_pc))
			goto out_line_number_table;

		if (cafebabe_stream_read_uint16(s, &e->line_number))
			goto out_line_number_table;
	}

	if (!cafebabe_stream_eof(s)) {
		s->cafebabe_errno = CAFEBABE_ERROR_EXPECTED_EOF;
		goto out_line_number_table;
	}

	/* Success */
	return 0;

out_line_number_table:
	free(a->line_number_table);
out:
	return 1;
}

void cafebabe_line_number_table_attribute_deinit(
	struct cafebabe_line_number_table_attribute *a)
{
	free(a->line_number_table);
}

int cafebabe_read_line_number_table_attribute(
	const struct cafebabe_class *class,
	const struct cafebabe_attribute_array *attributes,
	struct cafebabe_line_number_table_attribute *attrib)
{
	unsigned int line_number_table_index = 0;
	if (cafebabe_attribute_array_get(attributes,
		"LineNumberTable", class, &line_number_table_index))
	{
		attrib->line_number_table_length = 0;
		attrib->line_number_table = NULL;
		return 0;
	}

	const struct cafebabe_attribute_info *attribute
		= &attributes->array[line_number_table_index];

	struct cafebabe_stream stream;
	cafebabe_stream_open_buffer(&stream,
		attribute->info, attribute->attribute_length);

	if (cafebabe_line_number_table_attribute_init(attrib, &stream))
		return -1;

	cafebabe_stream_close_buffer(&stream);
	return 0;
}
