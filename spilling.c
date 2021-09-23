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

    if (data + 4 > data_end) {
        return 0;
    }

    uint32_t off = *((uint32_t *) data);
    if (off >= 1024) {
        return 0;
    }

    if (data + off + 1 > data_end) {
        return 0;
    }

    // Force clang to spill things to the stack.
    uint64_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;
    asm volatile("%0 = 0\n"
                 "%1 = 1\n"
                 "%2 = 2\n"
                 "%3 = 3\n"
                 "%4 = 4\n"
                 "%5 = 5\n"
                 "%6 = 6\n"
                 "%7 = 7\n"
                 "%8 = 8\n"
                 "%9 = 9"
                : "=r" (r0), "=r" (r1), "=r" (r2), "=r" (r3), "=r" (r4), "=r" (r5), "=r" (r6), "=r" (r7), "=r" (r8), "=r" (r9)
    );

    uint8_t foo = *(data + off);

    return r0 + r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8 + r9 + foo;
}
