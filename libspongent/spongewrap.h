#ifndef SPONGEWRAP_H_INC
#define SPONGEWRAP_H_INC

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Wrap a message using the SPONGEWRAP authenticated encryption.
 *
 * @p body_len bytes of data starting at @p body are wrapped using the key
 * @p key and @p ad_len of associated data starting at @p ad. The resulting
 * cipher text is written to @p cipher (make sure there is a buffer available
 * of at least @p body_len bytes) and the MAC to @p tag (the needed buffer size
 * depends of the amount of SPONGENT security bits.
 *
 * @param key       Optional pointer to input key buffer of SPONGENT_KEY_SIZE
 *                  bytes.
 * @param ad        Required pointer to start of associated data input buffer;
 *                  cannot be NULL.
 * @param ad_len    Length of associated data input buffer.
 * @param body      Optional pointer to input buffer holding the plain text;
                    NULL when only MAC over associated data is required.
 * @param body_len  Length of plain text data input buffer.
 * @param cipher    Optional pointer to output buffer of @p body_len bytes for
 *                  the cipher text; cannot be NULL when @p body is non-zero.
 * @param tag       Required pointer to output buffer of SPONGENT_TAG_SIZE bytes
 *                  for MAC over both associated data and plain text (if any);
 *                  cannot be NULL;
 *
 * @return 0 iff the wrapping succeeded.
 */
int spongent_wrap(   void* key,
                     void* ad, unsigned int ad_len,
                     void* body, unsigned int body_len,
                     void* cipher, void* tag);

int spongent_unwrap( void* key,
                     void* ad, unsigned int ad_len,
                     void* cipher, unsigned int cipher_len,
                     void* body, void* tag);

int spongent_mac(    void* key,
                     void* msg, unsigned int msg_len,
                     void* mac);

#ifdef __cplusplus
}
#endif

#endif
