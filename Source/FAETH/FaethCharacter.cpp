#include "FaethCharacter.h"
#include "FaethObjectTypes.h"

// Sets default values
AFaethCharacter::AFaethCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	CharacterAttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>("CharacterAttributeSet");
	bIsDead = false;
}

UAbilitySystemComponent* AFaethCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AFaethCharacter::InitAbilities()
{
	for (TSubclassOf<UGameplayAbility> ability : InitialAbilityClasses)
	{
		GainAbility(ability);
	}
}

void AFaethCharacter::InitAttributes()
{
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ASC does not exist for %s."), *GetClass()->GetName());
		return;
	}

	if (!InitAttributesEffectClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does not have base attributes to initialise."), *GetClass()->GetName());
	}
	else
	{
		// Create a GE context and set the character as the source object
		FGameplayEffectContextHandle GEContext = AbilitySystemComponent->MakeEffectContext();
		GEContext.AddSourceObject(this);

		// Create a new GE object from the class
		UGameplayEffect* GEInitAttributes = NewObject<UGameplayEffect>(GetTransientPackage(), InitAttributesEffectClass);

		// Apply gameplay effect to initialise attributes
		AbilitySystemComponent->ApplyGameplayEffectToSelf(GEInitAttributes, CharacterAttributeSet->GetLevel(), GEContext);

		return;
	}
}

void AFaethCharacter::SetHealth(float Value)
{
	CharacterAttributeSet->Health = Value;
}

void AFaethCharacter::SetMaxHealth(float Value)
{
	CharacterAttributeSet->MaxHealth = Value;
}

void AFaethCharacter::SetMana(float Value)
{
	CharacterAttributeSet->Mana = Value;
}

void AFaethCharacter::SetMaxMana(float Value)
{
	CharacterAttributeSet->MaxMana = Value;
}

void AFaethCharacter::SetStamina(float Value)
{
	CharacterAttributeSet->Stamina = Value;
}

void AFaethCharacter::SetMaxStamina(float Value)
{
	CharacterAttributeSet->MaxStamina = Value;
}

void AFaethCharacter::SetStagger(float Value)
{
	CharacterAttributeSet->Stagger = Value;
}

void AFaethCharacter::SetMaxStagger(float Value)
{
	CharacterAttributeSet->MaxStagger = Value;
}

void AFaethCharacter::SetStrength(float Value)
{
	CharacterAttributeSet->Strength = Value;
}

void AFaethCharacter::SetDefence(float Value)
{
	CharacterAttributeSet->Defence = Value;
}

bool AFaethCharacter::GetIsHostile(AFaethCharacter* other)
{
	if (TeamID != other->TeamID)
		return true;
	else
		return false;
}

void AFaethCharacter::GainAbility(TSubclassOf<UGameplayAbility> Ability)
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

void AFaethCharacter::OnHealthChanged_Implementation(float Health, float MaxHealth)
{
	if (Health <= 0.0f && !bIsDead)
	{
		bIsDead = true;
		BP_Death();
	}
}

void AFaethCharacter::OnManaChanged_Implementation(float Mana, float MaxMana)
{
}

void AFaethCharacter::OnStaminaChanged_Implementation(float Stamina, float MaxStamina)
{
}

void AFaethCharacter::OnStaggerChanged_Implementation(float Stagger, float MaxStagger)
{
}

void AFaethCharacter::BeginPlay()
{
	Super::BeginPlay();
	CharacterAttributeSet->OnHealthChange.AddDynamic(this, &AFaethCharacter::OnHealthChanged);
	CharacterAttributeSet->OnManaChange.AddDynamic(this, &AFaethCharacter::OnManaChanged);
	CharacterAttributeSet->OnStaminaChange.AddDynamic(this, &AFaethCharacter::OnStaminaChanged);

	InitAttributes();
	InitAbilities();
}

void AFaethCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFaethCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AFaethCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent,
	//	FGameplayAbilityInputBinds(FString("ConfirmTarget"), FString("CancelTarget"), FString("AbilityInputID"), static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel)));
}
