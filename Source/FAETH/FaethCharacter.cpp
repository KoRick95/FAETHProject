#include "FaethCharacter.h"
#include "FaethGameplayAbility.h"
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
	for (TSubclassOf<UFaethGameplayAbility> ability : InitialAbilityClasses)
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
	else if (!InitAttributesEffectClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s does not have base attributes to initialise."), *GetClass()->GetName());
		return;
	}
	else if (bHasInitialisedAttributes)
	{
		UE_LOG(LogTemp, Display, TEXT("Attributes has already been initialised for %s."), *GetClass()->GetName());
		return;
	}

	// Create a GE context and set the character as the source object
	FGameplayEffectContextHandle GEContext = AbilitySystemComponent->MakeEffectContext();
	GEContext.AddSourceObject(this);

	// Create a new GE object from the class
	UGameplayEffect* GEInitAttributes = NewObject<UGameplayEffect>(GetTransientPackage(), InitAttributesEffectClass);

	// Apply gameplay effect to initialise attributes
	AbilitySystemComponent->ApplyGameplayEffectToSelf(GEInitAttributes, CharacterAttributeSet->GetLevel(), GEContext);

	bHasInitialisedAttributes = true;
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

void AFaethCharacter::GainAbility(TSubclassOf<UFaethGameplayAbility> Ability)
{
	if (AbilitySystemComponent)
	{
		if (HasAuthority() && Ability)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
		}
	}
}

void AFaethCharacter::OnHealthChanged_Implementation(float Health, float MaxHealth)
{
	if (bHasInitialisedAttributes && !bIsDead && Health <= 0.0f)
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

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		InitAttributes();
		InitAbilities();
	}
}

void AFaethCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFaethCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AFaethCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (AbilitySystemComponent && InputComponent)
	{
		// Set up the ability input bind info
		FGameplayAbilityInputBinds abilityInputBinds = FGameplayAbilityInputBinds(
			FString("Confirm"),
			FString("Cancel"),
			FString("EAbilityInputID"),
			static_cast<int32>(EAbilityInputID::Confirm),
			static_cast<int32>(EAbilityInputID::Cancel));

		// Bind input to ASC
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, abilityInputBinds);
	}
}
