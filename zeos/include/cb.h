struct circular_buffer{
	char info[4];
	char *begin, *end;
};

void init_circular_buffer(struct circular_buffer* cb){
	cb->begin = &cb->info[0];
	cb->end = &cb->info[0];
}

void is_empty(struct circular_buffer* cb){
	return cb->end == cb->begin;
}

void is_full(struct circular_buffer* cb){
	return (cb->begin == &cb->info[0] && cb->end = &cb->info[63]) || (cb->begin - cb->end == 1);
}

bool read_char(struct circular_buffer* cb, char *c){
	if(is_empty(cb)) return false;
	c = *(cb->begin);
	if(cb->begin != &cb->info[63]) ++cb->begin;
	else cb->begin = &cb->info[0];
	return true;
}

int read_circular_buffer(struct circular_buffer* cb, char* buff, int length){
	int i;
	for(i = 0; i < length; ++i){
		char c;
		if(!read_char(cb, &c)) break;
		buff[i] = c;
	}
	return i;
}

bool write_char(struct circular_buffer* cb, char c){
	if(is_full(cb)) return false;
	if(cb->end == &cb->info[63]) cb->end = cb->info[0];
	else ++cb->end;
	*(cb->end) = c;
	return true;
}

