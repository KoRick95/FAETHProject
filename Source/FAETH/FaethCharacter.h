#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterAttributeSet.h"
#include "FaethCharacter.generated.h"

class UFaethGameplayAbility;

UCLASS()
class FAETH_API AFaethCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFaethCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCharacterAttributeSet* CharacterAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TeamID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Initial Attributes")
	TArray<TSubclassOf<UGameplayEffect>> InitAttributesEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Initial Abilities")
	TArray<TSubclassOf<UGameplayAbility>> InitialAbilityClasses;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHasInitialisedAttributes;

	UPROPERTY(BlueprintReadOnly)
	bool bIsDead;

public:
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void InitAbilities();

	UFUNCTION(BlueprintCallable)
	void InitAttributes();

	UFUNCTION(BlueprintCallable)
	void SetHealth(float Value);

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float Value);

	UFUNCTION(BlueprintCallable)
	void SetMana(float Value);

	UFUNCTION(BlueprintCallable)
	void SetMaxMana(float Value);

	UFUNCTION(BlueprintCallable)
	void SetStamina(float Value);

	UFUNCTION(BlueprintCallable)
	void SetMaxStamina(float Value);

	UFUNCTION(BlueprintCallable)
	void SetStagger(float Value);

	UFUNCTION(BlueprintCallable)
	void SetMaxStagger(float Value);

	UFUNCTION(BlueprintCallable)
	void SetStrength(float Value);

	UFUNCTION(BlueprintCallable)
	void SetDefence(float Value);

	UFUNCTION(BlueprintCallable)
	bool GetIsHostile(AFaethCharacter* other);

	UFUNCTION(BlueprintCallable)
	void GainAbility(TSubclassOf<UFaethGameplayAbility> Ability);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay", DisplayName = "OnHealthChanged")
	void BP_OnHealthChange(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay", DisplayName = "OnManaChanged")
	void BP_OnManaChange(float Mana, float MaxMana);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay", DisplayName = "OnStaminaChanged")
	void BP_OnStaminaChange(float Stamina, float MaxStamina);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay", DisplayName = "OnStaggerChanged")
	void BP_OnStaggerChange(float Stagger, float MaxStagger);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDeath"))
	void BP_OnDeath();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()
	void NativeOnHealthChange(float Health, float MaxHealth);
};
