#include "parse_latency_int.h"

#include <cstdlib>
#include <iostream>
#include <string>

using OHOS::AudioStandard::ParseLatencyU64;

static int g_fail = 0;

static void ExpectTrue(const char *name, bool ok)
{
    if (!ok) {
        std::cerr << "FAIL " << name << "\n";
        ++g_fail;
    }
}

static void ExpectFalse(const char *name, bool ok)
{
    ExpectTrue(name, !ok);
}

static void ExpectEq(const char *name, uint64_t got, uint64_t want)
{
    if (got != want) {
        std::cerr << "FAIL " << name << " got=" << got << " want=" << want << "\n";
        ++g_fail;
    }
}

int main()
{
    uint64_t out = 999;
    ExpectTrue("0", ParseLatencyU64("0", out));
    ExpectEq("0val", out, 0);
    ExpectTrue("123", ParseLatencyU64("123", out));
    ExpectEq("123val", out, 123);
    ExpectTrue("INT_MAX", ParseLatencyU64("2147483647", out));
    ExpectEq("INT_MAXval", out, 2147483647ULL);
    ExpectTrue("beyond_stoi", ParseLatencyU64("2147483648", out));
    ExpectEq("beyond_stoival", out, 2147483648ULL);

    ExpectFalse("empty", ParseLatencyU64("", out));
    ExpectFalse("abc", ParseLatencyU64("abc", out));
    ExpectFalse("12a", ParseLatencyU64("12a", out));
    ExpectFalse("space", ParseLatencyU64(" 12", out));
    ExpectFalse("neg", ParseLatencyU64("-1", out));
    ExpectFalse("huge", ParseLatencyU64("99999999999999999999", out));

    bool threw = false;
    try {
        (void)std::stoi(std::string("2147483648"));
    } catch (...) {
        threw = true;
    }
    ExpectTrue("stoi_overflow_throws", threw);

    if (g_fail != 0) {
        std::cerr << g_fail << " failures\n";
        return 1;
    }
    std::cout << "audio_standard ParseLatencyU64 host test passed\n";
    return 0;
}
