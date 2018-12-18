# ===========================================================
$(CC) ?= gcc
$(AR) ?= ar
# ===========================================================
main:libschnix_systems.o libschnix_stream.o libschnix_transform.o libschnix_joypad.o libschnix_keyboard.o libschnix_bitmap.o libschnix_sample.o libschnix_renderer.o libschnix_socket.o
	$(AR) crv libschnix.a libschnix_systems.o libschnix_stream.o libschnix_transform.o libschnix_joypad.o libschnix_keyboard.o libschnix_bitmap.o libschnix_sample.o libschnix_renderer.o libschnix_socket.o
libschnix_systems.o:libschnix_systems.c
	$(CC) -c libschnix_systems.c
libschnix_stream.o:libschnix_stream.c
	$(CC) -c libschnix_stream.c
libschnix_transform.o:libschnix_transform.c
	$(CC) -c libschnix_transform.c
libschnix_joypad.o:libschnix_joypad.c
	$(CC) -c libschnix_joypad.c
libschnix_keyboard.o:libschnix_keyboard.c
	$(CC) -c libschnix_keyboard.c
libschnix_bitmap.o:libschnix_bitmap.c
	$(CC) -c libschnix_bitmap.c
libschnix_sample.o:libschnix_sample.c
	$(CC) -c libschnix_sample.c
libschnix_renderer.o:libschnix_renderer.c
	$(CC) -c libschnix_renderer.c
libschnix_socket.o:libschnix_socket.c
	$(CC) -c libschnix_socket.c
clean:
	rm -f *.o main