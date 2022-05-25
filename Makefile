PROG = project04
OBJS = scan.o parse.o project04.o

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c project04.h
        gcc $(CFLAGS) -c -o $@ $<

all : $(PROG)

$(PROG) : $(OBJS)
        gcc $(CFLAGS) -o $@ $(OBJS)

clean :
        rm -rf $(PROG) $(OBJS)
