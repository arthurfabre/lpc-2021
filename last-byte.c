#define __section(NAME) __attribute__((section(NAME), used))

char __license[] __section("license") = "BSD";

// Shim out all the definitions required by cbpfc
// Real programs should use the proper headers
typedef unsigned long long uint64_t;
_Static_assert(sizeof(uint64_t) == 8, "uint64_t must be 8 bytes");
typedef unsigned int uint32_t;
_Static_assert(sizeof(uint32_t) == 4, "uint32_t must be 4 bytes");
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

typedef char bool;
#define false 0
#define true 1

#define ntohs __builtin_bswap16
#define ntohl __builtin_bswap32

struct xdp_md {
        uint32_t data;
        uint32_t data_end;
};

enum xdp_action {
        XDP_DROP = 1,
        XDP_PASS,
};

__section("xdp") int xdp_filter(struct xdp_md *ctx) {
    uint8_t *data = (uint8_t *)(long)ctx->data;
    uint8_t *data_end = (uint8_t *)(long)ctx->data_end;

    uint64_t size = data_end - data;

	if (data + size > data_end) {
		return 0;
	}

    uint8_t last = *(data + size - 1);
    return last;
}
