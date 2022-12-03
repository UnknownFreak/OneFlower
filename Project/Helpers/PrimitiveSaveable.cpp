#include "PrimitiveSaveable.hpp"

of::common::uuid of::file::archive::Trait<PrimitiveSaveable<int>>::typeId = of::common::uuid("bf9dfd80-6587-4ddc-ad62-cf17cde0013c");
of::common::uuid of::file::archive::Trait<PrimitiveSaveable<long>>::typeId = of::common::uuid("0a181c2f-6e0a-4e89-8ea6-6b1cbdc04ce2");
of::common::uuid of::file::archive::Trait<PrimitiveSaveable<double>>::typeId = of::common::uuid("fb327c00-b699-49c5-8a18-2719d28e9673");
of::common::uuid of::file::archive::Trait<PrimitiveSaveable<of::common::String>>::typeId = of::common::uuid("49230a9a-9ef1-4735-bd6c-98c34bdfd215");
of::common::uuid of::file::archive::Trait<PrimitiveSaveable<bool>>::typeId = of::common::uuid("23233e28-d8df-4fd0-a716-7f4fe4eda793");
of::common::uuid of::file::archive::Trait<PrimitiveSaveable<std::vector<long>>>::typeId = of::common::uuid("ad5c6af3-2d57-4a66-87a0-e527366b1106");
of::common::uuid of::file::archive::Trait<PrimitiveSaveable<std::vector<double>>>::typeId = of::common::uuid("796fdc19-0216-4624-8e0e-e5248013f7dd");
of::common::uuid of::file::archive::Trait<PrimitiveSaveable<std::vector<of::common::String>>>::typeId = of::common::uuid("d9469149-5c04-44b7-9ffe-21cfc4e6ae98");