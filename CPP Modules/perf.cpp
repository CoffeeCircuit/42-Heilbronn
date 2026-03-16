#include <iostream>
#include <chrono>
#include <thread>

bool has_invariant_tsc() {
    unsigned int eax, ebx, ecx, edx;
    eax = 0x80000007;
    __asm__ __volatile__(
        "cpuid"
        : "=d"(edx)
        : "a"(eax)
        : "ebx", "ecx"
    );
    return (edx & (1 << 8)); // Bit 8: Invariant TSC
}

uint64_t read_tsc() {
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

int main() {
    std::cout << "Invariant TSC: " << (has_invariant_tsc() ? "Yes" : "No") << std::endl;

    // Estimate TSC frequency
    uint64_t tsc1 = read_tsc();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    uint64_t tsc2 = read_tsc();
    std::cout << "Estimated TSC frequency: " << (tsc2 - tsc1)/1e9 << "GHz" << std::endl;
    return 0;
}
