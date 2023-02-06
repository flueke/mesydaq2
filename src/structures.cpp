#include "structures.h"
#include <cstddef>

 // Note (flueke): The whole packet structure thing was buggy in mesydaq2. The
 // two structures exceeded the standard max ethernet MTU. Also they were not
 // the same size but MDP_PACKET was cast to DATA_PACKET...

// Standard MTU is 1500 bytes
// IPv4 header is 20 bytes
// UDP header is 8 bytes
static const size_t UDPMaxPayloadSize = 1500 - 20 - 8;

static_assert(sizeof(MDP_PACKET) <= UDPMaxPayloadSize);
static_assert(sizeof(DATA_PACKET) <= UDPMaxPayloadSize);
static_assert(sizeof(MDP_PACKET) == sizeof(DATA_PACKET));