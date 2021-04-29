#include "BaseEquipment.h"
#include "BaseCharacter.h"

// Sets default values
ABaseEquipment::ABaseEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	EquipmentAttributeSet = CreateDefaultSubobject<UEquipmentAttributeSet>("EquipmentAttributeSet");
}

// Called when the game starts or when spawned
void ABaseEquipment::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEquipment::AddStatsToCharacter(ABaseCharacter* Character)
{
	UCharacterAttributeSet* CharAttribSet = Character->CharacterAttributeSet;

	CharAttribSet->MaxHealth.SetCurrentValue(CharAttribSet->MaxHealth.GetCurrentValue() + EquipmentAttributeSet->Health.GetCurrentValue());
	CharAttribSet->MaxMana.SetCurrentValue(CharAttribSet->MaxMana.GetCurrentValue() + EquipmentAttributeSet->Mana.GetCurrentValue());
	CharAttribSet->MaxStamina.SetCurrentValue(CharAttribSet->MaxStamina.GetCurrentValue() + EquipmentAttributeSet->Stamina.GetCurrentValue());
	CharAttribSet->Strength.SetCurrentValue(CharAttribSet->Strength.GetCurrentValue() + EquipmentAttributeSet->Attack.GetCurrentValue());
	CharAttribSet->Defence.SetCurrentValue(CharAttribSet->Defence.GetCurrentValue() + EquipmentAttributeSet->Defence.GetCurrentValue());
}
