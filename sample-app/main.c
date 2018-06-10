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

#include <stdio.h>
#include <stdint.h>
#include <sgx_urts.h>
#include "Enclave/encl_u.h"

#include "../libspongent/config.h" //XXX

#define ASSERT(cond)                                                    \
    do {                                                                \
        if (!(cond))                                                    \
        {                                                               \
            perror("[" __FILE__ "] assertion '" #cond "' failed");      \
            abort();                                                    \
        }                                                               \
    } while(0)

#define SGX_ASSERT(f)  { if ( SGX_SUCCESS != (enclave_rv = (f)) )       \
 {                                                                      \
       printf( "Error calling enclave at %s:%d (rv=0x%x)\n", __FILE__,  \
                                              __LINE__, enclave_rv);    \
        abort();                                                        \
 } }

int enclave_rv = 0;

void dump_hex(char *str, uint8_t *buf, int len)
{
    printf("%s = ", str);
    for (int i=0; i < len; i++)
        printf("%02x ", *(buf + i));
    printf("\n");
}

char *msg = "hello, world!";
uint8_t *cipher, *plain;
uint8_t tag[SPONGENT_TAG_SIZE] = {0x0};
uint8_t mac[SPONGENT_TAG_SIZE] = {0x0};

int main( int argc, char **argv )
{
	sgx_launch_token_t token = {0};
	int updated = 0, rv = 0, msg_len = 0;
    sgx_enclave_id_t eid = 0;

   	printf("Creating enclave...\n");
	SGX_ASSERT( sgx_create_enclave( "./Enclave/encl.so", /*debug=*/1,
                                    &token, &updated, &eid, NULL ) );

    printf("calling enclave..\n");

    msg_len = strlen(msg);
    cipher  = malloc(msg_len);
    plain   = malloc(msg_len);
    memset(cipher, 0x0, msg_len);
    memset(plain, 0x0, msg_len);

    SGX_ASSERT( ecall_wrap(eid, &rv, msg, msg_len, NULL, 0, cipher, tag) );
    ASSERT(!rv && "wrap failed");
    dump_hex("MSG   ", msg, msg_len);
    dump_hex("CIPHER", cipher, msg_len);
    dump_hex("TAG   ", tag, SPONGENT_TAG_SIZE);

    SGX_ASSERT( ecall_unwrap(eid, &rv, cipher, msg_len, NULL, 0, plain, tag) );
    ASSERT(!rv && "unwrap failed");
    dump_hex("PLAIN ", plain, msg_len);

    SGX_ASSERT( ecall_mac(eid, &rv, msg, msg_len, mac) );
    ASSERT(!rv && "mac failed");
    dump_hex("MAC   ", mac, SPONGENT_TAG_SIZE);

    printf("destroying enclave..\n");
   	SGX_ASSERT( sgx_destroy_enclave( eid ) );
    free(cipher);

    printf("all is well; exiting..\n");
	return 0;
}
