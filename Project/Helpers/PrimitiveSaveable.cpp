#include "PrimitiveSaveable.hpp"

Core::uuid Interfaces::Trait<PrimitiveSaveable<int>>::typeId = Core::uuid("bf9dfd80-6587-4ddc-ad62-cf17cde0013c");
Core::uuid Interfaces::Trait<PrimitiveSaveable<long>>::typeId = Core::uuid("0a181c2f-6e0a-4e89-8ea6-6b1cbdc04ce2");
Core::uuid Interfaces::Trait<PrimitiveSaveable<double>>::typeId = Core::uuid("fb327c00-b699-49c5-8a18-2719d28e9673");
Core::uuid Interfaces::Trait<PrimitiveSaveable<Core::String>>::typeId = Core::uuid("49230a9a-9ef1-4735-bd6c-98c34bdfd215");
Core::uuid Interfaces::Trait<PrimitiveSaveable<bool>>::typeId = Core::uuid("23233e28-d8df-4fd0-a716-7f4fe4eda793");
Core::uuid Interfaces::Trait<PrimitiveSaveable<std::vector<long>>>::typeId = Core::uuid("ad5c6af3-2d57-4a66-87a0-e527366b1106");
Core::uuid Interfaces::Trait<PrimitiveSaveable<std::vector<double>>>::typeId = Core::uuid("796fdc19-0216-4624-8e0e-e5248013f7dd");
Core::uuid Interfaces::Trait<PrimitiveSaveable<std::vector<Core::String>>>::typeId = Core::uuid("d9469149-5c04-44b7-9ffe-21cfc4e6ae98");