gdn : gdn.o
	$(CC) -o gdn gdn.o -lgmp $(CFLAGS) $(LDFLAGS)

clean :
	rm gdn gdn.o

install : gdn
	install gdn /usr/bin
