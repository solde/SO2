#ifndef __ZEOS_CIRCULAR_BUFFER_H__
#define __ZEOS_CIRCULAR_BUFFER_H__

#define MAX_SIZE 8

struct circular_buffer{
	char info[MAX_SIZE];
	char begin, end;
	char full;
};

void init_circular_buffer(struct circular_buffer* cb);
int cb_is_empty(struct circular_buffer* cb);
int cb_is_full(struct circular_buffer* cb);
int cb_size(struct circular_buffer *cb);

int cb_write(struct circular_buffer *cb, char c);
int cb_read(struct circular_buffer *cb, char *c);

#endif
