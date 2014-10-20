#ifndef FKN_OUTTER_BUFF_SIZE
  #define FKN_OUTTER_BUFF_SIZE 5
#endif

#ifndef FKN_INNER_BUFF_SIZE
  #define FKN_INNER_BUFF_SIZE 16
#endif

#define FKN_INNER_BUFF_SIZE_MASK (FKN_INNER_BUFF_SIZE-1)
#define FKN_BUFF_SIZE (FKN_OUTTER_BUFF_SIZE*FKN_INNER_BUFF_SIZE)

struct FKN_RINGBUFFER{
  char data[FKN_INNER_BUFF_SIZE];
  unsigned int index;
};

struct FKNBUFFER {
  struct FKN_RINGBUFFER *buffer;
  struct FKNBUFFER *next;
  struct FKNBUFFER *head;
};


struct FKNBUFFER *fkn_buffer_setup(struct FKNBUFFER *storage);
char fkn_buffer_get(struct FKNBUFFER *storage, unsigned int index);
void fkn_buffer_add(struct FKNBUFFER **buffer, unsigned char value);
void fkn_buffer_clear(struct FKNBUFFER *storage);

