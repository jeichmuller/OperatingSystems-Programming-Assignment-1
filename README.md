# OS-Assingment1

Programming Assignment #1 for Operating Systems

Jay Eichmuller


Run using: 

$ gcc producer.c -pthread -lrt -o producer

$ gcc consumer.c -pthread -lrt -o consumer

$ ./producer & ./consumer &


Files included
producer.c : holds the producer process
consumer.c : holds the consumer process
shared.h : holds definitions needed by both producer.c and consumer.c for sem structure and buffer

Producer produces characters a-z, produces until the table is full then waits for consumer to consume characters and can then produce again once table has open spots. Can run infinitely but kept it to only producing and consuming each letter of the alphabet.

The program uses shared memory and semaphores to allow synchronization between the producer and consumer. And mutual exclusion is in the code with the use of empty and full semaphores


By compiling with `gcc producer.c -pthread -lrt -o producer` and `gcc consumer.c -pthread -lrt -o consumer`.
And then running `./producer & ./consumer &`. The example code output should look like this:
```
Producer sent item on 0: a
Producer sent item on 1: b
Consumer got item on 0: a
Producer sent item on 0: c
Consumer got item on 1: b
Producer sent item on 1: d
Consumer got item on 0: c
Producer sent item on 0: e
Consumer got item on 1: d
Producer sent item on 1: f
Consumer got item on 0: e
Producer sent item on 0: g
Consumer got item on 1: f
Producer sent item on 1: h
Consumer got item on 0: g
Producer sent item on 0: i
Consumer got item on 1: h
Producer sent item on 1: j
Consumer got item on 0: i
Producer sent item on 0: k
Consumer got item on 1: j
Producer sent item on 1: l
Consumer got item on 0: k
Producer sent item on 0: m
Consumer got item on 1: l
Producer sent item on 1: n
Consumer got item on 0: m
Producer sent item on 0: o
Consumer got item on 1: n
Producer sent item on 1: p
Consumer got item on 0: o
Producer sent item on 0: q
Consumer got item on 1: p
Producer sent item on 1: r
Consumer got item on 0: q
Producer sent item on 0: s
Consumer got item on 1: r
Producer sent item on 1: t
Consumer got item on 0: s
Producer sent item on 0: u
Consumer got item on 1: t
Producer sent item on 1: v
Consumer got item on 0: u
Producer sent item on 0: w
Consumer got item on 1: v
Producer sent item on 1: x
Consumer got item on 0: w
Producer sent item on 0: y
Consumer got item on 1: x
Producer sent item on 1: z
Consumer got item on 0: y
Consumer got item on 1: z
```
