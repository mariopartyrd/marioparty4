#include "game/hsfformat.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dolphin.h>
#include <ext_math.h>
#include <unordered_set>

extern "C" {
#include "port/byteswap.h"
}

static std::unordered_set<void *> sVisitedPtrs;

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

template <typename B> void *offset_ptr(B &base)
{
    return reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(&base));
}

template <typename B, typename T> T *offset_ptr(B &base, T *ptr)
{
    return reinterpret_cast<T *>(reinterpret_cast<uintptr_t>(&base) + reinterpret_cast<uintptr_t>(ptr));
}
template <typename B, typename T> T *offset_ptr(B &base, T *ptr, void *extra)
{
    return reinterpret_cast<T *>(reinterpret_cast<uintptr_t>(&base) + reinterpret_cast<uintptr_t>(ptr) + reinterpret_cast<uintptr_t>(extra));
}

// template <typename B, typename T> static inline void bswap(B &base, T &data);
// template <typename B, typename P> void bswap(B &base, P *&ptr)
// {
//     ptr = bswap32(ptr);
// }
// template <typename B, typename T> void bswap(B &base, T *&ptr, s32 count)
// {
//     ptr = bswap32(ptr);
//     if (ptr == nullptr) {
//         return;
//     }
//     T *objBase = offset_ptr(base, ptr);
//     for (s32 i = 0; i < count; ++i) {
//         if (sVisitedPtrs.contains(objBase)) {
//             continue;
//         }
//         sVisitedPtrs.insert(objBase);
//         bswap(base, *objBase);
//         ++objBase;
//     }
// }
// template <typename B, typename T> void bswap_list(B &base, T **&ptr)
// {
//     ptr = bswap32(ptr);
//     if (ptr == nullptr) {
//         return;
//     }
//     T **objBase = offset_ptr(base, ptr);
//     while (*objBase != nullptr) {
//         bswap(base, *objBase, 1);
//         ++objBase;
//     }
// }
// template <typename B, typename T> void bswap_list(B &base, T *(&ptr)[])
// {
//     T **objBase = ptr;
//     while (*objBase != nullptr) {
//         bswap(base, *objBase, 1);
//         ++objBase;
//     }
// }
template <typename B, typename T> static void bswap_flat(B &base, T *start, s32 count)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    T *objBase = start;
    for (s32 i = 0; i < count; ++i) {
        bswap(base, objBase[i]);
    }
    // sVisitedPtrs.insert(offset_ptr(base));
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
    // if (sVisitedPtrs.contains(offset_ptr(base))) {
    //     return;
    // }
    bswap(base, vec.x);
    bswap(base, vec.y);
    bswap(base, vec.z);
    //sVisitedPtrs.insert(offset_ptr(base));
}
template <typename B> void bswap(B &base, S16Vec &vec)
{
    // if (sVisitedPtrs.contains(offset_ptr(base))) {
    //     return;
    // }
    bswap(base, vec.x);
    bswap(base, vec.y);
    bswap(base, vec.z);
    //sVisitedPtrs.insert(offset_ptr(base));
}
template <typename B> void bswap(B &base, Vec2f &vec)
{
    // if (sVisitedPtrs.contains(offset_ptr(base))) {
    //     return;
    // }
    bswap(base, vec.x);
    bswap(base, vec.y);
    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfVector3f &vec)
{
    // if (sVisitedPtrs.contains(offset_ptr(base))) {
    //     return;
    // }
    bswap(base, vec.x);
    bswap(base, vec.y);
    bswap(base, vec.z);
    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, AnimData32b &obj, AnimData &dest)
{
    // if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.bankNum);
        bswap(base, obj.patNum);
        bswap(base, obj.bmpNum);
        bswap(base, obj.useNum);
        bswap(base, obj.bank);
        bswap(base, obj.pat);
        bswap(base, obj.bmp);
        // sVisitedPtrs.insert(offset_ptr(base));
    // }

    dest.bankNum = obj.bankNum;
    dest.patNum = obj.patNum;
    dest.bmpNum = obj.bmpNum;
    dest.useNum = obj.useNum;
    dest.bank = reinterpret_cast<AnimBankData *>(static_cast<uintptr_t>(obj.bank));
    dest.pat = reinterpret_cast<AnimPatData *>(static_cast<uintptr_t>(obj.pat));
    dest.bmp = reinterpret_cast<AnimBmpData *>(static_cast<uintptr_t>(obj.bmp));
}

template <typename B> void bswap(B &base, AnimBankData32b &obj, AnimBankData &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.timeNum);
        bswap(base, obj.unk);
        bswap(base, obj.frame);
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.timeNum = obj.timeNum;
    dest.unk = obj.unk;
    dest.frame = reinterpret_cast<AnimFrameData *>(static_cast<uintptr_t>(obj.frame));
}

template <typename B> void bswap(B &base, AnimPatData32b &obj, AnimPatData &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.layerNum);
        bswap(base, obj.centerX);
        bswap(base, obj.centerY);
        bswap(base, obj.sizeX);
        bswap(base, obj.sizeY);
        bswap(base, obj.layer);
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.layerNum = obj.layerNum;
    dest.centerX = obj.centerX;
    dest.centerY = obj.centerY;
    dest.sizeX = obj.sizeX;
    dest.sizeY = obj.sizeY;
    dest.layer = reinterpret_cast<AnimLayerData *>(static_cast<uintptr_t>(obj.layer));
}

template <typename B> void bswap(B &base, AnimBmpData32b &obj, AnimBmpData &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.pixSize);
        bswap(base, obj.dataFmt);
        bswap(base, obj.palNum);
        bswap(base, obj.sizeX);
        bswap(base, obj.sizeY);
        bswap(base, obj.dataSize);
        bswap(base, obj.palData);
        bswap(base, obj.data);
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.pixSize = obj.pixSize;
    dest.dataFmt = obj.dataFmt;
    dest.palNum = obj.palNum;
    dest.sizeX = obj.sizeX;
    dest.sizeY = obj.sizeY;
    dest.dataSize = obj.dataSize;
    dest.palData = reinterpret_cast<void *>(static_cast<uintptr_t>(obj.palData));
    dest.data = reinterpret_cast<void *>(static_cast<uintptr_t>(obj.data));
}

template <typename B> void bswap(B &base, AnimFrameData &obj)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.pat);
    bswap(base, obj.time);
    bswap(base, obj.shiftX);
    bswap(base, obj.shiftY);
    bswap(base, obj.flip);
    bswap(base, obj.pad);

    // sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, AnimLayerData &obj)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
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

    // sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfSection &obj)
{
    // don't guard
    bswap(base, obj.ofs);
    bswap(base, obj.count);
}

template <typename B> void bswap(B &base, HsfHeader &obj)
{
    // if (sVisitedPtrs.contains(offset_ptr(base))) {
    //     return;
    // }
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

    // TODO
    // sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfCluster32b &obj, HsfCluster &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.name[0]);
        bswap(base, obj.name[1]);
        bswap(base, obj.targetName);
        bswap(base, obj.part);
        bswap(base, obj.index);
        bswap_flat(base, obj.weight, sizeof(obj.weight) / sizeof(float));
        bswap(base, obj.type);
        bswap(base, obj.vertexCnt);
        bswap(base, obj.vertex);
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.name[0] = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name[0]));
    dest.name[1] = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name[1]));

    dest.targetName = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.targetName));
    dest.index = obj.index;
    std::copy(std::begin(obj.weight), std::end(obj.weight), dest.weight);

    dest.adjusted = obj.adjusted;
    dest.unk95 = obj.unk95;
    dest.type = obj.type;
    dest.vertexCnt = obj.vertexCnt;
    dest.vertex = reinterpret_cast<HsfBuffer **>(static_cast<uintptr_t>(obj.vertex));
}

template <typename B> void bswap(B &base, HsfAttribute32b &obj, HsfAttribute &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
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
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.name = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name));
    dest.unk04 = reinterpret_cast<struct hsfdraw_struct_01 *>(static_cast<uintptr_t>(obj.unk04));
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
    dest.bitmap = reinterpret_cast<HsfBitmap *>(static_cast<uintptr_t>(obj.bitmap));
}

template <typename B> void bswap(B &base, HsfMaterial32b &obj, HsfMaterial &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
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
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.name = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name));
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
    dest.attrs = reinterpret_cast<s32 *>(static_cast<uintptr_t>(obj.attrs));
}

template <typename B> void bswap(B &base, HsfScene &obj)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    u32 fogType = static_cast<u32>(obj.fogType);
    fogType = bswap32(fogType);
    obj.fogType = static_cast<GXFogType>(fogType);
    bswap(base, obj.start);
    bswap(base, obj.end);
    // TODO
    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfBuffer32b &obj, HsfBuffer &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.name);
        bswap(base, obj.count);
        bswap(base, obj.data);
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.name = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name));
    dest.count = obj.count;
    dest.data = reinterpret_cast<void *>(static_cast<uintptr_t>(obj.data));
}

template <typename B> void bswap(B &base, HsfMatrix32b &obj, HsfMatrix &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.base_idx);
        bswap(base, obj.count);
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.base_idx = obj.base_idx;
    dest.count = obj.count;

    dest.data = reinterpret_cast<Mtx *>(&obj + 1);
    u32 matricesToByteSwap = dest.base_idx + dest.count + dest.base_idx * dest.count;
    for (u32 i = 0; i < matricesToByteSwap; i++) {
        for (u32 j = 0; j < 3; j++) {
            bswap_flat(base, dest.data[i][j], 4);
        }
    }
}

template <typename B> void bswap(B &base, HsfPalette32b &obj, HsfPalette &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.name);
        bswap(base, obj.unk);
        bswap(base, obj.palSize);
        bswap(base, obj.data);
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.name = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name));
    dest.unk = obj.unk;
    dest.palSize = obj.palSize;
    dest.data = reinterpret_cast<u16 *>(static_cast<uintptr_t>(obj.data));

}

template <typename B> void bswap(B &base, HsfPart32b &obj, HsfPart &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.name);
        bswap(base, obj.count);
        bswap(base, obj.vertex);
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.name = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name));
    dest.count = obj.count;
    dest.vertex = reinterpret_cast<u16 *>(static_cast<uintptr_t>(obj.vertex));

}

template <typename B> void bswap(B &base, HsfBitmap32b &obj, HsfBitmap &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.name);
        bswap(base, obj.maxLod);
        bswap(base, obj.sizeX);
        bswap(base, obj.sizeY);
        bswap(base, obj.palSize);
        bswap(base, obj.palData);
        bswap(base, obj.unk);
        bswap(base, obj.data);
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.name = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name));
    dest.maxLod = obj.maxLod;
    dest.dataFmt = obj.dataFmt;
    dest.pixSize = obj.pixSize;
    dest.sizeX = obj.sizeX;
    dest.sizeY = obj.sizeY;
    dest.palSize = obj.palSize;
    dest.tint = obj.tint;
    dest.palData = reinterpret_cast<void *>(static_cast<uintptr_t>(obj.palData));
    dest.unk = obj.unk;
    dest.data = reinterpret_cast<void *>(static_cast<uintptr_t>(obj.data));
}

template <typename B> void bswap(B &base, HsfMapAttr32b &obj, HsfMapAttr &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.minX);
        bswap(base, obj.minZ);
        bswap(base, obj.maxX);
        bswap(base, obj.maxZ);
        bswap(base, obj.data);
        bswap(base, obj.dataLen);
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.minX = obj.minX;
    dest.minZ = obj.minZ;
    dest.maxX = obj.maxZ;
    dest.data = reinterpret_cast<u16 *>(static_cast<uintptr_t>(obj.data));
    dest.dataLen = obj.dataLen;

}

template <typename B> void bswap(B &base, HsfTransform &obj)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.pos);
    bswap(base, obj.rot);
    bswap(base, obj.scale);

    // sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfSkeleton32b &obj, HsfSkeleton &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.name);
        bswap(base, obj.transform);
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.name = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name));
    dest.transform = obj.transform;
}

template <typename B> void bswap(B &base, HsfShape32b &obj, HsfShape &dest)
{
    if (!sVisitedPtrs.contains(offset_ptr(base))) {
        bswap(base, obj.name);
        bswap(base, obj.vertex);
        // sVisitedPtrs.insert(offset_ptr(base));
    }

    dest.name = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name));
    dest.vertex = reinterpret_cast<HsfBuffer **>(static_cast<uintptr_t>(obj.vertex));
}

template <typename B> void bswap(B &base, HsfCenvSingle &obj)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.target);
    bswap(base, obj.pos);
    bswap(base, obj.posCnt);
    bswap(base, obj.normal);
    bswap(base, obj.normalCnt);

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfCenvDualWeight &obj)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.weight);
    bswap(base, obj.pos);
    bswap(base, obj.posCnt);
    bswap(base, obj.normal);
    bswap(base, obj.normalCnt);

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfCenvDual32b &obj, HsfCenvDual &dest)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.target1);
    bswap(base, obj.target2);
    bswap(base, obj.weightCnt);
    bswap(base, obj.weight);

    dest.target1 = obj.target1;
    dest.target2 = obj.target2;
    dest.weightCnt = obj.weightCnt;
    dest.weight = reinterpret_cast<HsfCenvDualWeight *>(static_cast<uintptr_t>(obj.weight));

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfCenvMultiWeight &obj)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.target);
    bswap(base, obj.value);

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfCenvMulti32b &obj, HsfCenvMulti &dest)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.weightCnt);
    bswap(base, obj.pos);
    bswap(base, obj.posCnt);
    bswap(base, obj.normal);
    bswap(base, obj.normalCnt);
    bswap(base, obj.weight);

    dest.weightCnt = obj.weightCnt;
    dest.pos = obj.pos;
    dest.posCnt = obj.posCnt;
    dest.normal = obj.normal;
    dest.normalCnt = obj.normalCnt;
    dest.weight = reinterpret_cast<HsfCenvMultiWeight *>(static_cast<uintptr_t>(obj.weight));

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfCenv32b &obj, HsfCenv &dest)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.name);
    bswap(base, obj.singleData);
    bswap(base, obj.dualData);
    bswap(base, obj.multiData);
    bswap(base, obj.singleCount);
    bswap(base, obj.dualCount);
    bswap(base, obj.multiCount);
    bswap(base, obj.vtxCount);
    bswap(base, obj.copyCount);

    dest.name = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name));
    dest.singleData = reinterpret_cast<HsfCenvSingle *>(static_cast<uintptr_t>(obj.singleData));
    dest.dualData = reinterpret_cast<HsfCenvDual *>(static_cast<uintptr_t>(obj.dualData));
    dest.multiData = reinterpret_cast<HsfCenvMulti *>(static_cast<uintptr_t>(obj.multiData));
    dest.singleCount = obj.singleCount;
    dest.dualCount = obj.dualCount;
    dest.multiCount = obj.multiCount;
    dest.vtxCount = obj.vtxCount;
    dest.copyCount = obj.copyCount;

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfCamera &obj)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.target);
    bswap(base, obj.pos);
    bswap(base, obj.aspect_dupe);
    bswap(base, obj.fov);
    bswap(base, obj.nnear);
    bswap(base, obj.ffar);

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfLight &obj)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.pos);
    bswap(base, obj.target);
    bswap(base, obj.type);
    bswap(base, obj.unk2C);
    bswap(base, obj.ref_distance);
    bswap(base, obj.ref_brightness);
    bswap(base, obj.cutoff);

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfObjectData32b &obj, HsfObjectData &dest, u32 type)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.parent);
    bswap(base, obj.childrenCount);
    bswap(base, obj.children);
    bswap(base, obj.base);
    bswap(base, obj.curr);
    bswap(base, obj.face);
    bswap(base, obj.vertex);
    bswap(base, obj.normal);
    bswap(base, obj.color);
    bswap(base, obj.st);
    bswap(base, obj.material);
    bswap(base, obj.attribute);
    bswap(base, obj.vertexShapeCnt);
    bswap(base, obj.vertexShape);
    bswap(base, obj.clusterCnt);
    bswap(base, obj.cluster);
    bswap(base, obj.cenvCnt);
    bswap(base, obj.cenv);
    bswap(base, obj.vtxtop);
    bswap(base, obj.normtop);

    dest.parent = reinterpret_cast<struct hsf_object *>(static_cast<uintptr_t>(obj.parent));
    dest.childrenCount = obj.childrenCount;
    dest.children = reinterpret_cast<struct hsf_object **>(static_cast<uintptr_t>(obj.children));
    dest.base = obj.base;
    dest.curr = obj.curr;
    dest.face = reinterpret_cast<HsfBuffer *>(static_cast<uintptr_t>(obj.face));
    dest.vertex = reinterpret_cast<HsfBuffer *>(static_cast<uintptr_t>(obj.vertex));
    dest.normal = reinterpret_cast<HsfBuffer *>(static_cast<uintptr_t>(obj.normal));
    dest.color = reinterpret_cast<HsfBuffer *>(static_cast<uintptr_t>(obj.color));
    dest.st = reinterpret_cast<HsfBuffer *>(static_cast<uintptr_t>(obj.st));
    dest.material = reinterpret_cast<HsfMaterial *>(static_cast<uintptr_t>(obj.material));
    dest.attribute = reinterpret_cast<HsfAttribute *>(static_cast<uintptr_t>(obj.attribute));
    std::copy(std::begin(obj.unk120), std::end(obj.unk120), dest.unk120);
    dest.shapeType = obj.shapeType;
    dest.unk123 = obj.unk123;
    dest.vertexShapeCnt = obj.vertexShapeCnt;
    dest.vertexShape = reinterpret_cast<HsfBuffer **>(static_cast<uintptr_t>(obj.vertexShape));
    dest.clusterCnt = obj.clusterCnt;
    dest.cluster = reinterpret_cast<HsfCluster **>(static_cast<uintptr_t>(obj.cluster));
    dest.cenvCnt = obj.cenvCnt;
    dest.cenv = reinterpret_cast<HsfCenv *>(static_cast<uintptr_t>(obj.cenv));
    dest.vtxtop = reinterpret_cast<HsfVector3f *>(static_cast<uintptr_t>(obj.vtxtop));
    dest.normtop = reinterpret_cast<HsfVector3f *>(static_cast<uintptr_t>(obj.normtop));

    switch (type) {
        case HSF_OBJ_MESH:
            bswap(base, obj.mesh.min);
            bswap(base, obj.mesh.max);
            bswap(base, obj.mesh.baseMorph);
            bswap_flat(base, obj.mesh.morphWeight, std::size(obj.mesh.morphWeight));

            dest.mesh.min = obj.mesh.min;
            dest.mesh.max = obj.mesh.max;
            dest.mesh.baseMorph = obj.mesh.baseMorph;
            std::copy(std::begin(obj.mesh.morphWeight), std::end(obj.mesh.morphWeight), dest.mesh.morphWeight);
            break;
        case HSF_OBJ_REPLICA:
            bswap(base, obj.replica);

            dest.replica = reinterpret_cast<struct hsf_object *>(static_cast<uintptr_t>(obj.replica));
            break;
        default:
            break;
    }

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfObject32b &obj, HsfObject &dest)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.name);
    bswap(base, obj.type);
    bswap(base, obj.constData);
    bswap(base, obj.flags);

    dest.name = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name));
    dest.type = obj.type;
    dest.constData = reinterpret_cast<void *>(static_cast<uintptr_t>(obj.constData));
    dest.flags = obj.flags;

    switch (obj.type) {
        case HSF_OBJ_CAMERA:
            bswap(base, obj.camera);
            memcpy(&dest.camera, &obj.camera, sizeof(dest.camera));
            break;
        case HSF_OBJ_LIGHT:
            bswap(base, obj.light);
            memcpy(&dest.light, &obj.light, sizeof(dest.light));
            break;
        default:
            bswap(base, obj.data, dest.data, obj.type);
            break;
    }

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfBitmapKey32b &obj, HsfBitmapKey &dest)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.time);
    bswap(base, obj.data);

    dest.time = obj.time;
    dest.data = reinterpret_cast<HsfBitmap *>(static_cast<uintptr_t>(obj.data));

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfTrack32b &obj, HsfTrack &dest)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.target);
    bswap(base, obj.curveType);
    bswap(base, obj.numKeyframes);

    dest.type = obj.type;
    dest.start = obj.start;
    dest.target = obj.target;
    dest.curveType = obj.curveType;
    dest.numKeyframes = obj.numKeyframes;

    if (obj.curveType == HSF_CURVE_CONST) {
        bswap(base, obj.value);
        dest.value = obj.value;
    }
    else {
        bswap(base, obj.data);
        dest.data = reinterpret_cast<void *>(static_cast<uintptr_t>(obj.data));
    }

    // TODO is this right?
    if (obj.type == HSF_TRACK_CLUSTER_WEIGHT) {
        bswap(base, obj.unk04);
        dest.unk04 = obj.unk04;
    }
    else {
        bswap(base, obj.param);
        bswap(base, obj.channel);

        dest.param = obj.param;
        dest.channel = obj.channel;
    }

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfMotion32b &obj, HsfMotion &dest)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.name);
    bswap(base, obj.numTracks);
    bswap(base, obj.track);
    bswap(base, obj.len);

    dest.name = reinterpret_cast<char *>(static_cast<uintptr_t>(obj.name));
    dest.numTracks = obj.numTracks;
    dest.track = reinterpret_cast<HsfTrack *>(static_cast<uintptr_t>(obj.track));
    dest.len = obj.len;

    //sVisitedPtrs.insert(offset_ptr(base));
}

template <typename B> void bswap(B &base, HsfFace32b &obj, HsfFace &dest)
{
    if (sVisitedPtrs.contains(offset_ptr(base))) {
        return;
    }
    bswap(base, obj.type);
    bswap(base, obj.mat);
    bswap(base, obj.nbt);

    dest.type = obj.type;
    dest.mat = obj.mat;
    dest.nbt = obj.nbt;

    // TODO or obj.type == 4?
    if ((obj.type & 7) == 4) {
        bswap(base, obj.strip.count);
        bswap(base, obj.strip.data);
        bswap_flat(base, obj.strip.indices[0], 3 * 4);
    
        dest.strip.count = obj.strip.count;
        dest.strip.data = reinterpret_cast<s16 *>(static_cast<uintptr_t>(obj.strip.data));
        std::copy(&obj.strip.indices[0][0], &obj.strip.indices[0][0] + 3 * 4, &dest.strip.indices[0][0]);
    }
    else {
        bswap_flat(base, obj.indices[0], 4 * 4);
        std::copy(&obj.indices[0][0], &obj.indices[0][0] + 4 * 4, &dest.indices[0][0]);
    }

    //sVisitedPtrs.insert(offset_ptr(base));
}

void byteswap_clear_visited_ptrs()
{
    sVisitedPtrs.clear();
}

void byteswap_u16(u16 *src)
{
    bswap(*src, *src);
}

void byteswap_s16(s16 *src)
{
    bswap(*src, *src);
}

void byteswap_u32(u32 *src)
{
    bswap(*src, *src);
}

void byteswap_s32(s32 *src)
{
    bswap(*src, *src);
}

void byteswap_float(float *src)
{
    bswap(*src, *src);
}

void byteswap_vec(Vec *src)
{
    bswap(*src, *src);
}

void byteswap_vec2f(Vec2f *src)
{
    bswap(*src, *src);
}

void byteswap_hsfvec3f(HsfVector3f *src)
{
    bswap(*src, *src);
}

void byteswap_hsfvec2f(HsfVector2f *src)
{
    auto *vec = reinterpret_cast<Vec2f *>(src);
    bswap(*vec, *vec);
}

void byteswap_animdata(void *src, AnimData *dest)
{
    auto *anim = reinterpret_cast<AnimData32b *>(src);
    bswap(*anim, *anim, *dest);
}

void byteswap_animbankdata(AnimBankData32b *src, AnimBankData *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_animpatdata(AnimPatData32b *src, AnimPatData *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_animbmpdata(AnimBmpData32b *src, AnimBmpData *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_animframedata(AnimFrameData *src)
{
    bswap(*src, *src);
}

void byteswap_animlayerdata(AnimLayerData *src)
{
    bswap(*src, *src);
}

void byteswap_hsfheader(HsfHeader *src)
{
    bswap(*src, *src);
}

void byteswap_hsfcluster(HsfCluster32b *src, HsfCluster *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfattribute(HsfAttribute32b *src, HsfAttribute *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfmaterial(HsfMaterial32b *src, HsfMaterial *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfscene(HsfScene *src)
{
    bswap(*src, *src);
}

void byteswap_hsfbuffer(HsfBuffer32b *src, HsfBuffer *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfmatrix(HsfMatrix32b *src, HsfMatrix *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfpalette(HsfPalette32b *src, HsfPalette *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfpart(HsfPart32b *src, HsfPart *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfbitmap(HsfBitmap32b *src, HsfBitmap *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfmapattr(HsfMapAttr32b *src, HsfMapAttr *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfskeleton(HsfSkeleton32b *src, HsfSkeleton *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfshape(HsfShape32b *src, HsfShape *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfcenv_single(HsfCenvSingle *src)
{
    bswap(*src, *src);
}

void byteswap_hsfcenv_dual_weight(HsfCenvDualWeight *src)
{
    bswap(*src, *src);
}

void byteswap_hsfcenv_dual(HsfCenvDual32b *src, HsfCenvDual *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfcenv_multi_weight(HsfCenvMultiWeight *src)
{
    bswap(*src, *src);
}

void byteswap_hsfcenv_multi(HsfCenvMulti32b *src, HsfCenvMulti *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfcenv(HsfCenv32b *src, HsfCenv *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfobject(HsfObject32b *src, HsfObject *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfbitmapkey(HsfBitmapKey32b *src, HsfBitmapKey *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsftrack(HsfTrack32b *src, HsfTrack *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfmotion(HsfMotion32b *src, HsfMotion *dest)
{
    bswap(*src, *src, *dest);
}

void byteswap_hsfface(HsfFace32b *src, HsfFace *dest)
{
    bswap(*src, *src, *dest);
}
