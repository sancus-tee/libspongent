/*
 *  This file is part of the SGX-Step enclave execution control framework.
 *
 *  Copyright (C) 2017 Jo Van Bulck <jo.vanbulck@cs.kuleuven.be>,
 *                     Raoul Strackx <raoul.strackx@cs.kuleuven.be>
 *
 *  SGX-Step is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SGX-Step is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SGX-Step. If not, see <http://www.gnu.org/licenses/>.
 */

#include "libspongent/spongewrap.h"
#include <stdint.h>

uint64_t key = 0xdeadbeefcafebabe;
uint8_t mac[SPONGENT_TAG_SIZE] = {0x0};

int ecall_wrap(void *body, int body_len, void *ad, int ad_len, void *cipher, void *tag)
{
    return spongent_wrap(&key, ad, ad_len, body, body_len, cipher, tag);
}

int ecall_unwrap(void *cipher, int cipher_len, void *ad, int ad_len, void *body, void *expected_tag)
{
    return spongent_unwrap(&key, ad, ad_len, cipher, cipher_len, body, expected_tag);
}

int ecall_mac(void *msg, int msg_len, void *mac)
{
    return spongent_mac(&key, msg, msg_len, mac);
}
