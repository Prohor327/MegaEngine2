#pragma once

#include "Enums.h"

void CheckError(bool success, const Error::ErrorType& type);
void CheckError(int shader, const Error::ErrorType& type);