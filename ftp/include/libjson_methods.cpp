#include "libjson_methods.h"

/* utf-32 to utf-16 */
void json_wconv(const wchar_t *value, CUTF16String *u16)
{
	size_t wlen = wcslen(value);
	
#if VERSIONWIN
	*u16 = CUTF16String((const PA_Unichar *)value, wlen);
#else
	
	 CFStringRef str = CFStringCreateWithBytes(kCFAllocatorDefault, (const UInt8 *)value, wlen*sizeof(wchar_t), kCFStringEncodingUTF32LE, true);
	 if(str)
	 {
		int len = CFStringGetLength(str);
		std::vector<uint8_t> buf((len+1) * sizeof(PA_Unichar));
		CFStringGetCharacters(str, CFRangeMake(0, len), (UniChar *)&buf[0]);
		*u16 = CUTF16String((const PA_Unichar *)&buf[0], len);
		CFRelease(str);
	 }
	
	/*
	 uint32_t dataSize = (uint32_t)((wlen * sizeof(wchar_t))+ sizeof(PA_Unichar));
	 std::vector<char> buf(dataSize);
	 //returns byte size in toString (in this case, need to /2 to get characters)
	 uint32_t len = PA_ConvertCharsetToCharset((char *)value,
	 (PA_long32)(wlen * sizeof(wchar_t)),
	 eVTC_UTF_32,
	 (char *)&buf[0],
	 dataSize,
	 eVTC_UTF_16);
	 *u16 = CUTF16String((const PA_Unichar *)&buf[0], len/sizeof(PA_Unichar));
	 */
	
#endif
}

/* utf-32 to utf-8 */
void json_wconv(const wchar_t *value, CUTF8String *u8)
{
	C_TEXT t;
	size_t wlen = wcslen(value);
#if VERSIONWIN
	t.setUTF16String((const PA_Unichar *)value, wlen);
#else

	/*
	 uint32_t dataSize = (uint32_t)((wlen * sizeof(wchar_t))+ sizeof(PA_Unichar));
	 std::vector<char> buf(dataSize);
	 //returns byte size in toString (in this case, need to /2 to get characters)
	 uint32_t len = PA_ConvertCharsetToCharset((char *)value,
	 (PA_long32)(wlen * sizeof(wchar_t)),
	 eVTC_UTF_32,
	 (char *)&buf[0],
	 dataSize,
	 eVTC_UTF_16);
	 t.setUTF16String((const PA_Unichar *)&buf[0], len/sizeof(PA_Unichar));
	 */

	 CUTF16String u16;
	 json_wconv(value, &u16);
	 t.setUTF16String(&u16);

#endif
	t.copyUTF8String(u8);
}

#include <iostream>

/* utf-8 to utf-16 to utf-32 */
void json_wconv(const char *value, std::wstring &u32)
{
	if((value) && strlen(value))
	{
		C_TEXT t;
		CUTF8String u8 = CUTF8String((const uint8_t *)value);
		
		t.setUTF8String(&u8);
		
#if VERSIONWIN
		u32 = std::wstring((wchar_t *)t.getUTF16StringPtr());
#else
		
		/*
		 uint32_t dataSize = (t.getUTF16Length() * sizeof(wchar_t))+ sizeof(wchar_t);
		 std::vector<char> buf(dataSize);
		 PA_ConvertCharsetToCharset((char *)t.getUTF16StringPtr(),
		 t.getUTF16Length() * sizeof(PA_Unichar),
		 eVTC_UTF_16,
		 (char *)&buf[0],
		 dataSize,
		 eVTC_UTF_32);
		 u32 = std::wstring((wchar_t *)&buf[0]);
		 */

		 CFStringRef str = CFStringCreateWithCharacters(kCFAllocatorDefault, (const UniChar *)t.getUTF16StringPtr(), t.getUTF16Length());
		 if(str)
		 {
			size_t size = CFStringGetMaximumSizeForEncoding(CFStringGetLength(str), kCFStringEncodingUTF32LE) + sizeof(wchar_t);
			std::vector<uint8_t> buf(size);
			CFIndex len = 0;
			CFIndex count = CFStringGetBytes(str, CFRangeMake(0, CFStringGetLength(str)), kCFStringEncodingUTF32LE, 0, true, (UInt8 *)&buf[0], size, &len);
			u32 = std::wstring((wchar_t *)&buf[0], count);
			CFRelease(str);
		 }

#endif
	}else
	{
		u32 = L"";
	}
	
}

void json_push_back_s(JSONNODE *n, const char *value)
{
	if(n)
	{
		if(value)
		{
			std::wstring w32;
			json_wconv(value, w32);
			
			JSONNODE *e = json_new(JSON_STRING);
			json_set_a(e, w32.c_str());
			json_push_back(n, e);
		}else
		{
			JSONNODE *e = json_new(JSON_STRING);
			json_nullify(e);
			json_push_back(n, e);
		}
	}
	
}

void json_set_s(JSONNODE *n, const char *value)
{
	if(n)
	{
		if(value)
		{
			std::wstring w32;
			json_wconv(value, w32);
			json_set_a(n, w32.c_str());
		}else
		{
			json_nullify(n);
		}
	}
}

void json_set_s_for_key(JSONNODE *n, json_char *key, const char *value)
{
	if(n)
	{
		if(value)
		{
			std::wstring w32;
			json_wconv(value, w32);
			
			JSONNODE *e = json_get(n, key);
			if(e)
			{
				json_set_a(e, w32.c_str());//over-write existing value
			}else
			{
				json_push_back(n, json_new_a(key, w32.c_str()));
			}
			
		}else
		{
			JSONNODE *e = json_get(n, key);
			if(e)
			{
				json_nullify(e);//over-write existing value
			}else
			{
				JSONNODE *node = json_new_a(key, L"");
				json_nullify(node);
				json_push_back(n, node);
			}
		}
	}
}

void json_set_b_for_key(JSONNODE *n, json_char *key, json_bool_t value)
{
	if(n)
	{
		JSONNODE *e = json_get(n, key);
		if(e)
		{
			json_set_b(e, value);//over-write existing value
		}else
		{
			json_push_back(n, json_new_b(key, value));
		}
	}
}

void json_set_i_for_key(JSONNODE *n, json_char *key, json_int_t value)
{
	if(n)
	{
		JSONNODE *e = json_get(n, key);
		if(e)
		{
			json_set_i(e, value);//over-write existing value
		}else
		{
			json_push_back(n, json_new_i(key, value));
		}
	}
}

/* utf32 to utf16 */
void json_stringify(JSONNODE *json, CUTF16String &t, BOOL pretty)
{
	json_char *json_string = pretty ? json_write_formatted(json) : json_write(json);
	std::wstring wstr = std::wstring(json_string);
#if VERSIONWIN
	t = CUTF16String((const PA_Unichar *)wstr.c_str(), (uint32_t)wstr.length());
#else
	CFStringRef str = CFStringCreateWithBytes(kCFAllocatorDefault, (const UInt8 *)wstr.c_str(), wstr.size()*sizeof(wchar_t), kCFStringEncodingUTF32LE, true);
	if(str)
	{
		int len = CFStringGetLength(str);
		std::vector<uint8_t> buf((len+1) * sizeof(PA_Unichar));
		CFStringGetCharacters(str, CFRangeMake(0, len), (UniChar *)&buf[0]);
		t = CUTF16String((const PA_Unichar *)&buf[0], len);
		CFRelease(str);
	}
	
	/*
	 uint32_t dataSize = (uint32_t)((wstr.length() * sizeof(wchar_t))+ sizeof(PA_Unichar));
	 std::vector<char> buf(dataSize);
	 //returns byte size in toString (in this case, need to /2 to get characters)
	 uint32_t len = PA_ConvertCharsetToCharset((char *)wstr.c_str(),
	 (PA_long32)(wstr.length() * sizeof(wchar_t)),
	 eVTC_UTF_32,
	 (char *)&buf[0],
	 dataSize,
	 eVTC_UTF_16);
	 t = CUTF16String((const PA_Unichar *)&buf[0], len/sizeof(PA_Unichar));
	 */
	
#endif
	json_free(json_string);
}
