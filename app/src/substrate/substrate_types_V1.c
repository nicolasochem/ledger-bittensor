/*******************************************************************************
 *  (c) 2019 - 2023 Zondax AG
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/
#include "bignum.h"
#include "coin.h"
#include "parser_impl.h"
#include "substrate_dispatch_V1.h"
#include "substrate_strings.h"

#include <stddef.h>
#include <stdint.h>
#include <zxformat.h>
#include <zxmacros.h>

parser_error_t _readAccountId_V1(parser_context_t* c, pd_AccountId_V1_t* v) {
    GEN_DEF_READARRAY(32)
}

parser_error_t _readCompactAccountIndex_V1(parser_context_t* c, pd_CompactAccountIndex_V1_t* v)
{
    return _readCompactInt(c, &v->value);
}

parser_error_t _readLookupasStaticLookupSource_V1(parser_context_t* c, pd_LookupasStaticLookupSource_V1_t* v)
{
    CHECK_INPUT()
    CHECK_ERROR(_readUInt8(c, &v->value))
    switch (v->value) {
    case 0: // Id
        CHECK_ERROR(_readAccountId_V1(c, &v->id))
        break;
    case 1: // Index
        CHECK_ERROR(_readCompactAccountIndex_V1(c, &v->index))
        break;
    case 2: // Raw
        CHECK_ERROR(_readBytes(c, &v->raw))
        break;
    case 3: // Address32
        GEN_DEF_READARRAY(32)
        break;
    case 4: // Address20
        GEN_DEF_READARRAY(20)
        break;
    default:
        return parser_unexpected_value;
    }

    return parser_ok;
}

parser_error_t _readStakingAddress32_V1(parser_context_t* c, pd_StakingAddress32_V1_t* v)
{
    CHECK_INPUT()
    GEN_DEF_READARRAY(32)

    return parser_ok;
}

///////////////////////////////////
///////////////////////////////////
///////////////////////////////////

parser_error_t _toStringAccountId_V1(
    const pd_AccountId_V1_t* v,
    char* outValue,
    uint16_t outValueLen,
    uint8_t pageIdx,
    uint8_t* pageCount)
{
    return _toStringPubkeyAsAddress(v->_ptr, outValue, outValueLen, pageIdx, pageCount);
}

parser_error_t _toStringCompactAccountIndex_V1(
    const pd_CompactAccountIndex_V1_t* v,
    char* outValue,
    uint16_t outValueLen,
    uint8_t pageIdx,
    uint8_t* pageCount)
{
    return _toStringCompactInt(&v->value, 0, false, "", "", outValue, outValueLen, pageIdx, pageCount);
}

parser_error_t _toStringLookupasStaticLookupSource_V1(
    const pd_LookupasStaticLookupSource_V1_t* v,
    char* outValue,
    uint16_t outValueLen,
    uint8_t pageIdx,
    uint8_t* pageCount)
{
    CLEAN_AND_CHECK()
    switch (v->value) {
    case 0: // Id
        CHECK_ERROR(_toStringAccountId_V1(&v->id, outValue, outValueLen, pageIdx, pageCount))
        break;
    case 1: // Index
        CHECK_ERROR(_toStringCompactAccountIndex_V1(&v->index, outValue, outValueLen, pageIdx, pageCount))
        break;
    case 2: // Raw
        CHECK_ERROR(_toStringBytes(&v->raw, outValue, outValueLen, pageIdx, pageCount))
        break;
    case 3: // Address32
    {
        GEN_DEF_TOSTRING_ARRAY(32)
    }
    case 4: // Address20
    {
        GEN_DEF_TOSTRING_ARRAY(20)
    }
    default:
        return parser_not_supported;
    }

    return parser_ok;
}

parser_error_t _toStringStakingAddress32_V1(
    const pd_StakingAddress32_V1_t* v,
    char* outValue,
    uint16_t outValueLen,
    uint8_t pageIdx,
    uint8_t* pageCount)
{
    return _toStringPubkeyAsAddress(v->_ptr, outValue, outValueLen, pageIdx, pageCount);
}

parser_error_t _toStringCodeBytes_V1(
    const pd_Bytes_t* v,
    char* outValue,
    uint16_t outValueLen,
    uint8_t pageIdx,
    uint8_t* pageCount)
{
    char* outValueEnd = outValue;
    // === Add '0x' to start ===
    strncpy(outValue, "0x", 2);
    outValueEnd += 2;

    // Truncate the code hex if the length is greater than 8 bytes
    // e.g. 12345678900abcdef -> 0x1234567...abcdef (around 8 bytes long, or ~16 characters) 
    if ( v->_len <= 8 ) {
        // Short enough that we don't need to truncate the code hex

        // verify that the output buffer is large enough
        //   to avoid segfault
        if ( 2 + (v->_len * 2) + 1 > outValueLen ) { // 0x + 2 chars per byte + null terminator
            return parser_value_too_many_bytes;
        }
        parser_error_t result = _toStringBytes(v, outValueEnd, outValueLen - 2, pageIdx, pageCount);
        return result;
    } else {
        // === Truncate the code hex to be around 16 characters long ===
        // Only show the first 3 bytes of the code hex and the last 3 bytes
        // e.g. 12345678900abcdef -> 0x123456...abcdef
        pd_Bytes_t truncated_v_start = {
            ._ptr = v->_ptr,
            ._len = 3
        };

        pd_Bytes_t truncated_v_end = {
            ._ptr = v->_ptr + (v->_len - 3),
            ._len = 3
        };

        // === Add the first 3 bytes ===
        parser_error_t truncated_result_start = _toStringBytes(&truncated_v_start, outValueEnd, outValueLen - 2, pageIdx, pageCount);
        if (truncated_result_start != parser_ok) {
            return truncated_result_start; // Return error early
        }
        outValueEnd += (2 * 3); // 2 characters per byte
        // === Add the ellipsis ===
        strncpy(outValueEnd, "...", 3); // Add after the first 3 bytes, 2 characters per byte
        outValueEnd += 3;
        // === Add the last 3 bytes ===
        parser_error_t truncated_result_end = _toStringBytes(&truncated_v_end, outValueEnd, outValueLen - (2 + 2 * 3 + 3), pageIdx, pageCount);
        if (truncated_result_end != parser_ok) {
            return truncated_result_end; // Return error early
        }
        
        return parser_ok;
    }
}