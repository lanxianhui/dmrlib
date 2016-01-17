#include "dmr/fec/qr_16_7.h"
#include "dmr/bits.h"
#include "dmr/log.h"

static uint16_t qr_16_7_encoder_map[] = {
	0x0000, 0x0273, 0x04e5, 0x0696, 0x09c9, 0x0bba, 0x0d2c, 0x0f5f,
	0x11e2, 0x1391, 0x1507, 0x1774, 0x182b, 0x1a58, 0x1cce, 0x1ebd,
	0x21b7, 0x23c4, 0x2552, 0x2721, 0x287e, 0x2a0d, 0x2c9b, 0x2ee8,
	0x3055, 0x3226, 0x34b0, 0x36c3, 0x399c, 0x3bef, 0x3d79, 0x3f0a,
	0x411e, 0x436d, 0x45fb, 0x4788, 0x48d7, 0x4aa4, 0x4c32, 0x4e41,
	0x50fc, 0x528f, 0x5419, 0x566a, 0x5935, 0x5b46, 0x5dd0, 0x5fa3,
	0x60a9, 0x62da, 0x644c, 0x663f, 0x6960, 0x6b13, 0x6d85, 0x6ff6,
	0x714b, 0x7338, 0x75ae, 0x77dd, 0x7882, 0x7af1, 0x7c67, 0x7e14,
	0x804f, 0x823c, 0x84aa, 0x86d9, 0x8986, 0x8bf5, 0x8d63, 0x8f10,
	0x91ad, 0x93de, 0x9548, 0x973b, 0x9864, 0x9a17, 0x9c81, 0x9ef2,
	0xa1f8, 0xa38b, 0xa51d, 0xa76e, 0xa831, 0xaa42, 0xacd4, 0xaea7,
	0xb01a, 0xb269, 0xb4ff, 0xb68c, 0xb9d3, 0xbba0, 0xbd36, 0xbf45,
    0xc151, 0xc322, 0xc5b4, 0xc7c7, 0xc898, 0xcaeb, 0xcc7d, 0xce0e,
    0xd0b3, 0xd2c0, 0xd456, 0xd625, 0xd97a, 0xdb09, 0xdd9f, 0xdfec,
    0xe0e6, 0xe295, 0xe403, 0xe670, 0xe92f, 0xeb5c, 0xedca, 0xefb9,
    0xf104, 0xf377, 0xf5e1, 0xf792, 0xf8cd, 0xfabe, 0xfc28, 0xfe5b
};

void dmr_qr_16_7_encode(uint8_t buf[2])
{
    /* See Table E.6: Transmit bit order for voice burst with embedded signalling fragment 1 */
    uint16_t dv = (buf[0] >> 1) & 0x7f;
    uint16_t qr = qr_16_7_encoder_map[dv];
    dmr_log_trace("QR(16,7): encode %02x, qr = %04x", dv, qr);
    buf[0] = qr >> 8;
    buf[1] = qr & 0xff;
}

bool dmr_qr_16_7_decode(uint8_t buf[2])
{
    uint8_t dv = buf[0] >> 1;
    uint16_t parity = (buf[0] & 0x01) << 8 | buf[1];
    dmr_log_trace("QR(16,7): dv=%02x, parity=%04x", dv, parity);
    return (qr_16_7_encoder_map[dv] & 0x1ff) == parity;
}
