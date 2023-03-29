/*******************************************************************************
*  (c) 2023 Opentensor Technologies 
*  (c) 2019 Zondax GmbH
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

#include <zxmacros.h>
#include <zxformat.h>
#include "parser_impl.h"
#include "parser_txdef.h"
#include "coin.h"
#include "crypto_helper.h"
#include "bignum.h"
#include "substrate_types.h"
#include "substrate_dispatch.h"

extern uint16_t __address_type;

parser_error_t _readTx(parser_context_t *c, parser_tx_t *v) {
    CHECK_INPUT()

    // Reverse parse to retrieve spec before forward parsing
    CHECK_ERROR(_checkVersions(c))

    // Now forward parse
    CHECK_ERROR(_readCallIndex(c, &v->callIndex))
    #ifdef SUBSTRATE_PARSER_FULL
    // If call index is sudo, then we need to read the call index again
    v->isSudo = false; // Reset sudo flag
    if (v->callIndex.moduleIdx == PD_CALL_SUDO_V1) {
        // Set sudo flag
        v->isSudo = true;
        if (v->callIndex.idx == PD_CALL_SUDO_SUDO_V1 ) {
            // Read call index again to get the actual call
            CHECK_ERROR(_readCallIndex(c, &v->callIndex))
        }
        // Otherwise we have a sudo call that is not sudo.sudo
    } 
    #endif

    CHECK_ERROR(_readMethod(c, v->callIndex.moduleIdx, v->callIndex.idx, &v->method))
    CHECK_ERROR(_readEra(c, &v->era))
    CHECK_ERROR(_readCompactIndex(c, &v->nonce))
    CHECK_ERROR(_readCompactBalance(c, &v->tip))
    CHECK_ERROR(_readUInt32(c, &v->specVersion))
    CHECK_ERROR(_readUInt32(c, &v->transactionVersion))
    CHECK_ERROR(_readHash(c, &v->genesisHash))
    CHECK_ERROR(_readHash(c, &v->blockHash))

    if (c->offset < c->bufferLen) {
        return parser_unexpected_unparsed_bytes;
    }

    if (c->offset > c->bufferLen) {
        return parser_unexpected_buffer_end;
    }

    __address_type = _detectAddressType(c);

    return parser_ok;
}
