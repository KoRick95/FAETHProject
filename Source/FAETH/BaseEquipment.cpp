#include "BaseEquipment.h"

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
