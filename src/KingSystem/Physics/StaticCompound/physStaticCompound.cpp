#include "KingSystem/Physics/StaticCompound/physStaticCompound.h"
#include <Havok/Common/Serialize/Util/hkNativePackfileUtils.h>
#include <Havok/Common/Serialize/Util/hkRootLevelContainer.h>
#include <Havok/Physics2012/Utilities/Serialize/hkpPhysicsData.h>
#include "KingSystem/Physics/StaticCompound/physStaticCompoundBodyGroup.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundInfo.h"
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::phys {

// + 1 because body groups are one indexed, with the 0th group acting as a dummy group
constexpr int NumBodyGroups = 16 + 1;

StaticCompound::StaticCompound() = default;

StaticCompound::~StaticCompound() {
    // FIXME
}

void StaticCompound::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* parent_heap) {
    const char* error = nullptr;
    mBuffer = buffer;
    auto result = hkNativePackfileUtils::validatePackfileHeader(mBuffer, &error);
    if (!result.isSuccess())
        util::PrintDebugFmt("%s: invalid packfile: %s", __func__, error);
    mBufferSize = hkNativePackfileUtils::getRequiredBufferSize(mBuffer, int(buffer_size));
    mStaticCompoundInfo = static_cast<const StaticCompoundInfo*>(
        hkNativePackfileUtils::loadInPlace(mBuffer, mBufferSize, nullptr, &error));

    mContainerBuffer = buffer + mStaticCompoundInfo->m_Offset;
    auto result2 = hkNativePackfileUtils::validatePackfileHeader(mContainerBuffer, &error);
    if (!result2.isSuccess())
        util::PrintDebugFmt("%s: invalid physics packfile: %s", __func__, error);
    mContainerBufferSize =
        hkNativePackfileUtils::getRequiredBufferSize(mContainerBuffer, int(buffer_size));
    auto* container = static_cast<hkRootLevelContainer*>(
        hkNativePackfileUtils::loadInPlace(mContainerBuffer, mContainerBufferSize));

    auto* physics_data = container->findObject<hkpPhysicsData>();

    mHeap = util::tryCreateDualHeap(parent_heap);
    if (!mHeap) {
        util::PrintDebugFmt("%s: failed to create dual heap", __func__);
        return;
    }
    mHeap->enableWarning(false);
    auto* heap = mHeap;

    const auto& systems = physics_data->getPhysicsSystems();
    mFieldBodyGroups.allocBufferAssert(NumBodyGroups, heap);
    for (int i = 0, n = mFieldBodyGroups.size(); i < n; ++i)
        mFieldBodyGroups[i].init(*systems[i], &mMtx, this, heap);

    mName = systems[0]->getName();
    mName.trimMatchedString("_0");

    if (mStaticCompoundInfo->m_ActorInfo.getSize() > 0)
        mMapObjects.allocBufferAssert(mStaticCompoundInfo->m_ActorInfo.getSize(), heap);

    mFlags.set(Flag::Initialised);
    mHeap->adjust();
}

void StaticCompound::setMapObject(u32 hash_id, u32 srt_hash, map::Object* object) {
    int idx = mStaticCompoundInfo->getActorIdx(hash_id, srt_hash);
    if (idx < 0 || idx >= mMapObjects.size())
        return;
    mMapObjects[idx] = object;
}

map::Object* StaticCompound::getMapObject(int shape_idx) const {
    auto* info = mStaticCompoundInfo->getShapeInfo(shape_idx);
    if (!info)
        return nullptr;

    const int idx = info->m_ActorInfoIndex;
    if (!mMapObjects.isIndexValid(idx))
        return nullptr;

    return mMapObjects[idx];
}

bool StaticCompound::disableCollision(int actor_idx, bool x) {
    const int start = mStaticCompoundInfo->getShapeInfoStart(actor_idx);
    const int end = mStaticCompoundInfo->getShapeInfoEnd(actor_idx);
    for (int i = start; i <= end; ++i) {
        auto* info = mStaticCompoundInfo->getShapeInfo(i);
        if (!info || info->m_ActorInfoIndex < 0)
            continue;

        const auto group = info->m_BodyGroup;
        const auto type = static_cast<BodyLayerType>(info->m_BodyLayerType);
        const auto instance_id = info->m_InstanceId;

        mFieldBodyGroups[group].disableCollision(type, instance_id, x);
    }
    return true;
}

BodyGroup* StaticCompound::getFieldBodyGroup(int idx) {
    return &mFieldBodyGroups[idx];
}

bool StaticCompound::hasFieldBodyGroup(BodyGroup* group) const {
    for (int i = 0, n = mFieldBodyGroups.size(); i < n; ++i) {
        if (&mFieldBodyGroups[i] == group)
            return true;
    }
    return false;
}

}  // namespace ksys::phys
