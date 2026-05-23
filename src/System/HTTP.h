#pragma once
#include <HTTPClient.h>
#include "Platform/NString.h"

const char * sendRequest(NString URL, NString method, NString headers[]);