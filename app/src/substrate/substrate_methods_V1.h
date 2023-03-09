/*******************************************************************************
 *  (c) 2023 Opentensor Technologies 
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
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wextern-c-compat"
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "substrate_types.h"
#include "substrate_types_V1.h"
#include <stddef.h>
#include <stdint.h>
#ifdef LEDGER_SPECIFIC
#include "bolos_target.h"
#endif

#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif

#define PD_CALL_SYSTEM_V1 0

#define PD_CALL_SYSTEM_SET_CODE_V1 2
typedef struct {
    pd_Bytes_t code;
} pd_system_set_code_V1_t;

#define PD_CALL_SUDO_V1 7

#define PD_CALL_SUDO_SUDO_V1 0
typedef struct { // No params
} pd_sudo_sudo_V1_t;

#define PD_CALL_SUDO_SET_KEY_V1 2
typedef struct {
    pd_LookupasStaticLookupSource_V1_t new_;
} pd_sudo_set_key_V1_t;

#endif

#define PD_CALL_BALANCES_V1 5

#define PD_CALL_BALANCES_TRANSFER_ALL_V1 4
typedef struct {
    pd_LookupasStaticLookupSource_V1_t dest;
    pd_bool_t keep_alive;
} pd_balances_transfer_all_V1_t;

#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif

#define PD_CALL_BALANCES_FORCE_UNRESERVE_V1 5
typedef struct {
    pd_LookupasStaticLookupSource_V1_t who;
    pd_Balance_t amount;
} pd_balances_force_unreserve_V1_t;

#endif

typedef union {
    pd_balances_transfer_all_V1_t balances_transfer_all_V1;
#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif
    pd_sudo_sudo_V1_t sudo_sudo_V1;
    pd_balances_force_unreserve_V1_t balances_force_unreserve_V1;
#endif
} pd_MethodBasic_V1_t;

#define PD_CALL_BALANCES_TRANSFER_V1 0
typedef struct {
    pd_LookupasStaticLookupSource_V1_t dest;
    pd_CompactBalance_t amount;
} pd_balances_transfer_V1_t;

#define PD_CALL_BALANCES_FORCE_TRANSFER_V1 2
typedef struct {
    pd_LookupasStaticLookupSource_V1_t source;
    pd_LookupasStaticLookupSource_V1_t dest;
    pd_CompactBalance_t amount;
} pd_balances_force_transfer_V1_t;

#define PD_CALL_BALANCES_TRANSFER_KEEP_ALIVE_V1 3
typedef struct {
    pd_LookupasStaticLookupSource_V1_t dest;
    pd_CompactBalance_t amount;
} pd_balances_transfer_keep_alive_V1_t;

#define PD_CALL_PARATENSOR_V1 8

#define PD_CALL_PARATENSOR_ADD_STAKE_V1 2
typedef struct {
    pd_StakingAddress32_V1_t hotkey;
    pd_Balance_t amount_staked;
} pd_paratensor_add_stake_V1_t;

#define PD_CALL_PARATENSOR_REMOVE_STAKE_V1 3
typedef struct {
    pd_StakingAddress32_V1_t hotkey;
    pd_Balance_t amount_unstaked;
} pd_paratensor_remove_stake_V1_t;

#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif

#define PD_CALL_PARATENSOR_SUDO_ADD_NETWORK 9
typedef struct {
    pd_u16_t netuid;
    pd_u16_t tempo;
    pd_u16_t modality;
} pd_paratensor_sudo_add_network_V1_t;

#define PD_CALL_BALANCES_SET_BALANCE_V1 1
typedef struct {
    pd_LookupasStaticLookupSource_V1_t who;
    pd_CompactBalance_t new_free;
    pd_CompactBalance_t new_reserved;
} pd_balances_set_balance_V1_t;

#endif

typedef union {
    pd_balances_transfer_V1_t balances_transfer_V1;
    pd_balances_transfer_keep_alive_V1_t balances_transfer_keep_alive_V1;
    pd_paratensor_add_stake_V1_t paratensor_add_stake_V1;
    pd_paratensor_remove_stake_V1_t paratensor_remove_stake_V1;
#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif
    pd_system_set_code_V1_t system_set_code_V1;
    pd_sudo_set_key_V1_t sudo_set_key_V1;
    pd_paratensor_sudo_add_network_V1_t paratensor_sudo_add_network_V1;
    pd_balances_force_transfer_V1_t balances_force_transfer_V1;
    pd_balances_set_balance_V1_t balances_set_balance_V1;
#endif
} pd_MethodNested_V1_t;

typedef union {
    pd_MethodBasic_V1_t basic;
    pd_MethodNested_V1_t nested;
} pd_Method_V1_t;

#ifdef __cplusplus
}
#endif

#pragma clang diagnostic pop
