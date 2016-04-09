int main() {
    unsigned int *rand;
    unsigned char ok;

    asm volatile ("rdrand %0; setc %1"
    : "=r" (*rand), "=qm" (ok));

    return 1;
}