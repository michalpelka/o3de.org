

#include <RecastNavigationModuleInterface.h>
#include <RecastNavigationSystemComponent.h>

namespace RecastNavigation
{
    class RecastNavigationModule
        : public RecastNavigationModuleInterface
    {
    public:
        AZ_RTTI(RecastNavigationModule, "{a8fb0082-78ab-4ca6-8f63-68c98f1a6a6d}", RecastNavigationModuleInterface);
        AZ_CLASS_ALLOCATOR(RecastNavigationModule, AZ::SystemAllocator, 0);
    };
}// namespace RecastNavigation

AZ_DECLARE_MODULE_CLASS(Gem_RecastNavigation, RecastNavigation::RecastNavigationModule)
