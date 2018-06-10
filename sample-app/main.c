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
#include <sgx_urts.h>
#include "Enclave/encl_u.h"

#define SGX_ASSERT(f)  { if ( SGX_SUCCESS != (enclave_rv = (f)) )       \
 {                                                                      \
       printf( "Error calling enclave at %s:%d (rv=0x%x)\n", __FILE__,  \
                                              __LINE__, enclave_rv);    \
        abort();                                                        \
 } }

int enclave_rv = 0;

int main( int argc, char **argv )
{
	sgx_launch_token_t token = {0};
	int updated = 0, rv = 0;
    sgx_enclave_id_t eid = 0;

   	printf("Creating enclave...\n");
	SGX_ASSERT( sgx_create_enclave( "./Enclave/encl.so", /*debug=*/1,
                                    &token, &updated, &eid, NULL ) );

    printf("calling enclave..\n");
    SGX_ASSERT( enclave_dummy_call(eid, &rv) );

    printf("returned %d; destroying enclave..\n", rv);
   	SGX_ASSERT( sgx_destroy_enclave( eid ) );

    printf("all is well; exiting..\n");
	return 0;
}
