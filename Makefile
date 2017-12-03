
$(shell mkdir -p obj)
objFile = main.o log.o
obj = ./obj
bin = Log

all: $(objFile)
	cd $(obj); $(CXX) -Wall -o ../$(bin) $(objFile)
	@echo "make succ"

main.o:
	$(CXX) -Wall -c main.cpp -o $(obj)/main.o

log.o:
	$(CXX) -Wall -c log.cpp -o $(obj)/log.o


.PHONY: clean

clean:
	-rm -rf $(obj) $(bin)
