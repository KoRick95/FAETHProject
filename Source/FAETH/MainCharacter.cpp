#include "MainCharacter.h"
#include "CharacterAttributeSet.h"
#include "Components/InputComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>("AttributeSet");
	bIsDead = false;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	AttributeSet->OnHealthChange.AddDynamic(this, &AMainCharacter::OnHealthChanged);
	AttributeSet->OnManaChange.AddDynamic(this, &AMainCharacter::OnManaChanged);
	AttributeSet->OnStaminaChange.AddDynamic(this, &AMainCharacter::OnStaminaChanged);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainCharacter::Attack);
}

UAbilitySystemComponent* AMainCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMainCharacter::OnHealthChanged(float Health, float MaxHealth)
{
	if (Health <= 0.0f && !bIsDead)
	{
		bIsDead = true;
		BP_Death();
	}
	BP_OnHealthChanged(Health, MaxHealth);
}

void AMainCharacter::OnManaChanged(float Mana, float MaxMana)
{
	BP_OnManaChanged(Mana, MaxMana);
}

void AMainCharacter::OnStaminaChanged(float Stamina, float MaxStamina)
{
	BP_OnStaminaChanged(Stamina, MaxStamina);
}

void AMainCharacter::GainAbility(TSubclassOf<UGameplayAbility> Ability)
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