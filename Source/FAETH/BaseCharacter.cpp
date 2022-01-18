#include "BaseCharacter.h"
#include "FaethObjectTypes.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	CharacterAttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>("CharacterAttributeSet");
	bIsDead = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CharacterAttributeSet->OnHealthChange.AddDynamic(this, &ABaseCharacter::OnHealthChanged);
	CharacterAttributeSet->OnManaChange.AddDynamic(this, &ABaseCharacter::OnManaChanged);
	CharacterAttributeSet->OnStaminaChange.AddDynamic(this, &ABaseCharacter::OnStaminaChanged);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent,
	//	FGameplayAbilityInputBinds(FString("ConfirmTarget"), FString("CancelTarget"), FString("AbilityInputID"), static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel)));
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::OnHealthChanged(float Health, float MaxHealth)
{
	if (Health <= 0.0f && !bIsDead)
	{
		bIsDead = true;
		BP_Death();
	}
	BP_OnHealthChanged(Health, MaxHealth);
}

void ABaseCharacter::OnManaChanged(float Mana, float MaxMana)
{
	BP_OnManaChanged(Mana, MaxMana);
}

void ABaseCharacter::OnStaminaChanged(float Stamina, float MaxStamina)
{
	BP_OnStaminaChanged(Stamina, MaxStamina);
}

void ABaseCharacter::OnStaggerChanged(float Stagger, float MaxStagger)
{
	BP_OnStaggerChanged(Stagger, MaxStagger);
}

void ABaseCharacter::InitBaseAttributes()
{
	CharacterAttributeSet->InitHealth(BaseHealth);
	CharacterAttributeSet->InitMana(BaseMana);
	CharacterAttributeSet->InitStamina(BaseStamina);
	CharacterAttributeSet->InitStrength(BaseStrength);
	CharacterAttributeSet->InitDexterity(BaseDexterity);
	CharacterAttributeSet->InitIntelligence(BaseIntelligence);
	CharacterAttributeSet->InitAgility(BaseAgility);
	CharacterAttributeSet->InitDefence(BaseDefence);
	CharacterAttributeSet->InitResistance(BaseResistance);
	CharacterAttributeSet->InitPhysicalAttack(BasePhysicalAttack);
	CharacterAttributeSet->InitMagicAttack(BaseMagicAttack);
	CharacterAttributeSet->InitAttackSpeed(BaseAttackSpeed);
	CharacterAttributeSet->InitHealthRegen(BaseHealthRegen);
	CharacterAttributeSet->InitManaRegen(BaseManaRegen);
	CharacterAttributeSet->InitStaminaRegen(BaseStaminaRegen);
	CharacterAttributeSet->InitStaggerPower(BaseStaggerPower);
}

void ABaseCharacter::SetHealth(float Value)
{
	CharacterAttributeSet->Health = Value;
}

void ABaseCharacter::SetMaxHealth(float Value)
{
	CharacterAttributeSet->MaxHealth = Value;
}

void ABaseCharacter::SetMana(float Value)
{
	CharacterAttributeSet->Mana = Value;
}

void ABaseCharacter::SetMaxMana(float Value)
{
	CharacterAttributeSet->MaxMana = Value;
}

void ABaseCharacter::SetStamina(float Value)
{
	CharacterAttributeSet->Stamina = Value;
}

void ABaseCharacter::SetMaxStamina(float Value)
{
	CharacterAttributeSet->MaxStamina = Value;
}

void ABaseCharacter::SetStagger(float Value)
{
	CharacterAttributeSet->Stagger = Value;
}

void ABaseCharacter::SetMaxStagger(float Value)
{
	CharacterAttributeSet->MaxStagger = Value;
}

void ABaseCharacter::SetStrength(float Value)
{
	CharacterAttributeSet->Strength = Value;
}

void ABaseCharacter::SetDefence(float Value)
{
	CharacterAttributeSet->Defence = Value;
}

bool ABaseCharacter::GetIsHostile(ABaseCharacter* other)
{
	if (TeamID != other->TeamID)
		return true;
	else
		return false;
}

void ABaseCharacter::GainAbility(TSubclassOf<UGameplayAbility> Ability)
{
	if (AbilitySystemComponent)
	{
		if (HasAuthority() && Ability)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, 0));
		}

		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ABaseCharacter::ApplyGameplayEffectToTarget(const FGameplayEffectSpecHandle& GESpecHandle, const FGameplayAbilityTargetDataHandle& GATargetDataHandle)
{
	for (TSharedPtr<FGameplayAbilityTargetData> Data : GATargetDataHandle.Data)
	{
		Data->ApplyGameplayEffectSpec(*GESpecHandle.Data.Get());
	}
}
