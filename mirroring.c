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

// Converted cBPF filter

// True if packet matches, false otherwise
static inline
uint32_t filter(const uint8_t *const data, const uint8_t *const data_end) {
        __attribute__((unused))
        uint32_t a, x, m[16];


block_0:
__attribute__((unused));
        if (data + 12337 > data_end) return 0;
        x = 0;
        a = *(data + 12336);
        if (a == 808464432) goto block_50;

block_2:
__attribute__((unused));
        if (data + 12340 > data_end) return 0;
        a = *(data + 12336);
        a = *(data + 12336);
        a = ntohl(*((uint32_t *) (data + 12336)));
        if (a & 808464432) goto block_12;

block_6:
__attribute__((unused));
        a += 875573296;
        m[7] = a;
        a = ntohl(*((uint32_t *) (data + 48)));
        x = a;
        a = m[7];
        if (a != x) goto block_53;

block_12:
__attribute__((unused));
        a = ntohs(*((uint16_t *) (data + 64)));
        if (a != 12336) goto block_31;

block_14:
__attribute__((unused));
        m[2] = a;
        a = *(data + 12336);
        x = a;
        a = *(data + 12336);
        if (a == x) goto block_31;

block_19:
__attribute__((unused));
        a = *(data + 12336);
        a = *(data + 12336);
        a = *(data + 12336);
        a = *(data + 12336);
        a = *(data + 12336);
        a = *(data + 12336);
        a = *(data + 12336);
        a = *(data + 12336);
        a = *(data + 12336);
        x = a;
        a = *(data + 12336);
        a = *(data + 12336);

block_31:
__attribute__((unused));
        if (x >= 65467 || data + x + 68 > data_end) return 0;
        a = ntohs(*((uint16_t *) (data + x + 66)));
        if (a == 12336) goto block_42;

block_33:
__attribute__((unused));
        a = *(data + 12336);
        if (a == 808464432) goto block_42;

block_35:
__attribute__((unused));
        if (data + 12409 > data_end) return 0;
        a = *(data + 12336);
        a = *(data + 12336);
        x = a;
        a = *(data + 12336);
        a = *(data + 12336);
        a = *(data + 12408);
        if (a != 808464432) goto block_53;

block_42:
__attribute__((unused));
        a = *(data + 12336);
        a &= 808464432;
        if (a == 808464432) goto block_54;

block_45:
__attribute__((unused));
        a = *(data + 12336);
        a = *(data + 12336);
        a = *(data + 12336);
        a = *(data + 12336);
        a = *(data + 12336);

block_50:
__attribute__((unused));
        x = a;
        a = *(data + 12336);
        if (a == x) goto block_54;

block_53:
__attribute__((unused));
        return 808464432;

block_54:
__attribute__((unused));
        return 808464432;

}

__section("xdp") int xdp_filter(struct xdp_md *ctx) {
        uint8_t *data = (uint8_t *)(long)ctx->data;
        uint8_t const *data_end = (uint8_t *)(long)ctx->data_end;

        if (filter(data, data_end)) {
                return XDP_DROP;
        }

        return XDP_PASS;
}
