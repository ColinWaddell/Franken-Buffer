#ifndef OUTTER_BUFF_SIZE
  #define OUTTER_BUFF_SIZE 5
#endif

#ifndef INNER_BUFF_SIZE
  #define INNER_BUFF_SIZE 16
#endif

#define INNER_BUFF_SIZE_MASK (INNER_BUFF_SIZE-1)
#define BUFF_SIZE (OUTTER_BUFF_SIZE*INNER_BUFF_SIZE)

struct RINGBUFFER{
  char data[INNER_BUFF_SIZE];
  unsigned int index;
};

struct CSBUFFER {
  struct RINGBUFFER *buffer;
  struct CSBUFFER *next;
  struct CSBUFFER *head;
};


struct CSBUFFER *buffer_setup(struct CSBUFFER *storage);
#INLINE
char buffer_get(struct CSBUFFER *storage, unsigned int index);
void buffer_add(struct CSBUFFER **buffer, unsigned char value);
void buffer_clear(struct CSBUFFER *storage);

