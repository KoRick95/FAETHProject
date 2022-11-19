#include "FaethCharacter.h"
#include "../FaethAbility.h"
#include "../FaethAbilitySystemComponent.h"
#include "../FaethObjectTypes.h"

// Sets default values
AFaethCharacter::AFaethCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UFaethAbilitySystemComponent>("AbilitySystemComponent");
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
	for (TSubclassOf<UFaethAbility> ability : InitialAbilityClasses)
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
	else if (InitAttributesEffectClasses.Num() == 0)
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

	for (int i = 0; i < InitAttributesEffectClasses.Num(); ++i)
	{
		if (!InitAttributesEffectClasses[i])
			continue;

		// Create a new GE object from the class
		UGameplayEffect* GEInitAttributes = NewObject<UGameplayEffect>(GetTransientPackage(), InitAttributesEffectClasses[i]);

		// Apply gameplay effect to initialise attributes
		AbilitySystemComponent->ApplyGameplayEffectToSelf(GEInitAttributes, CharacterAttributeSet->GetLevel(), GEContext);

		bHasInitialisedAttributes = true;
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

void AFaethCharacter::GainAbility(TSubclassOf<UFaethAbility> Ability)
{
	if (AbilitySystemComponent && Ability && HasAuthority())
	{
		// To do: Pass the ability level dynamically.
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
	}
}

void AFaethCharacter::LoseAbility(TSubclassOf<UFaethAbility> Ability)
{
	if (AbilitySystemComponent && Ability && HasAuthority())
	{
		FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(Ability);

		if (AbilitySpec)
		{
			AbilitySystemComponent->ClearAbility(AbilitySpec->Handle);
		}
	}
}

void AFaethCharacter::GainEffect(TSubclassOf<UGameplayEffect> Effect)
{
	if (AbilitySystemComponent && Effect && HasAuthority())
	{
		// To do: Pass the effect level dynamically.
		AbilitySystemComponent->ApplyGameplayEffectToSelf(NewObject<UGameplayEffect>(Effect), 1, AbilitySystemComponent->MakeEffectContext());
	}
}

void AFaethCharacter::LoseEffect(TSubclassOf<UGameplayEffect> Effect)
{
	if (AbilitySystemComponent && Effect && HasAuthority())
	{
		AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(Effect, AbilitySystemComponent);
	}
}

void AFaethCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterAttributeSet->OnHealthChange.AddDynamic(this, &AFaethCharacter::NativeOnHealthChange);
	CharacterAttributeSet->OnHealthChange.AddDynamic(this, &AFaethCharacter::BP_OnHealthChange);
	CharacterAttributeSet->OnManaChange.AddDynamic(this, &AFaethCharacter::BP_OnManaChange);
	CharacterAttributeSet->OnStaminaChange.AddDynamic(this, &AFaethCharacter::BP_OnStaminaChange);

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

void AFaethCharacter::NativeOnHealthChange(float Health, float MaxHealth)
{
	if (bHasInitialisedAttributes && !bIsDead && FMath::IsNearlyZero(Health, 0.1f))
	{
		bIsDead = true;
		BP_OnDeath();
	}
}
