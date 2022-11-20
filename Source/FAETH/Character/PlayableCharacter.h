#pragma once

#include "CoreMinimal.h"
#include "FaethCharacter.h"
#include "PlayableCharacter.generated.h"

class USkillSystemComponent;

UCLASS()
class FAETH_API APlayableCharacter : public AFaethCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills")
	USkillSystemComponent* SkillSystemComponent;

public:
	USkillSystemComponent* GetSkillSystemComponent() { return SkillSystemComponent; }

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
