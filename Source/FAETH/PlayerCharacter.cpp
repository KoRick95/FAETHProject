#include "PlayerCharacter.h"

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
