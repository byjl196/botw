#pragma once

#include "KingSystem/GameData/gdtManager.h"

namespace ksys::gdt {

inline bool getBool(FlagHandle handle, bool debug = false) {
    bool value{};

    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getBool(handle, &value, debug);

    return value;
}

inline s32 getS32(FlagHandle handle, bool debug = false) {
    s32 value{};

    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getS32(handle, &value, debug);

    return value;
}

inline f32 getF32(FlagHandle handle, bool debug = false) {
    f32 value{};

    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getF32(handle, &value, debug);

    return value;
}

inline void getStr(FlagHandle handle, const char** value, bool debug = false) {
    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getStr(handle, value, debug);
}

inline void getStr64(FlagHandle handle, const char** value, bool debug = false) {
    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getStr64(handle, value, debug);
}

inline void getStr256(FlagHandle handle, const char** value, bool debug = false) {
    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getStr256(handle, value, debug);
}

inline void getVec2f(FlagHandle handle, sead::Vector2f* value, bool debug = false) {
    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getVec2f(handle, value, debug);
}

inline void getVec3f(FlagHandle handle, sead::Vector3f* value, bool debug = false) {
    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getVec3f(handle, value, debug);
}

inline void getVec4f(FlagHandle handle, sead::Vector4f* value, bool debug = false) {
    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getVec4f(handle, value, debug);
}

inline bool getBool(FlagHandle handle, s32 idx, bool debug = false) {
    bool value{};

    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getBool(handle, &value, idx, debug);

    return value;
}

inline s32 getS32(FlagHandle handle, s32 idx, bool debug = false) {
    s32 value{};

    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getS32(handle, &value, idx, debug);

    return value;
}

inline f32 getF32(FlagHandle handle, s32 idx, bool debug = false) {
    f32 value{};

    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getF32(handle, &value, idx, debug);

    return value;
}

inline void getStr(FlagHandle handle, const char** value, s32 idx, bool debug = false) {
    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getStr(handle, value, idx, debug);
}

inline void getStr64(FlagHandle handle, const char** value, s32 idx, bool debug = false) {
    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getStr64(handle, value, idx, debug);
}

inline void getStr256(FlagHandle handle, const char** value, s32 idx, bool debug = false) {
    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getStr256(handle, value, idx, debug);
}

inline void getVec2f(FlagHandle handle, sead::Vector2f* value, s32 idx, bool debug = false) {
    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getVec2f(handle, value, idx, debug);
}

inline void getVec3f(FlagHandle handle, sead::Vector3f* value, s32 idx, bool debug = false) {
    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getVec3f(handle, value, idx, debug);
}

inline void getVec4f(FlagHandle handle, sead::Vector4f* value, s32 idx, bool debug = false) {
    auto* mgr = Manager::instance();
    if (mgr)
        mgr->getVec4f(handle, value, idx, debug);
}

#define GDT_SET_FLAG_(NAME, T)                                                                     \
    inline void NAME(T value, FlagHandle handle, bool debug = false) {                             \
        auto* mgr = Manager::instance();                                                           \
        if (mgr)                                                                                   \
            mgr->NAME(value, handle, debug);                                                       \
    }                                                                                              \
    inline void NAME(T value, FlagHandle handle, s32 sub_idx, bool debug = false) {                \
        auto* mgr = Manager::instance();                                                           \
        if (mgr)                                                                                   \
            mgr->NAME(value, handle, debug, sub_idx);                                              \
    }

#define GDT_SET_FLAG_STR_(NAME, T)                                                                 \
    inline void NAME(T value, FlagHandle handle, bool debug = false) {                             \
        auto* mgr = Manager::instance();                                                           \
        if (mgr)                                                                                   \
            mgr->NAME(value.cstr(), handle, debug);                                                \
    }                                                                                              \
    inline void NAME(T value, FlagHandle handle, s32 sub_idx, bool debug = false) {                \
        auto* mgr = Manager::instance();                                                           \
        if (mgr)                                                                                   \
            mgr->NAME(value.cstr(), handle, debug, sub_idx);                                       \
    }

GDT_SET_FLAG_(setBool, bool)
GDT_SET_FLAG_(setS32, s32)
GDT_SET_FLAG_(setF32, f32)
GDT_SET_FLAG_STR_(setStr, const sead::SafeString&)
GDT_SET_FLAG_STR_(setStr64, const sead::SafeString&)
GDT_SET_FLAG_STR_(setStr256, const sead::SafeString&)
GDT_SET_FLAG_(setVec2f, const sead::Vector2f&)
GDT_SET_FLAG_(setVec3f, const sead::Vector3f&)
GDT_SET_FLAG_(setVec4f, const sead::Vector4f&)

#undef GDT_SET_FLAG_
#undef GDT_SET_FLAG_STR_

}  // namespace ksys::gdt