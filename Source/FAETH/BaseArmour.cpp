#include "BaseArmour.h"

// Sets default values
ABaseArmour::ABaseArmour()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseArmour::BeginPlay()
{
	Super::BeginPlay();

	EquipmentAttributeSet->Defence = Defence;
}

// Called every frame
void ABaseArmour::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
