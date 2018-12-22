#pragma once

void errorLoadAssets();

bool isErrorThrown();

void errorThrow(const char *header, const char *info, const char *data);

void errorDestroyAssets();