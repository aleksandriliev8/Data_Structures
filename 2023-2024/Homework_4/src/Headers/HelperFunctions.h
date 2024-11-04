#pragma once

bool hasNoSybols(std::string line) {
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] != ' ' && line[i] != '\n') {
            return false;
        }
    }

    return true;
}