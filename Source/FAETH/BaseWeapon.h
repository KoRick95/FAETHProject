#pragma once

#include "CoreMinimal.h"
#include "BaseEquipment.h"
#include "BaseWeapon.generated.h"

UCLASS()
class FAETH_API ABaseWeapon : public ABaseEquipment
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats", meta=(ClampMin="0"))
	float Attack = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
