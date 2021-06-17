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

void ABaseEquipment::InitBaseAttributes()
{
	EquipmentAttributeSet->InitHealth(BaseHealth);
	EquipmentAttributeSet->InitMana(BaseMana);
	EquipmentAttributeSet->InitStamina(BaseStamina);
	EquipmentAttributeSet->InitStrength(BaseStrength);
	EquipmentAttributeSet->InitDexterity(BaseDexterity);
	EquipmentAttributeSet->InitIntelligence(BaseIntelligence);
	EquipmentAttributeSet->InitAgility(BaseAgility);
	EquipmentAttributeSet->InitArmour(BaseArmour);
	EquipmentAttributeSet->InitResistance(BaseResistance);
	EquipmentAttributeSet->InitPhysicalAttack(BasePhysicalAttack);
	EquipmentAttributeSet->InitMagicAttack(BaseMagicAttack);
	EquipmentAttributeSet->InitAttackSpeed(BaseAttackSpeed);
	EquipmentAttributeSet->InitHealthRegen(BaseHealthRegen);
	EquipmentAttributeSet->InitManaRegen(BaseManaRegen);
	EquipmentAttributeSet->InitStaminaRegen(BaseStaminaRegen);
	EquipmentAttributeSet->InitStaggerPower(BaseStaggerPower);
}

void ABaseEquipment::AddStatsToCharacter(ABaseCharacter* Character)
{
	UCharacterAttributeSet* CharAttribSet = Character->CharacterAttributeSet;

	CharAttribSet->SetMaxHealth(CharAttribSet->MaxHealth.GetBaseValue() + EquipmentAttributeSet->Health.GetBaseValue());
	CharAttribSet->SetMaxMana(CharAttribSet->MaxMana.GetBaseValue() + EquipmentAttributeSet->Mana.GetBaseValue());
	CharAttribSet->SetMaxStamina(CharAttribSet->MaxStamina.GetBaseValue() + EquipmentAttributeSet->Stamina.GetBaseValue());
	CharAttribSet->SetStrength(CharAttribSet->Strength.GetBaseValue() + EquipmentAttributeSet->Strength.GetBaseValue());
	CharAttribSet->SetDexterity(CharAttribSet->Dexterity.GetBaseValue() + EquipmentAttributeSet->Dexterity.GetBaseValue());
	CharAttribSet->SetIntelligence(CharAttribSet->Intelligence.GetBaseValue() + EquipmentAttributeSet->Intelligence.GetBaseValue());
	CharAttribSet->SetAgility(CharAttribSet->Agility.GetBaseValue() + EquipmentAttributeSet->Agility.GetBaseValue());
	CharAttribSet->SetDefence(CharAttribSet->Defence.GetBaseValue() + EquipmentAttributeSet->Armour.GetBaseValue());
	CharAttribSet->SetResistance(CharAttribSet->Agility.GetBaseValue() + EquipmentAttributeSet->Resistance.GetBaseValue());
	CharAttribSet->SetPhysicalAttack(CharAttribSet->PhysicalAttack.GetBaseValue() + EquipmentAttributeSet->PhysicalAttack.GetBaseValue());
	CharAttribSet->SetMagicAttack(CharAttribSet->MagicAttack.GetBaseValue() + EquipmentAttributeSet->MagicAttack.GetBaseValue());
	CharAttribSet->SetAttackSpeed(CharAttribSet->AttackSpeed.GetBaseValue() + EquipmentAttributeSet->AttackSpeed.GetBaseValue());
	CharAttribSet->SetHealthRegen(CharAttribSet->HealthRegen.GetBaseValue() + EquipmentAttributeSet->HealthRegen.GetBaseValue());
	CharAttribSet->SetManaRegen(CharAttribSet->ManaRegen.GetBaseValue() + EquipmentAttributeSet->ManaRegen.GetBaseValue());
	CharAttribSet->SetStaminaRegen(CharAttribSet->StaminaRegen.GetBaseValue() + EquipmentAttributeSet->StaminaRegen.GetBaseValue());
	CharAttribSet->SetStaggerPower(CharAttribSet->StaggerPower.GetBaseValue() + EquipmentAttributeSet->StaggerPower.GetBaseValue());
}
