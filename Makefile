.PHONY: all clean src

all: src

clean:
	$(MAKE) clean -C src

src:
	$(MAKE) -C src
