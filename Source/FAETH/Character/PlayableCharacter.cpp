#include "PlayableCharacter.h"
#include "../Skill/SkillSystemComponent.h"

APlayableCharacter::APlayableCharacter()
{
	SkillSystemComponent = CreateDefaultSubobject<USkillSystemComponent>("SkillSystemComponent");
}

void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (AbilitySystemComponent && InputComponent)
	{
		// Set up the ability input bind info
		FGameplayAbilityInputBinds abilityInputBinds = FGameplayAbilityInputBinds(
			FString("ConfirmInput"),
			FString("CancelInput"),
			FString("EAbilityInputID"),
			static_cast<int32>(EAbilityInputID::Confirm),
			static_cast<int32>(EAbilityInputID::Cancel)
		);

		// Bind input to ASC
		AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent, abilityInputBinds);
	}
}
