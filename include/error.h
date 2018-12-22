#pragma once

void errorRegisterAssets();

bool isErrorThrown();

void errorThrow(const char *header, const char *info, const char *data);