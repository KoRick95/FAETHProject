#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "MainCharacter.generated.h"

class UCharacterAttributeSet;

UCLASS()
class FAETH_API AMainCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCharacterAttributeSet* AttributeSet;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION()
	void OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION()
	void OnManaChanged(float Mana, float MaxMana);

	UFUNCTION()
	void OnStaminaChanged(float Stamina, float MaxStamina);

	UFUNCTION(BlueprintCallable)
	void GainAbility(TSubclassOf<UGameplayAbility> Ability);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHealthChanged"))
	void BP_OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnManaChanged"))
	void BP_OnManaChanged(float Mana, float MaxMana);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnStaminaChanged"))
	void BP_OnStaminaChanged(float Stamina, float MaxStamina);


	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Death"))
		void BP_Death();

protected:
	bool bIsDead;
};
