#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#define CURL_STATICLIB
#include <curl/curl.h>
#include "csmd5.h"

typedef struct { char *api_key, *api_secret, *salt, *signature, *user_agent, *timestamp; } user_opt;
typedef struct { char *memory; size_t size; } response_struct;

int curlProcess(bool, char *, char *, response_struct *);

user_opt user_opt_init(char *, char *);
static size_t WriteMemoryCallback(void *, size_t, size_t, void *);

char* getOS(char*);
char* getBrowser(char*);
void getTimestamp(char*);
char* getUniq();
void getSignature(const char*, const char *, const char *, char *);