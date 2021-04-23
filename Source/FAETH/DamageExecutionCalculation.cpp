#include "DamageExecutionCalculation.h"
#include "CharacterAttributeSet.h"

struct DamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defence)

	DamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSet, Strength, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSet, Health, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UCharacterAttributeSet, Defence, Target, true);
	}
};

static DamageStatics& GetDamageStatics()
{
	static DamageStatics DamageStaticsVar;
	return DamageStaticsVar;
}

UDamageExecutionCalculation::UDamageExecutionCalculation()
{
	RelevantAttributesToCapture.Add(GetDamageStatics().StrengthDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().DefenceDef);
}

void UDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float StrengthMagnitude = 0.0f;
	float DefenceMagnitude = 0.0f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().StrengthDef, FAggregatorEvaluateParameters(), StrengthMagnitude);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().DefenceDef, FAggregatorEvaluateParameters(), DefenceMagnitude);

	float FinalDamage = StrengthMagnitude - DefenceMagnitude;
	FinalDamage = FMath::Clamp(FinalDamage, 0.0f, FinalDamage);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageStatics().HealthProperty, EGameplayModOp::Additive, -FinalDamage));
}
