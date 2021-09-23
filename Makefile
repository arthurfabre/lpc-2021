CLANG := clang-9
CFLAGS := -target bpf -mcpu=v3 -O2 -g -nostdinc -Wall -Werror -Wno-address-of-packed-member -Iheaders/upstream -Iheaders

%.elf: %.c
	$(CLANG) $(CFLAGS) -c $< -o $@
