#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/ansi_fp.h"

static int __count_trailing_zerol(unsigned int arg0) {
    int var_r4;
    int var_r5;
    int var_r6;
    int var_r7;
    unsigned int var_r8;

    var_r5 = 0x20;
    var_r8 = 0xFFFF;
    var_r6 = 0x10;
    var_r4 = 0;
    var_r7 = 0x10;
    while (var_r5 != 0) {
        if (!(arg0 & var_r8)) {
            var_r4 += var_r7;
            arg0 >>= var_r7;
            var_r5 -= var_r7;
        } else if (var_r8 == 1) {
            break;
        }
        if (var_r6 > 1) {
            var_r6 /= 2;
        }
        if (var_r8 > 1) {
            var_r8 >>= var_r6;
            var_r7 -= var_r6;
        }
    }
    return var_r4;
}

static inline int __count_trailing_zero(double n){
    if (__LO(n) != 0U) {
        return __count_trailing_zerol(__LO(n));
    } else {
        return 32 + __count_trailing_zerol(__HI(n) | 0x100000);
    }
}

static void __ull2dec(decimal* result, unsigned long long val) {
    result->sign = 0;

    if (val == 0) {
        result->exp = 0;
        result->sig.length = 1;
        result->sig.text[0] = 0;
        return;
    }

    result->sig.length = 0;

    for(; val != 0; val /= 10) {
        result->sig.text[result->sig.length++] = val % 10;
    }

    {
        unsigned char* i = result->sig.text;
        unsigned char* j = result->sig.text + result->sig.length;

        for (; i < --j; ++i) {
            unsigned char t = *i;
            *i = *j;
            *j = t;
        }
    }

    result->exp = result->sig.length - 1;
}

static inline void __dorounddecup(decimal* d, int digits){
    unsigned char* b = d->sig.text;
    unsigned char* i = b + digits - 1;

    while(1){
        if (*i < 9) {
            *i += 1;
            break;
        }
        if (i == b) {
            *i = 1;
            d->exp++;
            break;
        }
        *i-- = 0;
    }
}

static void __timesdec(decimal* result, const decimal* x, const decimal* y) {
    unsigned int accumulator = 0;
    unsigned char mantissa[SIGDIGLEN * 2];
    int i = x->sig.length + y->sig.length - 1;
    unsigned char* pDigit;
    unsigned char* ip = mantissa + i + 1;
    unsigned char* ep = ip;

    result->sign = 0;

    for(; i > 0; i--) {
        int k = y->sig.length - 1;
        int j = i - k - 1;
        int l;
        int t;
        const unsigned char* jp;
        const unsigned char* kp;

        if (j < 0) {
            j = 0;
            k = i - 1;
        }

        jp = x->sig.text + j;
        kp = y->sig.text + k;
        l = k + 1;
        t = x->sig.length - j;

        if (l > t) l = t;

        for (; l > 0; l--, jp++, kp--) {
            accumulator += *jp * *kp;
        }

        *--ip = accumulator % 10;
        accumulator /= 10;
    }

    result->exp = (short)(x->exp + y->exp);

    if (accumulator) {
        *--ip = accumulator;
        result->exp++;
    }

    for (i = 0; i < SIGDIGLEN && ip < ep; i++, ip++) {
        result->sig.text[i] = *ip;
    }
    result->sig.length = i;

    if (ip < ep && *ip >= 5){
        if (*ip == 5){
            unsigned char* jp = ip + 1;
            for (; jp < ep; jp++) {
                if (*jp != 0) goto round;
            }
            if ((ip[-1] & 1) == 0) return;
        }
    round:
        __dorounddecup(result, result->sig.length);
    }
}

static void __str2dec(decimal* d, const signed char* s, short exp) {
    int i;

    d->exp = exp;
    d->sign = 0;

    for (i = 0; i < SIGDIGLEN && *s; ) {
        d->sig.text[i++] = *s++ - '0';
    }
    d->sig.length = i;

    if (*s != 0 && *s >= 5) {
        const signed char* p = s + 1;

        for (; *p != 0; p++) {
            if (*p != '0') goto round;
        }

        if ((d->sig.text[i - 1] & 1) == 0) return;
    round:
        __dorounddecup(d, d->sig.length);
    }
}

// TODO: ideally, these strings should be used as literals in the function below.
// However, the first one (179769313486231580793729011405303420, corresponding to
// 2^1024) is not used in the function and messes up alignment.

const signed char lbl_8011E630[] =
    "179769313486231580793729011405303420\000" \
    "542101086242752217003726400434970855712890625\000" \
    "11102230246251565404236316680908203125\000" \
    "23283064365386962890625\000" \
    "152587890625\000" \
    "390625\000" \
    "78125\000" \
    "15625\000" \
    "3125\000" \
    "625\000" \
    "125\000" \
    "25\000" \
    "5\000" \
    "1\000" \
    "2\000" \
    "4\000" \
    "8\000" \
    "16\000" \
    "32\000" \
    "64\000" \
    "128\000" \
    "256";

static void __two_exp(decimal* result, short exp) {
    decimal sp8C;
    decimal sp60;
    decimal sp34;
    decimal sp8;

    switch (exp) {
        case -64:
            __str2dec(result, lbl_8011E630 + 0x25, -20);
            break;
        case -53:
            __str2dec(result, lbl_8011E630 + 0x53, -16);
            break;
        case -32:
            __str2dec(result, lbl_8011E630 + 0x7A, -10);
            break;
        case -16:
            __str2dec(result, lbl_8011E630 + 0x92, -5);
            break;
        case -8:
            __str2dec(result, lbl_8011E630 + 0x9F, -3);
            break;
        case -7:
            __str2dec(result, lbl_8011E630 + 0xA6, -3);
            break;
        case -6:
            __str2dec(result, lbl_8011E630 + 0xAC, -2);
            break;
        case -5:
            __str2dec(result, lbl_8011E630 + 0xB2, -2);
            break;
        case -4:
            __str2dec(result, lbl_8011E630 + 0xB7, -2);
            break;
        case -3:
            __str2dec(result, lbl_8011E630 + 0xBB, -1);
            break;
        case -2:
            __str2dec(result, lbl_8011E630 + 0xBF, -1);
            break;
        case -1:
            __str2dec(result, lbl_8011E630 + 0xC2, -1);
            break;
        case 0:
            __str2dec(result, lbl_8011E630 + 0xC4, 0);
            break;
        case 1:
            __str2dec(result, lbl_8011E630 + 0xC6, 0);
            break;
        case 2:
            __str2dec(result, lbl_8011E630 + 0xC8, 0);
            break;
        case 3:
            __str2dec(result, lbl_8011E630 + 0xCA, 0);
            break;
        case 4:
            __str2dec(result, lbl_8011E630 + 0xCC, 1);
            break;
        case 5:
            __str2dec(result, lbl_8011E630 + 0xCF, 1);
            break;
        case 6:
            __str2dec(result, lbl_8011E630 + 0xD2, 1);
            break;
        case 7:
            __str2dec(result, lbl_8011E630 + 0xD5, 2);
            break;
        case 8:
            __str2dec(result, lbl_8011E630 + 0xD9, 2);
            break;
        default:
            __two_exp(&sp8C, exp / 2);
            __timesdec(result, &sp8C, &sp8C);
            if (exp & 1) {
                sp60 = *result;
                if (exp > 0) {
                    __str2dec(&sp34, lbl_8011E630 + 0xC6, 0);
                    __timesdec(result, &sp60, &sp34);
                } else {
                    __str2dec(&sp8, lbl_8011E630 + 0xC2, -1);
                    __timesdec(result, &sp60, &sp8);
                }
            }
            break;
    }
}

static void __num2dec_internal(decimal* d, double x) {
    signed char sign = (signbit(x) != 0);

    if (x == 0) {
        d->sign = sign;
        d->exp = 0;
        d->sig.length = 1;
        d->sig.text[0] = 0;
        return;
    }

    if (!isfinite(x)) {
        d->sign = sign;
        d->exp = 0;
        d->sig.length = 1;
        d->sig.text[0] = (fpclassify(x) == 1) ? 'N' : 'I';
        return;
    }

    if (sign != 0) {
        x = -x;
    }

    {
        int exp;
        double frac = frexp(x, &exp);
        short num_bits_extract = DBL_MANT_DIG - __count_trailing_zero(frac);
        decimal int_d, pow2_d;
        double sp30;

        __two_exp(&pow2_d, exp - num_bits_extract);
        modf(ldexp(frac, num_bits_extract), &sp30);
        __ull2dec(&int_d, sp30);
        __timesdec(d, &int_d, &pow2_d);
        d->sign = sign;
    }
}

static inline int __must_round(const decimal* d, int digits){
    unsigned char const* i = d->sig.text + digits;

    if (*i > 5) {
        return 1;
    }

    if (*i < 5) {
        return -1;
    }

    {
        unsigned char const* e = d->sig.text + d->sig.length;

        for(i++; i < e; i++){
            if (*i != 0) {
                return 1;
            }
        }
    }

    if (d->sig.text[digits - 1] & 1) {
        return 1;
    }

    return -1;
}

static inline void __rounddec(decimal* d, int digits){
    if (digits > 0 && digits < d->sig.length) {
        int unkBool = __must_round(d,digits);
        d->sig.length = digits;

        if (unkBool >= 0) {
            __dorounddecup(d, digits);
        }
    }
}

void __num2dec(const decform* form, double x, decimal* d) {
    short digits = form->digits;
    int i;
    __num2dec_internal(d, x);

    if (d->sig.text[0] > 9) {
        return;
    }

    if (digits > SIGDIGLEN) {
        digits = SIGDIGLEN;
    }

    __rounddec(d, digits);

    while(d->sig.length < digits){
        d->sig.text[d->sig.length++] = 0;
    }

    d->exp -= d->sig.length - 1;

    for(i = 0; i < d->sig.length; i++) {
        d->sig.text[i] += '0';
    }
}
