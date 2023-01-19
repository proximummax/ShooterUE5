#pragma once

class STUtils
{
public:
	template <typename T>
	static T* GetSTPlayerComponent(AActor* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());

		return Cast<T>(Component);
	}
};
