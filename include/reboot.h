#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void rebootToRCM();

void rebootToPayload(const char *payload);

#ifdef __cplusplus
}
#endif