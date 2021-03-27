matrix: Matrix/Matrix.cpp Matrix/main.cpp Matrix/IPrint.cpp
	$(CC) $(CFLAGS) $? $(LDFLAGS) -o $@
clean:
	-rm *.o *.~
