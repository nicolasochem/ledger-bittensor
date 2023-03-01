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
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Modules names
static const char* STR_MO_SUDO = "Sudo";

static const char* STR_MO_BALANCES = "Balances";

static const char* STR_MO_SYSTEM = "System";

static const char* STR_MO_PARATENSOR = "Paratensor";

// Methods names
// === Sudo ===
static const char* STR_ME_SUDO = "Sudo";
static const char* STR_ME_SET_KEY = "Set key";

// === Balances ===
static const char* STR_ME_TRANSFER = "Transfer";
static const char* STR_ME_SET_BALANCE = "Set balance";
static const char* STR_ME_FORCE_TRANSFER = "Force transfer";
static const char* STR_ME_TRANSFER_KEEP_ALIVE = "Transfer keep alive";
static const char* STR_ME_TRANSFER_ALL = "Transfer all";
static const char* STR_ME_FORCE_UNRESERVE = "Force unreserve";

// === System ===
static const char* STR_ME_SET_CODE = "Set code";

// === Paratensor ===
static const char* STR_ME_ADD_STAKE = "Add stake";
static const char* STR_ME_REMOVE_STAKE = "Remove stake";
static const char* STR_ME_SUDO_ADD_NETWORK = "Add network";

// Items names
static const char* STR_IT_new = "New";
static const char* STR_IT_dest = "Dest";
static const char* STR_IT_amount = "Amount";
static const char* STR_IT_who = "Who";
static const char* STR_IT_new_free = "New free";
static const char* STR_IT_new_reserved = "New reserved";
static const char* STR_IT_source = "Source";
static const char* STR_IT_keep_alive = "Keep alive";

static const char* STR_IT_hotkey = "Hotkey";
static const char* STR_IT_amount_staked = "Amount staked";
static const char* STR_IT_amount_unstaked = "Amount unstaked";

static const char* STR_IT_netuid = "Net UID";
static const char* STR_IT_tempo = "Tempo";
static const char* STR_IT_modality = "Modality";

static const char* STR_IT_code = "Code";

#ifdef __cplusplus
}
#endif
