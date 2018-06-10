#ifndef SPONGENT_CONFIG_H
#define SPONGENT_CONFIG_H

/**
 * The number of bits security offered by the crypto functions
 */
#define SPONGENT_SECURITY 64

/**
 * The size of the keys used by the crypto functions: (SPONGENT_SECURITY / 8)
 *
 * NOTE: need to hard-define here, for sgx_edger8r cannot expand static
 *       artithmetic operations. We rely on a static assertion in spongent.h to
 *       ensure correctness.
 */
#define SPONGENT_KEY_SIZE 8

/**
 * The size of the tags used and produces by the crypto functions.
 */
#define SPONGENT_TAG_SIZE SPONGENT_KEY_SIZE

#define SW_SECURITY SPONGENT_SECURITY


#define debug_printf(msg, ...)                                          \
    do {                                                                \
    } while(0)

#endif

