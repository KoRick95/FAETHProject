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

void ABaseEquipment::InitAttributes()
{
	EquipmentAttributeSet->InitHealth(BaseHealth);
	EquipmentAttributeSet->InitMana(BaseMana);
	EquipmentAttributeSet->InitStamina(BaseStamina);
	EquipmentAttributeSet->InitStrength(BaseStrength);
}

void ABaseEquipment::AddStatsToCharacter(ABaseCharacter* Character)
{
	UCharacterAttributeSet* CharAttribSet = Character->CharacterAttributeSet;

	CharAttribSet->SetMaxHealth(CharAttribSet->MaxHealth.GetBaseValue() + EquipmentAttributeSet->Health.GetBaseValue());
	CharAttribSet->SetMaxMana(CharAttribSet->MaxMana.GetBaseValue() + EquipmentAttributeSet->Mana.GetBaseValue());
	CharAttribSet->SetMaxStamina(CharAttribSet->MaxStamina.GetBaseValue() + EquipmentAttributeSet->Stamina.GetBaseValue());
	CharAttribSet->SetStrength(CharAttribSet->Strength.GetBaseValue() + EquipmentAttributeSet->Strength.GetBaseValue());
}
