#include "SkillSubsystem.h"
#include "SkillSystemComponent.h"

TArray<USkillSystemComponent*> USkillSubsystem::GetRegisteredSkillComponents()
{
	return RegisteredSkillComponents;
}

FCharacterSkillInfo USkillSubsystem::GetCharacterSkillInfo(FName CharacterId)
{
	// To do: Return saved array of character skills.
	return FCharacterSkillInfo();
}

void USkillSubsystem::RegisterSkillComponent(USkillSystemComponent* NewSkillComponent)
{
	RegisteredSkillComponents.Add(NewSkillComponent);

	// To do: Also ref this subsystem from the component.
}

void USkillSubsystem::OnSkillComponentDestroyed(USkillSystemComponent* SkillComponent)
{
	// To do: Deregister the component and remove from internal array.
}

void USkillSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USkillSubsystem::Deinitialize()
{
	Super::Deinitialize();
}
