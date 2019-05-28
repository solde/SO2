#include <circular_buffer.h>

void init_circular_buffer(struct circular_buffer* cb){
	cb->begin = 0;
	cb->end = 0;
}

int cb_is_full(struct circular_buffer* cb){
	if(cb->begin == cb->end && cb->full) return 1;
	return 0;
}

int cb_is_empty(struct circular_buffer* cb){
	if(cb->end == cb->begin && !cb->full) return 1;
	return 0;
}

int cb_size(struct circular_buffer *cb){
	if(cb_is_full(cb)) return MAX_CB_SIZE;
	if(cb_is_empty(cb)) return 0;
	int s = cb->end - cb->begin;
	if(s > 0){
		return s;
	}
	return MAX_CB_SIZE + s;
}

int cb_write(struct circular_buffer *cb, char c){
	if(cb_is_full(cb)) return -1;
	cb->info[cb->end] = c;
	cb->end = (cb->end+1) % MAX_CB_SIZE;

	if(cb->end == cb->begin) cb->full = 1;
	return 1;
}

int cb_read(struct circular_buffer *cb, char *c){
	if(cb_is_empty(cb)) return -1;

	*c = cb->info[cb->begin];
	cb->begin = (cb->begin+1)%MAX_CB_SIZE;
	cb->full = 0;
	return 1;
}
