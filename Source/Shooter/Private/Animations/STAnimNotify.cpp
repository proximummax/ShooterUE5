// Shooter, All Rights Reserved


#include "Animations/STAnimNotify.h"

void USTAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotified.Broadcast(MeshComp);
	
	Super::Notify(MeshComp, Animation);
}