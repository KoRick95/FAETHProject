#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterAttributeSet.h"
#include "BaseCharacter.generated.h"

UCLASS()
class FAETH_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

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

	UFUNCTION()
	void OnStaggerChanged(float Stagger, float MaxStagger);

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
	bool GetIsHostile(ABaseCharacter* other);

	UFUNCTION(BlueprintCallable)
	void GainAbility(TSubclassOf<UGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectToTarget(const FGameplayEffectSpecHandle& GESpecHandle, const FGameplayAbilityTargetDataHandle& GATargetDataHandle);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHealthChanged"))
	void BP_OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnManaChanged"))
	void BP_OnManaChanged(float Mana, float MaxMana);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnStaminaChanged"))
	void BP_OnStaminaChanged(float Stamina, float MaxStamina);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnStaggerChanged"))
	void BP_OnStaggerChanged(float Stagger, float MaxStagger);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDeath"))
	void BP_Death();

protected:
	bool bIsDead;
};
