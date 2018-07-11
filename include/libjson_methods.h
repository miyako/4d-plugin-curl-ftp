#include "4DPluginAPI.h"
#include "libjson.h"

#if defined(__APPLE__)
#define DATE_FORMAT_ISO @"yyyy-MM-dd'T'HH:mm:ss"
#define DATE_FORMAT_ISO_GMT @"yyyy-MM-dd'T'HH:mm:ss'Z'"
#endif

/* utf-32 to utf-16 */
void json_wconv(const wchar_t *value, CUTF16String *u16);
/* utf-32 to utf-8 */
void json_wconv(const wchar_t *value, CUTF8String *u8);
/* utf-8 to utf-16 to utf-32 */
void json_wconv(const char *value, std::wstring &u32);


void json_push_back_s(JSONNODE *n, const char *value);
void json_set_s(JSONNODE *n, const char *value);
void json_set_s_for_key(JSONNODE *n, json_char *key, const char *value);
void json_set_b_for_key(JSONNODE *n, json_char *key, json_bool_t value);
void json_set_i_for_key(JSONNODE *n, json_char *key, json_int_t value);


/* utf32 to utf16 */
void json_stringify(JSONNODE *json, CUTF16String &t, BOOL pretty);
