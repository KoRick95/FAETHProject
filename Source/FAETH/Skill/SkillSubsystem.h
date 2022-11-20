#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SkillSubsystem.generated.h"

class USkill;
class USkillSystemComponent;

USTRUCT(BlueprintType)
struct FCharacterSkillInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FName CharacterId;

	UPROPERTY(BlueprintReadWrite)
	TArray<USkill*> SkillSet;
};

UCLASS()
class FAETH_API USkillSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	

protected:
	TArray<USkillSystemComponent*> RegisteredSkillComponents;

public:
	UFUNCTION(BlueprintPure)
	FCharacterSkillInfo GetCharacterSkillInfo(FName CharacterId);
	
	UFUNCTION(BlueprintPure)
	TArray<USkillSystemComponent*> GetRegisteredSkillComponents();

	UFUNCTION(BlueprintCallable)
	void RegisterSkillComponent(USkillSystemComponent* NewSkillComponent);

	void OnSkillComponentDestroyed(USkillSystemComponent* SkillComponent);

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
