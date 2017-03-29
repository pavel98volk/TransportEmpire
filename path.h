#pragma once

#include <cstdint>

class Path
{
public:
    uint32_t segment_id;
    uint32_t quality_level;
    double milage;

public:
    Path();
};

