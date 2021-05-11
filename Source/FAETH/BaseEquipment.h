#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "EquipmentAttributeSet.h"
#include "BaseEquipment.generated.h"

UCLASS()
class FAETH_API ABaseEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEquipment();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UEquipmentAttributeSet* EquipmentAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats", meta = (ClampMin = "0"))
	float BaseHealth = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats", meta = (ClampMin = "0"))
	float BaseMana = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats", meta = (ClampMin = "0"))
	float BaseStamina = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats", meta = (ClampMin = "0"))
	float BaseStrength = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitAttributes();

	void AddStatsToCharacter(class ABaseCharacter* Character);
};
