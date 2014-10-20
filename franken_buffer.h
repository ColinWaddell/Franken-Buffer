#ifndef OUTTER_BUFF_SIZE
  #define OUTTER_BUFF_SIZE 5
#endif

#ifndef INNER_BUFF_SIZE
  #define INNER_BUFF_SIZE 16
#endif

#define INNER_BUFF_SIZE_MASK (INNER_BUFF_SIZE-1)
#define BUFF_SIZE (OUTTER_BUFF_SIZE*INNER_BUFF_SIZE)

struct FKN_RINGBUFFER{
  char data[INNER_BUFF_SIZE];
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

