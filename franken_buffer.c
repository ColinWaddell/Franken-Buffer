struct FKNBUFFER *fkn_buffer_setup(struct FKNBUFFER *storage){
  int i;

  for (i=0; i<FKN_OUTTER_BUFF_SIZE; i++)
  {
      // Link next item, or wrap-round to start if at the end
      storage[i].next = (i==FKN_OUTTER_BUFF_SIZE-1) ? storage : &(storage[i+1]);
      storage[i].head =  storage;
      storage[i].buffer = malloc(sizeof(struct FKN_RINGBUFFER));
      storage[i].buffer->index = 0;
    }

  return storage;
}

// LOOK - No ifs or buts!
void fkn_buffer_add(struct FKNBUFFER **buffer, unsigned char value){
  (*buffer)->buffer->data[((*buffer)->buffer->index++)&FKN_INNER_BUFF_SIZE_MASK] = value;
  (*buffer) = (*buffer)->next;
}

// Very unoptimised.
char fkn_buffer_get(struct FKNBUFFER *buffer, unsigned int index){
  struct CSBUFFER *buf = &(buffer->head[index % FKN_OUTTER_BUFF_SIZE]);
  struct RINGBUFFER *rb = buf->buffer;
  return rb->data[index / FKN_OUTTER_BUFF_SIZE];
}

void fkn_buffer_clear(struct FKNBUFFER *buffer){
  unsigned int i, j;

  for (i=0; i<OUTTER_BUFF_SIZE; i++)
    for(j=0; j<INNER_BUFF_SIZE; j++)
      buffer->head[i].buffer->data[j] = 0;
}

