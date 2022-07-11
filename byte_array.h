#ifndef BYTE_ARRAY_H
#define BYTE_ARRAY_H

#include "FreeRTOS.h"

typedef struct {
    char  *data;
    size_t capacity;
    size_t size;
} byte_array_t;

typedef char *byte_array_iterator_t;
char         *byte_array_begin(byte_array_t *ba);
char         *byte_array_end(byte_array_t *ba);

byte_array_t *byte_array_new_with_size(size_t size);
byte_array_t *byte_array_new();
byte_array_t *byte_array_new_from_chars(const char *chars, size_t size);
byte_array_t *byte_array_new_from_string(const char *string);
byte_array_t *byte_array_new_from_byte_array(byte_array_t *other, int index, int size);
void          byte_array_delete(byte_array_t *ba);
int           byte_array_is_empty(byte_array_t *ba);
void          byte_array_clear(byte_array_t *ba);
void          byte_array_insert_char(byte_array_t *ba, int index, char ch);
void          byte_array_insert_chars(byte_array_t *ba, int index, const char *chars, size_t size);
int           byte_array_index_of_char_from_count(byte_array_t *ba, char ch, int from, int count);
int  byte_array_index_of_chars_from_count(byte_array_t *ba, const char *chars, size_t size, int from, int count);
int  byte_array_index_of_char_count(byte_array_t *ba, char ch, int count);
int  byte_array_index_of_chars_count(byte_array_t *ba, const char *chars, size_t size, int count);
int  byte_array_index_of_char(byte_array_t *ba, char ch);
int  byte_array_index_of_chars(byte_array_t *ba, const char *chars, size_t size);
int  byte_array_index_of_string(byte_array_t *ba, const char *string);
int  byte_array_index_of_byte_array(byte_array_t *ba, byte_array_t *other);
void byte_array_remove(byte_array_t *ba, int begin, size_t size);
void byte_array_push_back_char(byte_array_t *ba, char ch);
void byte_array_push_back_chars(byte_array_t *ba, const char *chars, size_t size);
void byte_array_push_back_string(byte_array_t *ba, const char *string);
void byte_array_push_back_byte_array(byte_array_t *ba, byte_array_t *other);
void byte_array_push_front_char(byte_array_t *ba, char ch);
void byte_array_push_front_chars(byte_array_t *ba, const char *chars, size_t size);
void byte_array_push_front_string(byte_array_t *ba, const char *string);
void byte_array_push_front_byte_array(byte_array_t *ba, byte_array_t *other);
void byte_array_fill_char(byte_array_t *ba, char ch, size_t size);
void byte_array_fill_char_full(byte_array_t *ba, char ch);
char byte_array_first(byte_array_t *ba);
char byte_array_last(byte_array_t *ba);
void byte_array_push_back_same_chars(byte_array_t *ba, const char *chars, size_t size, size_t count);
void byte_array_push_back_same_char(byte_array_t *ba, char ch, size_t count);
void byte_array_push_back_same_string(byte_array_t *ba, const char *string, size_t count);
void byte_array_push_back_same_byte_array(byte_array_t *ba, byte_array_t *other, size_t count);
void byte_array_push_front_same_chars(byte_array_t *ba, const char *chars, size_t size, size_t count);
void byte_array_push_front_same_char(byte_array_t *ba, char ch, size_t count);
void byte_array_push_front_same_string(byte_array_t *ba, const char *string, size_t count);
void byte_array_push_front_same_byte_array(byte_array_t *ba, byte_array_t *other, size_t count);
byte_array_t *byte_array_replace_with_char_at(byte_array_t *ba, char ch, size_t pos, size_t len);
byte_array_t *byte_array_replace_with_chars_at(byte_array_t *ba, char *chars, size_t size, size_t pos, size_t len);

#endif // BYTE_ARRAY_H
