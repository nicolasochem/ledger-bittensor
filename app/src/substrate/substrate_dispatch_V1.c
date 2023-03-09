/*******************************************************************************
 *  (c) 2019 - 2022 Zondax AG
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

#include "substrate_dispatch_V1.h"
#include "substrate_strings.h"
#include "zxmacros.h"
#include <stdint.h>
#ifdef LEDGER_SPECIFIC
#include "bolos_target.h"
#endif

__Z_INLINE parser_error_t _readMethod_balances_transfer_V1(
    parser_context_t* c, pd_balances_transfer_V1_t* m)
{
    CHECK_ERROR(_readLookupasStaticLookupSource_V1(c, &m->dest))
    CHECK_ERROR(_readCompactBalance(c, &m->amount))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_balances_force_transfer_V1(
    parser_context_t* c, pd_balances_force_transfer_V1_t* m)
{
    CHECK_ERROR(_readLookupasStaticLookupSource_V1(c, &m->source))
    CHECK_ERROR(_readLookupasStaticLookupSource_V1(c, &m->dest))
    CHECK_ERROR(_readCompactBalance(c, &m->amount))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_balances_transfer_keep_alive_V1(
    parser_context_t* c, pd_balances_transfer_keep_alive_V1_t* m)
{
    CHECK_ERROR(_readLookupasStaticLookupSource_V1(c, &m->dest))
    CHECK_ERROR(_readCompactBalance(c, &m->amount))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_balances_transfer_all_V1(
    parser_context_t* c, pd_balances_transfer_all_V1_t* m)
{
    CHECK_ERROR(_readLookupasStaticLookupSource_V1(c, &m->dest))
    CHECK_ERROR(_readbool(c, &m->keep_alive))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_paratensor_add_stake_V1(
    parser_context_t* c, pd_paratensor_add_stake_V1_t * m)
{
    CHECK_ERROR(_readStakingAddress32_V1(c, &m->hotkey))
    CHECK_ERROR(_readBalance(c, &m->amount_staked ))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_paratensor_remove_stake_V1(
    parser_context_t* c, pd_paratensor_remove_stake_V1_t * m)
{
    CHECK_ERROR(_readStakingAddress32_V1(c, &m->hotkey))
    CHECK_ERROR(_readBalance(c, &m->amount_unstaked ))
    return parser_ok;
}

#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif

__Z_INLINE parser_error_t _readMethod_paratensor_sudo_add_network_V1(
    parser_context_t* c, pd_paratensor_sudo_add_network_V1_t * m)
{
    CHECK_ERROR(_readu16(c, &m->netuid ))
    CHECK_ERROR(_readu16(c, &m->tempo ))
    CHECK_ERROR(_readu16(c, &m->modality ))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_sudo_sudo_V1(
    parser_context_t* c, pd_sudo_sudo_V1_t * m)
{
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_sudo_set_key_V1(
    parser_context_t* c, pd_sudo_set_key_V1_t * m)
{
    CHECK_ERROR(_readLookupasStaticLookupSource_V1(c, &m->new_))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_balances_set_balance_V1(
    parser_context_t* c, pd_balances_set_balance_V1_t* m)
{
    CHECK_ERROR(_readLookupasStaticLookupSource_V1(c, &m->who))
    CHECK_ERROR(_readCompactBalance(c, &m->new_free))
    CHECK_ERROR(_readCompactBalance(c, &m->new_reserved))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_balances_force_unreserve_V1(
    parser_context_t* c, pd_balances_force_unreserve_V1_t* m)
{
    CHECK_ERROR(_readLookupasStaticLookupSource_V1(c, &m->who))
    CHECK_ERROR(_readBalance(c, &m->amount))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_system_set_code_V1(
    parser_context_t* c, pd_system_set_code_V1_t* m)
{
    CHECK_ERROR(_readBytes(c, &m->code))
    return parser_ok;
}

#endif

parser_error_t _readMethod_V1(
    parser_context_t* c,
    uint8_t moduleIdx,
    uint8_t callIdx,
    pd_Method_V1_t* method)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 0x0500: /* module 5 call 0 */
        CHECK_ERROR(_readMethod_balances_transfer_V1(c, &method->nested.balances_transfer_V1))
        break;
    case 0x0502: /* module 5 call 2 */
        CHECK_ERROR(_readMethod_balances_force_transfer_V1(c, &method->nested.balances_force_transfer_V1))
        break;
    case 0x0503: /* module 5 call 3 */
        CHECK_ERROR(_readMethod_balances_transfer_keep_alive_V1(c, &method->nested.balances_transfer_keep_alive_V1))
        break;
    case 0x0504: /* module 5 call 4 */
        CHECK_ERROR(_readMethod_balances_transfer_all_V1(c, &method->basic.balances_transfer_all_V1))
        break;
    
    case 0x0802: /* module 8 call 2 */
        CHECK_ERROR(_readMethod_paratensor_add_stake_V1(c, &method->nested.paratensor_add_stake_V1))
        break;
    case 0x0803: /* module 8 call 3 */
        CHECK_ERROR(_readMethod_paratensor_remove_stake_V1(c, &method->nested.paratensor_remove_stake_V1))
        break;
    
#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif

    case 0x0002: // Module 0, Call 2
        CHECK_ERROR(_readMethod_system_set_code_V1(c, &method->nested.system_set_code_V1))
        break;

    case 0x0700: // Module 7, Call 0
        CHECK_ERROR(_readMethod_sudo_sudo_V1(c, &method->basic.sudo_sudo_V1))
        break;
    case 0x0702:  // Module 7, Call 2
        CHECK_ERROR(_readMethod_sudo_set_key_V1(c, &method->nested.sudo_set_key_V1))
        break;

    case 0x0809: /* module 8 call 9 */
        CHECK_ERROR(_readMethod_paratensor_sudo_add_network_V1(c, &method->nested.paratensor_sudo_add_network_V1))
        break;

    case 0x0501: /* module 5 call 2 */
        CHECK_ERROR(_readMethod_balances_set_balance_V1(c, &method->nested.balances_set_balance_V1))
        break;
    case 0x0505: /* module 5 call 5 */
        CHECK_ERROR(_readMethod_balances_force_unreserve_V1(c, &method->basic.balances_force_unreserve_V1))
        break;
#endif
    default:
        return parser_unexpected_callIndex;
    }

    return parser_ok;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

const char* _getMethod_ModuleName_V1(uint8_t moduleIdx)
{
    switch (moduleIdx) {
    case 0x05:
        return STR_MO_BALANCES;
    case 0x08:
        return STR_MO_PARATENSOR;
#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif
    case 0x00:
        return STR_MO_SYSTEM;
    case 0x07:
        return STR_MO_SUDO;
        
#endif
    default:
        return NULL;
    }

    return NULL;
}

const char* _getMethod_Name_V1(uint8_t moduleIdx, uint8_t callIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 0x0500: /* module 5 call 0 */
        return STR_ME_TRANSFER;
    case 0x0502: /* module 5 call 2 */
        return STR_ME_FORCE_TRANSFER;
    case 0x0503: /* module 5 call 3 */
        return STR_ME_TRANSFER_KEEP_ALIVE;
    case 0x0504: /* module 5 call 4 */
        return STR_ME_TRANSFER_ALL;

    case 0x0802: /* module 8 call 2 */
        return STR_ME_ADD_STAKE;
    case 0x0803: /* module 8 call 3 */
        return STR_ME_REMOVE_STAKE;
    
    default:
        return _getMethod_Name_V1_ParserFull(callPrivIdx);
    }

    return NULL;
}

const char* _getMethod_Name_V1_ParserFull(uint16_t callPrivIdx)
{
    switch (callPrivIdx) {
#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif
    case 0x0002: // Module 0, Call 2
        return STR_ME_SET_CODE;

    case 0x0700: // Module 7, Call 0
        return STR_ME_SUDO;
    case 0x0702:  // Module 7, Call 2
        return STR_ME_SET_KEY;
    
    case 0x0501: /* module 5 call 2 */
        return STR_ME_SET_BALANCE;
    case 0x0505: /* module 5 call 5 */
        return STR_ME_FORCE_UNRESERVE;
    
    case 0x0809: /* module 8 call 9 */
        return STR_ME_SUDO_ADD_NETWORK;

#endif
    default:
        return NULL;
    }

    return NULL;
}

uint8_t _getMethod_NumItems_V1(uint8_t moduleIdx, uint8_t callIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 0x0500: /* module 5 call 0 */
        return 2;
    case 0x0502: /* module 5 call 2 */
        return 3;
    case 0x0503: /* module 5 call 3 */
        return 2;
    case 0x0504: /* module 5 call 4 */
        return 2;
    
    case 0x0802: /* module 8 call 2 */
        return 2;
    case 0x0803: /* module 8 call 3 */
        return 2;

#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif
    case 0x0002: // Module 0, Call 2
        return 1;
    
    case 0x0702: // Module 7, Call 2
        return 1;
    
    case 0x0501: /* module 5 call 2 */
        return 3;
    case 0x0505: /* module 5 call 5 */
        return 2;
    
    case 0x0809: /* module 8 call 9 */
        return 3;
#endif
    default:
        return 0;
    }

    return 0;
}

const char* _getMethod_ItemName_V1(uint8_t moduleIdx, uint8_t callIdx, uint8_t itemIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 0x0500: /* module 5 call 0 */
        switch (itemIdx) {
        case 0:
            return STR_IT_dest;
        case 1:
            return STR_IT_amount;
        default:
            return NULL;
        }
    case 0x0502: /* module 5 call 2 */
        switch (itemIdx) {
        case 0:
            return STR_IT_source;
        case 1:
            return STR_IT_dest;
        case 2:
            return STR_IT_amount;
        default:
            return NULL;
        }
    case 0x0503: /* module 5 call 3 */
        switch (itemIdx) {
        case 0:
            return STR_IT_dest;
        case 1:
            return STR_IT_amount;
        default:
            return NULL;
        }
    case 0x0504: /* module 5 call 4 */
        switch (itemIdx) {
        case 0:
            return STR_IT_dest;
        case 1:
            return STR_IT_keep_alive;
        default:
            return NULL;
        }

    case 0x0802: /* module 8 call 2 */
        switch (itemIdx) {
        case 0:
            return STR_IT_hotkey;
        case 1:
            return STR_IT_amount_staked;
        default:
            return NULL;
        }
    case 0x0803: /* module 8 call 3 */
        switch (itemIdx) {
        case 0:
            return STR_IT_hotkey;
        case 1:
            return STR_IT_amount_unstaked;
        default:
            return NULL;
        }
#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif
    case 0x0002: // Module 0, Call 2
        switch (itemIdx) {
        case 0:
            return STR_IT_code;
        default:
            return NULL;
        }

    case 0x0702: // Module 7, Call 2
        switch (itemIdx) {
        case 0:
            return STR_IT_new;
        default:
            return NULL;
        }

    case 0x0501: /* module 5 call 2 */
        switch (itemIdx) {
        case 0:
            return STR_IT_who;
        case 1:
            return STR_IT_new_free;
        case 2:
            return STR_IT_new_reserved;
        default:
            return NULL;
        }
    case 0x0505: /* module 5 call 5 */
        switch (itemIdx) {
        case 0:
            return STR_IT_who;
        case 1:
            return STR_IT_amount;
        default:
            return NULL;
        }

    case 0x0809: /* module 8 call 9 */
        switch (itemIdx) {
        case 0:
            return STR_IT_netuid;
        case 1:
            return STR_IT_tempo;
        case 2:
            return STR_IT_modality;
        default:
            return NULL;
        }
#endif
    default:
        return NULL;
    }

    return NULL;
}

parser_error_t _getMethod_ItemValue_V1(
    pd_Method_V1_t* m,
    uint8_t moduleIdx, uint8_t callIdx, uint8_t itemIdx,
    char* outValue, uint16_t outValueLen,
    uint8_t pageIdx, uint8_t* pageCount)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 0x0500: /* module 5 call 0 */
        switch (itemIdx) {
        case 0: /* balances_transfer_V1 - dest */;
            return _toStringLookupasStaticLookupSource_V1(
                &m->nested.balances_transfer_V1.dest,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* balances_transfer_V1 - amount */;
            return _toStringCompactBalance(
                &m->nested.balances_transfer_V1.amount,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
    case 0x0502: /* module 5 call 2 */
        switch (itemIdx) {
        case 0: /* balances_force_transfer_V1 - source */;
            return _toStringLookupasStaticLookupSource_V1(
                &m->nested.balances_force_transfer_V1.source,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* balances_force_transfer_V1 - dest */;
            return _toStringLookupasStaticLookupSource_V1(
                &m->nested.balances_force_transfer_V1.dest,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 2: /* balances_force_transfer_V1 - amount */;
            return _toStringCompactBalance(
                &m->nested.balances_force_transfer_V1.amount,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
    case 0x0503: /* module 5 call 3 */
        switch (itemIdx) {
        case 0: /* balances_transfer_keep_alive_V1 - dest */;
            return _toStringLookupasStaticLookupSource_V1(
                &m->nested.balances_transfer_keep_alive_V1.dest,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* balances_transfer_keep_alive_V1 - amount */;
            return _toStringCompactBalance(
                &m->nested.balances_transfer_keep_alive_V1.amount,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
    case 0x0504: /* module 5 call 4 */
        switch (itemIdx) {
        case 0: /* balances_transfer_all_V1 - dest */;
            return _toStringLookupasStaticLookupSource_V1(
                &m->basic.balances_transfer_all_V1.dest,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* balances_transfer_all_V1 - keep_alive */;
            return _toStringbool(
                &m->basic.balances_transfer_all_V1.keep_alive,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
    
    case 0x0802: /* module 8 call 2 */
        switch (itemIdx) {
        case 0: /* paratensor_add_stake_V1 - hotkey */;
            return _toStringStakingAddress32_V1(
                &m->nested.paratensor_add_stake_V1.hotkey,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* paratensor_add_stake_V1 - amount_staked */;
            return _toStringBalance(
                &m->nested.paratensor_add_stake_V1.amount_staked,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
    case 0x0803: /* module 8 call 3 */
        switch (itemIdx) {
        case 0: /* paratensor_remove_stake_V1 - hotkey */;
            return _toStringStakingAddress32_V1(
                &m->nested.paratensor_remove_stake_V1.hotkey,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* paratensor_remove_stake_V1 - amount_unstaked */;
            return _toStringBalance(
                &m->nested.paratensor_remove_stake_V1.amount_unstaked,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
    
#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif
    case 0x0002: // Module 0, Call 0
        switch (itemIdx) {
        case 0: /* system_set_code_V1 - code */;
            return _toStringCodeBytes_V1 (
                &m->nested.system_set_code_V1.code,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }

    case 0x0702: // Module 7, Call 2
        switch (itemIdx) {
        case 0: /* sudo_set_key_V1 - new */;
            return _toStringLookupasStaticLookupSource_V1(
                &m->nested.sudo_set_key_V1.new_,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
    
    case 0x0501: /* module 5 call 2 */
        switch (itemIdx) {
        case 0: /* balances_set_balance_V1 - who */;
            return _toStringLookupasStaticLookupSource_V1(
                &m->nested.balances_set_balance_V1.who,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* balances_set_balance_V1 - new_free */;
            return _toStringCompactBalance(
                &m->nested.balances_set_balance_V1.new_free,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 2: /* balances_set_balance_V1 - new_reserved */;
            return _toStringCompactBalance(
                &m->nested.balances_set_balance_V1.new_reserved,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
    case 0x0505: /* module 5 call 5 */
        switch (itemIdx) {
        case 0: /* balances_force_unreserve_V1 - who */;
            return _toStringLookupasStaticLookupSource_V1(
                &m->basic.balances_force_unreserve_V1.who,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* balances_force_unreserve_V1 - amount */;
            return _toStringBalance(
                &m->basic.balances_force_unreserve_V1.amount,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }

    case 0x0809: /* module 8 call 9 */
        switch (itemIdx) {
        case 0: /* paratensor_sudo_add_network_V1 - netuid */;
            return _toStringu16(
                &m->nested.paratensor_sudo_add_network_V1.netuid,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* paratensor_sudo_add_network_V1 - tempo */;
            return _toStringu16(
                &m->nested.paratensor_sudo_add_network_V1.tempo,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 2: /* paratensor_sudo_add_network_V1 - modality */;
            return _toStringu16(
                &m->nested.paratensor_sudo_add_network_V1.modality,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
#endif
    default:
        return parser_ok;
    }

    return parser_ok;
}

bool _getMethod_ItemIsExpert_V1(uint8_t moduleIdx, uint8_t callIdx, uint8_t itemIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {

    default:
        return false;
    }
}

bool _getMethod_IsNestingSupported_V1(uint8_t moduleIdx, uint8_t callIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 0x0700: // Sudo:Sudo
    case 0x0504: // Balances:Transfer all
    case 0x0505: // Balances:Force unreserve
        return false;
    default:
        return true;
    }
}
