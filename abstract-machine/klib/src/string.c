#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  // panic("Not implemented");
  size_t cnt = 0;
  while (*s != 0) {
    ++s;
    ++cnt;
  }
  return cnt;
}

char *strcpy(char *dst, const char *src) {
  // panic("Not implemented");
  char* res = dst;
  while (src) {
    *dst++ = *src++;
  }
  *dst = 0;
  return res;
}

char *strncpy(char *dst, const char *src, size_t n) {
  // panic("Not implemented");
  size_t len = 0;
	while(src[len] && len < n) {
		dst[len] = src[len];
		++len;
	}

	while(len < n) { dst[len++] = 0; }
	return dst;
}

char *strcat(char *dst, const char *src) {
  panic("Not implemented");
}

int strcmp(const char *s1, const char *s2) {
  // panic("Not implemented");
  while (*s1 || *s2) {
		if(*s1 < *s2) { return -1; }
		else if(*s1 > *s2) { return 1; }
    ++s1;
    ++s2;
	}
	return 0;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  // panic("Not implemented");
  for(size_t i = 0; i != n; ++i) {
		if(*s1 < *s2) { return -1; }
		else if(*s1 > *s2) { return 1; }
    ++s1;
    ++s2;
	}
	return 0;
}

void *memset(void *s, int c, size_t n) {
  // panic("Not implemented");
  for (size_t i = 0; i < n; ++i) {
    *(char*)(s + i) = (char)c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  // panic("Not implemented");
  void* tmp = malloc(n);
  memcpy(tmp, src, n);
  memcpy(dst, tmp, n);
  free(tmp);
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  // panic("Not implemented");
  for (size_t i = 0; i < n; ++i) {
    *(char*)(out + i) = *(char*)(in + i);
  }
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  // panic("Not implemented");
  for(size_t i = 0; i != n; ++i) {
		if(*(const unsigned char*)s1 < *(const unsigned char*)s2) { return -1; }
		else if(*(const unsigned char*)s1 > *(const unsigned char*)s2) { return 1; }
    ++s1;
    ++s2;
	}
	return 0;
}

#endif
