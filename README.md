#Franken-Buffer

A combination link-list and ring-buffer for situations where your memory is limited and fragmented.

The inspiration to write this came from using a PIC where I couldn't allocate a large enough single memory
block to buffer data coming in from a high-speed serial link. Due to time constraints of the application,
**this code does not use a single branching statement (if/switch) when adding data to the buffer. Each write
increments the ring buffer and the link list simultaneously.**

Speed savings are made with the ring buffer by masking in the index to ensure it only counts from 1 to any
2<sup>n</sup> value. The link list allows your buffer to be the size of **n** times any arbitrary value. A double ring-buffer
could have been used but this had too many limitations in the total size the buffer could occupy.

#Usage
This is still currently a little dirty.

There are two main declarations which first need setup: `FKN_OUTTER_BUFF_SIZE`, which can be any value and `FKN_INNER_BUFF_SIZE` which must be of 2<sup>n</sup> (ie. 8, 16, 32).

Next, you need to declare your outer buffer. This is a pseudo-link-list. I say pseudo as you can't add/remove nodes, but still uses the concept of holding a pointer to the next entry in it's own structure. The reason for this will become apparent if you look at the implementation of the `fkn_buffer_add` function.

To use the buffer you also need to declare a pointer of type `FKNBUFFER`. This is your route in and out of the buffer and is returned by `fkn_buffer_setup`

Adding data is performed through `fkn_buffer_add` which places a value in the next buffer space. Retrieving data is performed using `fkn_get_data` which takes as a parameter an arbitrary location in the buffer. The add routine is designed to be blindingly fast, the get routine is not.

#Example

```
  int i; 
  struct FKNBUFFER *outer;
  struct FKNBUFFER buffer_raw[FKN_OUTTER_BUFF_SIZE];

  outer = fkn_buffer_setup(buffer_raw);
  fkn_buffer_clear(outer);

  for (i=0; i<FKN_BUFF_SIZE; i++){
    fkn_buffer_add(&outer, i); // Add 0 to 79
  }

  for (i=0; i<FKN_BUFF_SIZE; i++){
    printf("i=%d \t %d\n", i, fkn_buffer_get(outer, i)); // Read out 0 to 79
  }
```

In this example it would be possible to use malloc instead of declaring `buffer_raw` as shown, however for readability this has been ommited.

#Requirements

The setup function currently requires malloc in order to give itself the space it requires to operate.
