struct FKNBUFFER *buffer_setup(struct FKNBUFFER *storage){
  int i;

  for (i=0; i<OUTTER_BUFF_SIZE; i++)
  {
      storage[i].next = (i==OUTTER_BUFF_SIZE-1) ? storage : &(storage[i+1]);
      storage[i].head =  storage;
      storage[i].buffer = malloc(sizeof(struct FKN_RINGBUFFER));
      storage[i].buffer->index = 0;
    }

  return storage;
}

void buffer_add(struct FKNBUFFER **buffer, unsigned char value){
  (*buffer)->buffer->data[((*buffer)->buffer->index++)&INNER_BUFF_SIZE_MASK] = value;
  (*buffer) = (*buffer)->next;
}

char buffer_get(struct FKNBUFFER *buffer, unsigned int index){
  struct CSBUFFER *buf = &(buffer->head[index % OUTTER_BUFF_SIZE]);
  struct RINGBUFFER *rb = buf->buffer;
  return rb->data[index / OUTTER_BUFF_SIZE];
}

void buffer_clear(struct FKNBUFFER *buffer){
  unsigned int i, j;

  for (i=0; i<OUTTER_BUFF_SIZE; i++)
    for(j=0; j<INNER_BUFF_SIZE; j++)
      buffer->head[i].buffer->data[j] = 0;
}

