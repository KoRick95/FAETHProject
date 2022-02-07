#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterAttributeSet.h"
#include "FaethCharacter.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseMana = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseStamina = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseStrength = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseDexterity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseIntelligence = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseAgility = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseDefence = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseResistance = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BasePhysicalAttack = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseMagicAttack = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseAttackSpeed = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseHealthRegen = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseManaRegen = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseStaminaRegen = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float BaseStaggerPower = 0;

protected:
	bool bIsDead;

public:
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	void InitBaseAttributes();

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
	void GainAbility(TSubclassOf<UGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectToTarget(const FGameplayEffectSpecHandle& GESpecHandle, const FGameplayAbilityTargetDataHandle& GATargetDataHandle);

	UFUNCTION(BlueprintNativeEvent, Category = "Gameplay")
	void OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION(BlueprintNativeEvent, Category = "Gameplay")
	void OnManaChanged(float Mana, float MaxMana);

	UFUNCTION(BlueprintNativeEvent, Category = "Gameplay")
	void OnStaminaChanged(float Stamina, float MaxStamina);

	UFUNCTION(BlueprintNativeEvent, Category = "Gameplay")
	void OnStaggerChanged(float Stagger, float MaxStagger);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDeath"))
	void BP_Death();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
