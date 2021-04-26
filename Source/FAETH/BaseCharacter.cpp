#include "BaseCharacter.h"
#include "CharacterAttributeSet.h"
//#include "Components/InputComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>("AttributeSet");
	bIsDead = false;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	AttributeSet->OnHealthChange.AddDynamic(this, &ABaseCharacter::OnHealthChanged);
	AttributeSet->OnManaChange.AddDynamic(this, &ABaseCharacter::OnManaChanged);
	AttributeSet->OnStaminaChange.AddDynamic(this, &ABaseCharacter::OnStaminaChanged);
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

	//PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABaseCharacter::Attack);
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

void ABaseCharacter::SetHealth(float Value)
{
	AttributeSet->Health = Value;
}

void ABaseCharacter::SetMaxHealth(float Value)
{
	AttributeSet->MaxHealth = Value;
}

void ABaseCharacter::SetMana(float Value)
{
	AttributeSet->Mana = Value;
}

void ABaseCharacter::SetMaxMana(float Value)
{
	AttributeSet->MaxMana = Value;
}

void ABaseCharacter::SetStamina(float Value)
{
	AttributeSet->Stamina = Value;
}

void ABaseCharacter::SetMaxStamina(float Value)
{
	AttributeSet->MaxStamina = Value;
}

void ABaseCharacter::SetStagger(float Value)
{
	AttributeSet->Stagger = Value;
}

void ABaseCharacter::SetMaxStagger(float Value)
{
	AttributeSet->MaxStagger = Value;
}

void ABaseCharacter::SetStrength(float Value)
{
	AttributeSet->Strength = Value;
}

void ABaseCharacter::SetDefence(float Value)
{
	AttributeSet->Defence = Value;
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
