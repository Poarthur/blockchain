#pragma once

class Header final
{
    static constexpr unsigned sha256_size = 8;
public:
    using sha256 = int32_t[sha256_size];
public:
    Header(){}
private:
    int32_t _vesion = 0;
    sha256 a;
};