CC = g++

CFLAGS = -Wall -g

INCLUDES = 

LFLAGS = -lpthread

LIBS = 

SRCS = main.cpp QoSQueue.cpp Examples.cpp DataStr.cpp

OUTDIR = ./build

OBJS = $(SRCS:.cpp=.o)

OUTOBJS = $(addprefix $(OUTDIR)/, $(OBJS))

MAIN = Runnable.out

.PHONY: depend clean

all: $(MAIN)

$(MAIN): $(OUTDIR) | $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(OUTDIR)/$(MAIN) $(OUTOBJS) $(LFLAGS) $(LIBS)

$(OUTDIR):
	mkdir ./build

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(OUTDIR)/$@

clean:
	rm -f $(MAIN)
	rm -r $(OUTDIR)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

run:
	./$(MAIN)