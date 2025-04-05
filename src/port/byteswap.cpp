#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <dolphin.h>
#include <ext_math.h>
#include <unordered_set>

extern "C"
{
#include "port/byteswap.h"

typedef struct AnimData32b {
    s16 bankNum;
    s16 patNum;
    s16 bmpNum;
    s16 useNum;

    u32 bank;
    u32 pat;
    u32 bmp;
} AnimData32b;

typedef struct AnimBankData32b {
    s16 timeNum;
    s16 unk;
    u32 frame;
} AnimBankData32b;

typedef struct AnimPatData32b {
    s16 layerNum;
    s16 centerX;
    s16 centerY;
    s16 sizeX;
    s16 sizeY;
    u32 layer;
} AnimPatData32b;

typedef struct AnimBmpData32b {
    u8 pixSize;
    u8 dataFmt;
    s16 palNum;
    s16 sizeX;
    s16 sizeY;
    u32 dataSize;
    u32 palData;
    u32 data;
} AnimBmpData32b;

}

template <typename T> [[nodiscard]] constexpr T bswap16(T val) noexcept
{
    static_assert(sizeof(T) == sizeof(u16));
    union {
        u16 u;
        T t;
    } v{.t = val};
#if __GNUC__
    v.u = __builtin_bswap16(v.u);
#elif _WIN32
    v.u = _byteswap_ushort(v.u);
#else
    v.u = (v.u << 8) | ((v.u >> 8) & 0xFF);
#endif
    return v.t;
}

template <typename T> [[nodiscard]] constexpr T bswap32(T val) noexcept
{
    static_assert(sizeof(T) == sizeof(u32));
    union {
        u32 u;
        T t;
    } v{.t = val};
#if __GNUC__
    v.u = __builtin_bswap32(v.u);
#elif _WIN32
    v.u = _byteswap_ulong(v.u);
#else
    v.u = ((v.u & 0x0000FFFF) << 16) | ((v.u & 0xFFFF0000) >> 16) | ((v.u & 0x00FF00FF) << 8) |
          ((v.u & 0xFF00FF00) >> 8);
#endif
    return v.t;
}

static void bswap16_unaligned(u8 *ptr)
{
    u8 temp = ptr[0];
    ptr[0] = ptr[1];
    ptr[1] = temp;
}

static void bswap32_unaligned(u8 *ptr)
{
    u8 temp = ptr[0];
    ptr[0] = ptr[3];
    ptr[3] = temp;
    temp = ptr[1];
    ptr[1] = ptr[2];
    ptr[2] = temp;
}

static std::unordered_set<void *> sVisitedPtrs;

template <typename B, typename T> T *offset_ptr(B &base, T *ptr)
{
    return reinterpret_cast<T *>(reinterpret_cast<uintptr_t>(&base) +
                                 reinterpret_cast<uintptr_t>(ptr));
}
template <typename B, typename T> T *offset_ptr(B &base, T *ptr, void *extra)
{
    return reinterpret_cast<T *>(reinterpret_cast<uintptr_t>(&base) +
                                 reinterpret_cast<uintptr_t>(ptr) +
                                 reinterpret_cast<uintptr_t>(extra));
}

template <typename B, typename T> static inline void bswap(B &base, T &data);
template <typename B, typename P> void bswap(B &base, P *&ptr)
{
    ptr = bswap32(ptr);
}
template <typename B, typename T> void bswap(B &base, T *&ptr, s32 count)
{
    ptr = bswap32(ptr);
    if (ptr == nullptr)
    {
        return;
    }
    T *objBase = offset_ptr(base, ptr);
    for (s32 i = 0; i < count; ++i)
    {
        if (sVisitedPtrs.contains(objBase))
        {
            continue;
        }
        sVisitedPtrs.insert(objBase);
        bswap(base, *objBase);
        ++objBase;
    }
}
template <typename B, typename T> void bswap_list(B &base, T **&ptr)
{
    ptr = bswap32(ptr);
    if (ptr == nullptr)
    {
        return;
    }
    T **objBase = offset_ptr(base, ptr);
    while (*objBase != nullptr)
    {
        bswap(base, *objBase, 1);
        ++objBase;
    }
}
template <typename B, typename T> void bswap_list(B &base, T *(&ptr)[])
{
    T **objBase = ptr;
    while (*objBase != nullptr)
    {
        bswap(base, *objBase, 1);
        ++objBase;
    }
}
template <typename B, typename T> void bswap_flat(B &base, T *start, s32 count)
{
    T *objBase = start;
    for (s32 i = 0; i < count; ++i)
    {
        bswap(base, objBase[i]);
    }
}
template <typename B> void bswap(B &base, f32 &v)
{
    v = bswap32(v);
}
template <typename B> void bswap(B &base, s32 &v)
{
    v = bswap32(v);
}
template <typename B> void bswap(B &base, u32 &v)
{
    v = bswap32(v);
}
template <typename B> void bswap(B &base, s16 &v)
{
    v = bswap16(v);
}
template <typename B> void bswap(B &base, u16 &v)
{
    v = bswap16(v);
}
template <typename B> void bswap(B &base, u8 &v)
{
    // no-op
}
template <typename B> void bswap(B &base, s8 &v)
{
    // no-op
}
template <typename B> void bswap(B &base, char &v)
{
    // no-op
}
template <typename B> void bswap(B &base, Vec &vec)
{
    bswap(base, vec.x);
    bswap(base, vec.y);
    bswap(base, vec.z);
}
template <typename B> void bswap(B &base, S16Vec &vec)
{
    bswap(base, vec.x);
    bswap(base, vec.y);
    bswap(base, vec.z);
}
template <typename B> void bswap(B &base, Vec2f &vec)
{
    bswap(base, vec.x);
    bswap(base, vec.y);
}

template <typename B> void bswap(B &base, AnimData32b &obj, AnimData &dest)
{
    bswap(base, obj.bankNum);
    bswap(base, obj.patNum);
    bswap(base, obj.bmpNum);
    bswap(base, obj.useNum);
    bswap(base, obj.bank);
    bswap(base, obj.pat);
    bswap(base, obj.bmp);

    dest.bankNum = obj.bankNum;
    dest.patNum = obj.patNum;
    dest.bmpNum = obj.bmpNum;
    dest.useNum = obj.useNum;
    dest.bank = reinterpret_cast<AnimBankData *>(obj.bank);
    dest.pat = reinterpret_cast<AnimPatData *>(obj.pat);
    dest.bmp = reinterpret_cast<AnimBmpData *>(obj.bmp);
}

template <typename B> void bswap(B &base, AnimBankData32b &obj, AnimBankData &dest)
{
    bswap(base, obj.timeNum);
    bswap(base, obj.unk);
    bswap(base, obj.frame);

    dest.timeNum = obj.timeNum;
    dest.unk = obj.unk;
    dest.frame = reinterpret_cast<AnimFrameData *>(obj.frame);
}

template <typename B> void bswap(B &base, AnimPatData32b &obj, AnimPatData &dest)
{
    bswap(base, obj.layerNum);
    bswap(base, obj.centerX);
    bswap(base, obj.centerY);
    bswap(base, obj.sizeX);
    bswap(base, obj.sizeY);
    bswap(base, obj.layer);

    dest.layerNum = obj.layerNum;
    dest.centerX = obj.centerX;
    dest.centerY = obj.centerY;
    dest.sizeX = obj.sizeX;
    dest.sizeY = obj.sizeY;
    dest.layer = reinterpret_cast<AnimLayerData *>(obj.layer);
}

template <typename B> void bswap(B &base, AnimBmpData32b &obj, AnimBmpData &dest)
{
    bswap(base, obj.pixSize);
    bswap(base, obj.dataFmt);
    bswap(base, obj.palNum);
    bswap(base, obj.sizeX);
    bswap(base, obj.sizeY);
    bswap(base, obj.dataSize);
    bswap(base, obj.palData);
    bswap(base, obj.data);

    dest.pixSize = obj.pixSize;
    dest.dataFmt = obj.dataFmt;
    dest.palNum = obj.palNum;
    dest.sizeX = obj.sizeX;
    dest.sizeY = obj.sizeY;
    dest.dataSize = obj.dataSize;
    dest.palData = reinterpret_cast<void *>(obj.palData);
    dest.data = reinterpret_cast<void *>(obj.data);
}

template <typename B> void bswap(B &base, AnimFrameData &obj)
{
    bswap(base, obj.pat);
    bswap(base, obj.time);
    bswap(base, obj.shiftX);
    bswap(base, obj.shiftY);
    bswap(base, obj.flip);
    bswap(base, obj.pad);
}

template <typename B> void bswap(B &base, AnimLayerData &obj)
{
    bswap(base, obj.alpha);
    bswap(base, obj.flip);
    bswap(base, obj.bmpNo);
    bswap(base, obj.startX);
    bswap(base, obj.startY);
    bswap(base, obj.sizeX);
    bswap(base, obj.sizeY);
    bswap(base, obj.shiftX);
    bswap(base, obj.shiftY);
    bswap_flat(base, obj.vtx, sizeof(obj.vtx) / sizeof(s16));
}

void byteswap_animdata(void *src, AnimData *dest)
{
    auto *anim = reinterpret_cast<AnimData32b *>(src);
    bswap(*anim, *anim, *dest);
    sVisitedPtrs.clear();
}

void byteswap_animbankdata(void *src, AnimBankData *dest)
{
    auto *bank = reinterpret_cast<AnimBankData32b *>(src);
    bswap(*bank, *bank, *dest);
    sVisitedPtrs.clear();
}

void byteswap_animpatdata(void *src, AnimPatData *dest)
{
    auto *pat = reinterpret_cast<AnimPatData32b *>(src);
    bswap(*pat, *pat, *dest);
    sVisitedPtrs.clear();
}

void byteswap_animbmpdata(void *src, AnimBmpData *dest)
{
    auto *bmp = reinterpret_cast<AnimBmpData32b *>(src);
    bswap(*bmp, *bmp, *dest);
    sVisitedPtrs.clear();
}

void byteswap_animframedata(AnimFrameData *src)
{
    bswap(*src, *src);
    sVisitedPtrs.clear();
}

void byteswap_animlayerdata(AnimLayerData *src)
{
    bswap(*src, *src);
    sVisitedPtrs.clear();
}
