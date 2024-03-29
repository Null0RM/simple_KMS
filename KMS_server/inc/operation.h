#ifndef COMMAND_SEND_H
# define COMMAND_SEND_H

#  include "openssl_utils.h"
#  include "common.h"
#  ifndef MQ_H
#   include "mq.h"
#  endif

/* ___MACROS_START___ */
/* __define_start__*/

#  define COMMAND_SUCCESS 1
#  define COMMAND_FAILURE 0

#  define OPERATION_FAILURE 0x00000099

#  ifndef BUFFER_SIZE
#   define BUFFER_SIZE 1024
#  endif

// operations
#  define OPERATION_CREATEKEY 0x00000001 //by KMIP enumeration
#  define OPERATION_ENCRYPT 0x0000001f //by KMIP enumeration
#  define OPERATION_DECRYPT 0x00000020 //by KMIP enumeration
// is_MAC
#  define ISMAC_NONE 0x00000001 // 임의 지정
#  define ISMAC_HMAC 0x00000002 // 임의 지정
#  define ISMAC_CMAC 0x00000003 // 임의 지정
// algo
#  define ALGO_AES128 0x00000001 // AES와 128이 따로라서 임의지정
#  define ALGO_AES256 0x00000002 // AES와 256이 따로라서 임의지정
#  define ALGO_SHA_256 0x00000006 //by KMIP enumeration
#  define ALGO_SHA3_256 0x0000000f //by KMIP enumeration
// mode
#  define MODE_NONE 0x00000000 // 임의 지정
#  define MODE_CBC 0x00000001 //by KMIP enumeration
#  define MODE_CTR 0x00000006 //by KMIP enumeration
// data or text
#  define INPUTTYPE_FILE 0x00000001 // 임의지정
#  define INPUTTYPE_TEXT 0x00000002 // 임의지정
//types
#  define TYPE_ISMAC 0x0001
#  define TYPE_ALGO 0x0002
#  define TYPE_MODE 0x0003
#  define TYPE_KEY 0x0004
#  define TYPE_IV 0x0005
#  define TYPE_INPUT_TYPE 0x0006
#  define TYPE_INPUT_DATA 0x0007
/* __define_end__*/
/* __typedef_start__*/

typedef struct s_operation
{
    long    operation_type; // createkey, encryption, decryption
    int     operation_len; // size of operation_buf
    void    *operation_buf; // t_createKey, t_decryption, t_encryption
} t_operation;

typedef struct s_createKey
{
    int createKey_isMAC; // encdeckey, hmac, cmac
    int createKey_algo; // aes128, aes256, sha-256, sha3-256; 
    int createKey_mode; // NULL, CBC, CTR
} t_createKey;

typedef struct s_enc_dec
{
    int enc_dec_isMAC; // encdeckey, (hmac, cmac)
    int enc_dec_algo;  // aes128, aes256, (sha-256, sha3-256);
    int enc_dec_mode;  // NULL, CBC, CTR
    uint8_t *key;      // algo에 따라 malloc 후 입력받아서 전송
    uint8_t *iv;       // algo에 따라 malloc 후 입력받아서 전송
    int key_len;
    uint8_t *input_data; // if(file): path, if(text): plain
    int data_len;
} t_enc_dec;


/* __typedef_end__*/
/* ___MACROS_END___ */
/* *************************************************************************************************** */

/* *************************************************************************************************** */
/* ___FUNCTION_DEFINE_START___ */


void storeLE32(uint8_t *buffer, uint32_t value);
void storeLE16(uint8_t *buffer, uint16_t value);
void    *mq_recv(key_t key, int *flag);
void    *deserialize_tlv(uint8_t *oper, int oper_len, int oper_type);
uint8_t *do_op(t_operation *struct_oper, int flag, int *len);
t_keys  get_session_key(void);

/* ___FUNCTION_DEFINE_END___ */
/* *************************************************************************************************** */

#endif
