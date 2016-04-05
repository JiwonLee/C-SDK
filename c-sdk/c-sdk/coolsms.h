#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

typedef enum { false, true; } bool;

int curlProcess(bool, char *, char *, response_struct *);