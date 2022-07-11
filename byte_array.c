#include "byte_array.h"

#include <string.h>

#define malloc pvPortMalloc
#define free vPortFree

static void byte_array_grow_capacity(byte_array_t *ba, size_t size) {
    if (ba->capacity < size) {
        while (ba->capacity < size) ba->capacity *= 2;
        void *data = malloc(ba->capacity);
        memcpy(data, ba->data, ba->size);
        free(ba->data);
        ba->data = data;
    }
}

byte_array_t *byte_array_new_with_size(size_t size) {
    byte_array_t *ba = malloc(sizeof(*ba));

    ba->capacity = size;
    ba->data = malloc(ba->capacity);
    ba->size = 0;

    return ba;
}

inline byte_array_t *byte_array_new_from_chars(const char *chars, size_t size) {
    byte_array_t *ba = byte_array_new_with_size(size);

    byte_array_push_back_chars(ba, chars, size);

    return ba;
}

inline byte_array_t *byte_array_new_from_string(const char *string) {
    return byte_array_new_from_chars(string, strlen(string));
}

byte_array_t *byte_array_new_from_byte_array(byte_array_t *other, int index, int size) {
    byte_array_t *ba = byte_array_new_with_size(size);
    
    byte_array_push_back_chars(other, other->data + index, size);
    
    return ba;
}

inline byte_array_t *byte_array_new() {
    return byte_array_new_with_size(11);
}

inline void byte_array_delete(byte_array_t *ba) {
    free(ba->data);
    free(ba);
}

inline int byte_array_is_empty(byte_array_t *ba) {
    return ba->size == 0;
}

void byte_array_insert_chars(byte_array_t *ba, int index, const char *chars, size_t size) {
    byte_array_grow_capacity(ba, ba->size + size);
    memmove(ba->data + index + size, ba->data + index, (ba->size - index) * sizeof(char));
    memcpy(ba->data + index, chars, size);
    ba->size += size;
}

void byte_array_insert_char(byte_array_t *ba, int index, char ch) {
    byte_array_insert_chars(ba, index, &ch, sizeof(ch));
}

inline void byte_array_push_back_same_chars(byte_array_t *ba, const char *chars, size_t size, size_t count) {
    byte_array_grow_capacity(ba, ba->size + size * count);
    for (int i = 0; i < count; ++i) byte_array_insert_chars(ba, ba->size, chars, size);
}

inline void byte_array_push_back_same_char(byte_array_t *ba, char ch, size_t count) {
    byte_array_push_back_same_chars(ba, &ch, sizeof(ch), count);
}

inline void byte_array_push_back_same_string(byte_array_t *ba, const char *string, size_t count) {
    byte_array_push_back_same_chars(ba, string, strlen(string), count);
}

inline void byte_array_push_back_same_byte_array(byte_array_t *ba, byte_array_t *other, size_t count) {
    byte_array_push_back_same_chars(ba, other->data, other->size, count);
}

inline void byte_array_push_front_same_chars(byte_array_t *ba, const char *chars, size_t size, size_t count) {
    byte_array_grow_capacity(ba, ba->size + size * count);
    for (int i = 0; i < count; ++i) byte_array_insert_chars(ba, 0, chars, size);
}

inline void byte_array_push_front_same_char(byte_array_t *ba, char ch, size_t count) {
    byte_array_push_front_same_chars(ba, &ch, sizeof(ch), count);
}

inline void byte_array_push_front_same_string(byte_array_t *ba, const char *string, size_t count) {
    byte_array_push_front_same_chars(ba, string, strlen(string), count);
}

inline void byte_array_push_front_same_byte_array(byte_array_t *ba, byte_array_t *other, size_t count) {
    byte_array_push_front_same_chars(ba, other->data, other->size, count);
}

inline void byte_array_push_back_char(byte_array_t *ba, char ch) {
    byte_array_insert_chars(ba, ba->size, &ch, sizeof(ch));
}

inline void byte_array_push_back_chars(byte_array_t *ba, const char *chars, size_t size) {
    byte_array_insert_chars(ba, ba->size, chars, size);
}

inline void byte_array_push_back_string(byte_array_t *ba, const char *string) {
    byte_array_insert_chars(ba, ba->size, string, strlen(string));
}

inline void byte_array_push_back_byte_array(byte_array_t *ba, byte_array_t *other) {
    byte_array_insert_chars(ba, ba->size, other->data, other->size);
}

inline void byte_array_push_front_char(byte_array_t *ba, char ch) {
    byte_array_insert_chars(ba, 0, &ch, sizeof(ch));
}

inline void byte_array_push_front_chars(byte_array_t *ba, const char *chars, size_t size) {
    byte_array_insert_chars(ba, 0, chars, size);
}

inline void byte_array_push_front_string(byte_array_t *ba, const char *string) {
    byte_array_insert_chars(ba, 0, string, strlen(string));
}

inline void byte_array_push_front_byte_array(byte_array_t *ba, byte_array_t *other) {
    byte_array_insert_chars(ba, 0, other->data, other->size);
}

inline void byte_array_clear(byte_array_t *ba) {
    ba->size = 0;
}

int byte_array_index_of_char_from_count(byte_array_t *ba, char ch, int from, int count) {
    for (int i = from, found = 0; i < (int)ba->size; ++i) {
        if (ba->data[i] == ch) {
            if (++found == count) return i;
        } else {
            found = 0;
        }
    }

    return -1;
}

int byte_array_index_of_chars_from_count(byte_array_t *ba, const char *chars, size_t size, int from, int count) {
    for (int i = from, found = 0; i <= (int)ba->size - (int)size;) {
        if (!memcmp(ba->data + i, chars, size)) {
            if (++found == count) return i;
            i += size;
        } else {
            ++i;
            found = 0;
        }
    }

    return -1;
}

inline int byte_array_index_of_char_count(byte_array_t *ba, char ch, int count) {
    return byte_array_index_of_char_from_count(ba, ch, 0, count);
}

inline int byte_array_index_of_chars_count(byte_array_t *ba, const char *chars, size_t size, int count) {
    return byte_array_index_of_chars_from_count(ba, chars, size, 0, count);
}

inline int byte_array_index_of_char(byte_array_t *ba, char ch) {
    return byte_array_index_of_char_count(ba, ch, 1);
}

inline int byte_array_index_of_chars(byte_array_t *ba, const char *chars, size_t size) {
    return byte_array_index_of_chars_count(ba, chars, size, 1);
}

inline int byte_array_index_of_string(byte_array_t *ba, const char *string) {
    return byte_array_index_of_chars_count(ba, string, strlen(string), 1);
}

inline int byte_array_index_of_byte_array(byte_array_t *ba, byte_array_t *other) {
    return byte_array_index_of_chars_count(ba, other->data, other->size, 1);
}

void byte_array_remove(byte_array_t *ba, int begin, size_t size) {
    if (begin < ba->size && ba->size >= begin + size) {
        memcpy(ba->data + begin, ba->data + begin + size, ba->size - size);
        ba->size -= size;
    }
}

void byte_array_resize(byte_array_t *ba, size_t size) {
    if (size > ba->size)
        byte_array_grow_capacity(ba, size);
    else if (size < ba->size) {
    }
}

inline void byte_array_fill_char(byte_array_t *ba, char ch, size_t size) {
    for (size_t i = 0; i < size; ++i) ba->data[i] = ch;
}

inline void byte_array_fill_char_full(byte_array_t *ba, char ch) {
    byte_array_fill_char(ba, ch, ba->size);
}

inline char byte_array_first(byte_array_t *ba) {
    return ba->data[0];
}

inline char byte_array_last(byte_array_t *ba) {
    return ba->data[ba->size - 1];
}

inline char *byte_array_begin(byte_array_t *ba) {
    return ba->data;
}

inline char *byte_array_end(byte_array_t *ba) {
    return ba->data + ba->size;
}
