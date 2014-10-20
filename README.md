#Franken-Buffer

A combination link-list and ring-buffer for situations where your memory is limited and fragmented.

The inspiration to write this came from using a PIC where I couldn't allocate a large enough single memory
block to buffer data coming in from a high-speed serial link. Due to time constraints of the application,
this code does not use a single branching statement (if/switch) when adding data to the buffer. Each write
increments the ring buffer and the link list simultaneously.

Speed savings are made with the ring buffer by masking in the index to ensure it only counts from 1 to any
2^n value. The link list allows your buffer to be the size of n times any arbitrary value. A double ring-buffer
could have been used but this had too many limitations in the total size the buffer could occupy.

