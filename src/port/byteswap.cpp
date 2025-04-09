#include "game/hsfformat.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <dolphin.h>
#include <ext_math.h>
#include <unordered_set>

extern "C" {
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
    } v { .t = val };
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
    } v { .t = val };
#if __GNUC__
    v.u = __builtin_bswap32(v.u);
#elif _WIN32
    v.u = _byteswap_ulong(v.u);
#else
    v.u = ((v.u & 0x0000FFFF) << 16) | ((v.u & 0xFFFF0000) >> 16) | ((v.u & 0x00FF00FF) << 8) | ((v.u & 0xFF00FF00) >> 8);
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
    return reinterpret_cast<T *>(reinterpret_cast<uintptr_t>(&base) + reinterpret_cast<uintptr_t>(ptr));
}
template <typename B, typename T> T *offset_ptr(B &base, T *ptr, void *extra)
{
    return reinterpret_cast<T *>(reinterpret_cast<uintptr_t>(&base) + reinterpret_cast<uintptr_t>(ptr) + reinterpret_cast<uintptr_t>(extra));
}

template <typename B, typename T> static inline void bswap(B &base, T &data);
template <typename B, typename P> void bswap(B &base, P *&ptr)
{
    ptr = bswap32(ptr);
}
template <typename B, typename T> void bswap(B &base, T *&ptr, s32 count)
{
    ptr = bswap32(ptr);
    if (ptr == nullptr) {
        return;
    }
    T *objBase = offset_ptr(base, ptr);
    for (s32 i = 0; i < count; ++i) {
        if (sVisitedPtrs.contains(objBase)) {
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
    if (ptr == nullptr) {
        return;
    }
    T **objBase = offset_ptr(base, ptr);
    while (*objBase != nullptr) {
        bswap(base, *objBase, 1);
        ++objBase;
    }
}
template <typename B, typename T> void bswap_list(B &base, T *(&ptr)[])
{
    T **objBase = ptr;
    while (*objBase != nullptr) {
        bswap(base, *objBase, 1);
        ++objBase;
    }
}
template <typename B, typename T> void bswap_flat(B &base, T *start, s32 count)
{
    T *objBase = start;
    for (s32 i = 0; i < count; ++i) {
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

template <typename B> void bswap(B &base, HsfSection &obj)
{
    bswap(base, obj.ofs);
    bswap(base, obj.count);
}

template <typename B> void bswap(B &base, HsfHeader &obj)
{
    bswap(base, obj.scene);
    bswap(base, obj.color);
    bswap(base, obj.material);
    bswap(base, obj.attribute);
    bswap(base, obj.vertex);
    bswap(base, obj.normal);
    bswap(base, obj.st);
    bswap(base, obj.face);
    bswap(base, obj.object);
    bswap(base, obj.bitmap);
    bswap(base, obj.palette);
    bswap(base, obj.motion);
    bswap(base, obj.cenv);
    bswap(base, obj.skeleton);
    bswap(base, obj.part);
    bswap(base, obj.cluster);
    bswap(base, obj.shape);
    bswap(base, obj.mapAttr);
    bswap(base, obj.matrix);
    bswap(base, obj.symbol);
    bswap(base, obj.string);
}

template <typename B> void bswap(B &base, HsfCluster32b &obj, HsfCluster &dest)
{
    bswap(base, obj.name[0]);
    bswap(base, obj.name[1]);
    bswap(base, obj.targetName);
    bswap(base, obj.part);
    bswap(base, obj.index);
    bswap_flat(base, obj.weight, sizeof(obj.weight) / sizeof(float));
    bswap(base, obj.type);
    bswap(base, obj.vertexCnt);
    bswap(base, obj.vertex);

    dest.name[0] = reinterpret_cast<char *>(obj.name[0]);
    dest.name[1] = reinterpret_cast<char *>(obj.name[1]);

    dest.targetName = reinterpret_cast<char *>(obj.targetName);
    dest.index = obj.index;
    std::copy(std::begin(obj.weight), std::end(obj.weight), dest.weight);

    dest.adjusted = obj.adjusted;
    dest.unk95 = obj.unk95;
    dest.type = obj.type;
    dest.vertexCnt = obj.vertexCnt;
    dest.vertex = reinterpret_cast<HsfBuffer **>(obj.vertex);
}

template <typename B> void bswap(B &base, HsfAttribute32b &obj, HsfAttribute &dest)
{
    bswap(base, obj.name);
    bswap(base, obj.unk04);
    bswap(base, obj.unk0C);
    bswap(base, obj.unk14);
    bswap(base, obj.unk20);
    bswap(base, obj.unk28);
    bswap(base, obj.unk2C);
    bswap(base, obj.unk30);
    bswap(base, obj.unk34);
    bswap(base, obj.wrap_s);
    bswap(base, obj.wrap_t);
    bswap(base, obj.unk78);
    bswap(base, obj.flag);
    bswap(base, obj.bitmap);

    dest.name = reinterpret_cast<char *>(obj.name);
    dest.unk04 = reinterpret_cast<struct hsfdraw_struct_01 *>(obj.unk04);
    std::copy(std::begin(obj.unk8), std::end(obj.unk8), dest.unk8);
    dest.unk0C = obj.unk0C;
    std::copy(std::begin(obj.unk10), std::end(obj.unk10), dest.unk10);
    dest.unk14 = obj.unk14;
    std::copy(std::begin(obj.unk18), std::end(obj.unk18), dest.unk18);
    dest.unk20 = obj.unk20;
    std::copy(std::begin(obj.unk24), std::end(obj.unk24), dest.unk24);
    dest.unk28 = obj.unk28;
    dest.unk2C = obj.unk2C;
    dest.unk30 = obj.unk30;
    dest.unk34 = obj.unk34;
    std::copy(std::begin(obj.unk38), std::end(obj.unk38), dest.unk38);
    dest.wrap_s = obj.wrap_s;
    dest.wrap_t = obj.wrap_t;
    std::copy(std::begin(obj.unk6C), std::end(obj.unk6C), dest.unk6C);
    dest.unk78 = obj.unk78;
    dest.flag = obj.flag;
    dest.bitmap = reinterpret_cast<HsfBitmap *>(obj.bitmap);
}

template <typename B> void bswap(B &base, HsfMaterial32b &obj, HsfMaterial &dest)
{
    bswap(base, obj.name);
    bswap(base, obj.pass);
    bswap(base, obj.hilite_scale);
    bswap(base, obj.unk18);
    bswap(base, obj.invAlpha);
    bswap_flat(base, obj.unk20, sizeof(obj.unk20) / sizeof(float));
    bswap(base, obj.refAlpha);
    bswap(base, obj.unk2C);
    bswap(base, obj.flags);
    bswap(base, obj.numAttrs);
    bswap(base, obj.attrs);

    dest.name = reinterpret_cast<char *>(obj.name);
    std::copy(std::begin(obj.unk4), std::end(obj.unk4), dest.unk4);
    dest.pass = obj.pass;
    dest.vtxMode = obj.vtxMode;
    std::copy(std::begin(obj.litColor), std::end(obj.litColor), dest.litColor);
    std::copy(std::begin(obj.color), std::end(obj.color), dest.color);
    std::copy(std::begin(obj.shadowColor), std::end(obj.shadowColor), dest.shadowColor);
    dest.hilite_scale = obj.hilite_scale;
    dest.unk18 = obj.unk18;
    dest.invAlpha = obj.invAlpha;
    std::copy(std::begin(obj.unk20), std::end(obj.unk20), dest.unk20);
    dest.refAlpha = obj.refAlpha;
    dest.unk2C = obj.unk2C;
    dest.flags = obj.flags;
    dest.numAttrs = obj.numAttrs;
    dest.attrs = reinterpret_cast<s32 *>(obj.attrs);
}

template <typename B> void bswap(B &base, HsfScene &obj)
{
    u32 fogType = static_cast<u32>(obj.fogType);
    fogType = bswap32(fogType);
    obj.fogType = static_cast<GXFogType>(fogType);
    bswap(base, obj.start);
    bswap(base, obj.end);
}

template <typename B> void bswap(B &base, HsfBuffer32b &obj, HsfBuffer &dest)
{
    bswap(base, obj.name);
    bswap(base, obj.count);
    bswap(base, obj.data);

    dest.name = reinterpret_cast<char *>(obj.name);
    dest.count = obj.count;
    dest.data = reinterpret_cast<void *>(obj.data);
}

template <typename B> void bswap(B &base, HsfMatrix &obj)
{
    bswap(base, obj.base_idx);
    bswap(base, obj.count);

    obj.data = (Mtx *)((uintptr_t)&obj + sizeof(0xC)); // hardcoded for 64 bit support
    for (s32 i = 0; i < obj.count; i++) {
        for (s32 j = 0; j < 3; j++) {
            bswap_flat(base, obj.data[i][j], 4);
        }
    }
}   

template <typename B> void bswap(B &base, HsfPalette32b &obj, HsfPalette &dest)
{
    bswap(base, obj.name);
    bswap(base, obj.unk);
    bswap(base, obj.palSize);
    bswap(base, obj.data);

    dest.name = reinterpret_cast<char *>(obj.name);
    dest.unk = obj.unk;
    dest.palSize = obj.palSize;
    dest.data = reinterpret_cast<u16 *>(obj.data);
}

template <typename B> void bswap(B &base, HsfPart32b &obj, HsfPart &dest)
{
    bswap(base, obj.name);
    bswap(base, obj.count);
    bswap(base, obj.vertex);

    dest.name = reinterpret_cast<char *>(obj.name);
    dest.count = obj.count;
    dest.vertex = reinterpret_cast<u16 *>(obj.vertex);
}

template <typename B> void bswap(B &base, HsfBitmap32b &obj, HsfBitmap &dest)
{
    bswap(base, obj.name);
    bswap(base, obj.maxLod);
    bswap(base, obj.sizeX);
    bswap(base, obj.sizeY);
    bswap(base, obj.palSize);
    bswap(base, obj.palData);
    bswap(base, obj.unk);
    bswap(base, obj.data);

    dest.name = reinterpret_cast<char *>(obj.name);
    dest.maxLod = obj.maxLod;
    dest.dataFmt = obj.dataFmt;
    dest.pixSize = obj.pixSize;
    dest.sizeX = obj.sizeX;
    dest.sizeY = obj.sizeY;
    dest.palSize = obj.palSize;
    dest.tint = obj.tint;
    dest.palData = reinterpret_cast<void *>(obj.palData);
    dest.unk = obj.unk;
    dest.data = reinterpret_cast<void *>(obj.data);
}

template <typename B> void bswap(B &base, HsfMapAttr32b &obj, HsfMapAttr &dest)
{
    bswap(base, obj.minX);
    bswap(base, obj.minZ);
    bswap(base, obj.maxX);
    bswap(base, obj.maxZ);
    bswap(base, obj.data);
    bswap(base, obj.dataLen);

    dest.minX = obj.minX;
    dest.minZ = obj.minZ;
    dest.maxX = obj.maxZ;
    dest.data = reinterpret_cast<u16 *>(obj.data);
    dest.dataLen = obj.dataLen;
}

template <typename B> void bswap(B &base, HsfTransform &obj)
{
    bswap(base, obj.pos);
    bswap(base, obj.rot);
    bswap(base, obj.scale);
}

template <typename B> void bswap(B &base, HsfSkeleton32b &obj, HsfSkeleton &dest)
{
    bswap(base, obj.name);
    bswap(base, obj.transform);

    dest.name = reinterpret_cast<char *>(obj.name);
    dest.transform = obj.transform;
}

template <typename B> void bswap(B &base, HsfShape32b &obj, HsfShape &dest)
{
    bswap(base, obj.name);
    bswap(base, obj.vertex);

    dest.name = reinterpret_cast<char *>(obj.name);
    dest.vertex = reinterpret_cast<HsfBuffer **>(obj.vertex);
}

template <typename B> void bswap(B &base, HsfCenvSingle &obj)
{
    bswap(base, obj.target);
    bswap(base, obj.pos);
    bswap(base, obj.posCnt);
    bswap(base, obj.normal);
    bswap(base, obj.normalCnt);
}

template <typename B> void bswap(B &base, HsfCenv32b &obj, HsfCenv &dest)
{
    bswap(base, obj.name);
    bswap(base, obj.singleData);
    bswap(base, obj.dualData);
    bswap(base, obj.multiData);
    bswap(base, obj.singleCount);
    bswap(base, obj.dualCount);
    bswap(base, obj.multiCount);
    bswap(base, obj.vtxCount);
    bswap(base, obj.copyCount);

    dest.name = reinterpret_cast<char *>(obj.name);
    dest.singleData = reinterpret_cast<HsfCenvSingle *>(obj.singleData);
    dest.dualData = reinterpret_cast<HsfCenvDual *>(obj.dualData);
    dest.multiData = reinterpret_cast<HsfCenvMulti *>(obj.multiData);
    dest.singleCount = obj.singleCount;
    dest.dualCount = obj.dualCount;
    dest.multiCount = obj.multiCount;
    dest.vtxCount = obj.vtxCount;
    dest.copyCount = obj.copyCount;
}

template <typename B> void bswap(B &base, HsfObject32b &obj, HsfObject &dest)
{
    bswap(base, obj.name);
    bswap(base, obj.type);
    bswap(base, obj.constData);
    bswap(base, obj.flags);

    dest.name = reinterpret_cast<char *>(obj.name);
    dest.type = obj.type;
    dest.constData = reinterpret_cast<void *>(obj.constData);
    dest.flags = obj.flags;
}

void byteswap_u16(u16 *src)
{
    bswap(*src, *src);
    sVisitedPtrs.clear();
}

void byteswap_s16(s16 *src)
{
    bswap(*src, *src);
    sVisitedPtrs.clear();
}

void byteswap_u32(u32 *src)
{
    bswap(*src, *src);
    sVisitedPtrs.clear();
}

void byteswap_s32(s32 *src)
{
    bswap(*src, *src);
    sVisitedPtrs.clear();
}

void byteswap_hsfvec3f(HsfVector3f *src)
{
    auto *vec = reinterpret_cast<Vec *>(src);
    bswap(*vec, *vec);
    sVisitedPtrs.clear();
}

void byteswap_hsfvec2f(HsfVector2f *src)
{
    auto *vec = reinterpret_cast<Vec2f *>(src);
    bswap(*vec, *vec);
    sVisitedPtrs.clear();
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

void byteswap_hsfheader(HsfHeader *src)
{
    bswap(*src, *src);
    sVisitedPtrs.clear();
}

void byteswap_hsfcluster(HsfCluster32b *src, HsfCluster *dest)
{
    bswap(*src, *src, *dest);
    sVisitedPtrs.clear();
}

void byteswap_hsfattribute(HsfAttribute32b *src, HsfAttribute *dest)
{
    bswap(*src, *src, *dest);
    sVisitedPtrs.clear();
}

void byteswap_hsfmaterial(HsfMaterial32b *src, HsfMaterial *dest)
{
    bswap(*src, *src, *dest);
    sVisitedPtrs.clear();
}

void byteswap_hsfscene(HsfScene *src)
{
    bswap(*src, *src);
    sVisitedPtrs.clear();
}

void byteswap_hsfbuffer(HsfBuffer32b *src, HsfBuffer *dest)
{
    bswap(*src, *src, *dest);
    sVisitedPtrs.clear();
}

void byteswap_hsfmatrix(HsfMatrix *src)
{
    bswap(*src, *src);
    sVisitedPtrs.clear();
}

void byteswap_hsfpalette(HsfPalette32b *src, HsfPalette *dest)
{
    bswap(*src, *src, *dest);
    sVisitedPtrs.clear();
}

void byteswap_hsfpart(HsfPart32b *src, HsfPart *dest)
{
    bswap(*src, *src, *dest);
    sVisitedPtrs.clear();
}

void byteswap_hsfbitmap(HsfBitmap32b *src, HsfBitmap *dest)
{
    bswap(*src, *src, *dest);
    sVisitedPtrs.clear();
}

void byteswap_hsfmapattr(HsfMapAttr32b *src, HsfMapAttr *dest)
{
    bswap(*src, *src, *dest);
    sVisitedPtrs.clear();
}

void byteswap_hsfskeleton(HsfSkeleton32b *src, HsfSkeleton *dest)
{
    bswap(*src, *src, *dest);
    sVisitedPtrs.clear();
}

void byteswap_hsfshape(HsfShape32b *src, HsfShape *dest)
{
    bswap(*src, *src, *dest);
    sVisitedPtrs.clear();
}

void byteswap_hsfcenvsingle(HsfCenvSingle *src)
{
    bswap(*src, *src);
    sVisitedPtrs.clear();
}

void byteswap_hsfcenv(HsfCenv32b *src, HsfCenv *dest)
{
    bswap(*src, *src, *dest);
    sVisitedPtrs.clear();
}

void byteswap_hsfobject(HsfObject32b *src, HsfObject *dest)
{
    bswap(*src, *src, *dest);
    sVisitedPtrs.clear();
}