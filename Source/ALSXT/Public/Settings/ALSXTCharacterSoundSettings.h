#pragma once

#include "Utility/ALSXTStructs.h"
#include "Engine/DataAsset.h"
#include "Engine/EngineTypes.h"
#include "ALSXTCharacterSoundSettings.generated.h"

USTRUCT(BlueprintType)
struct ALSXT_API FALSXTCharacterSoundParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	FGameplayTag Location{FGameplayTag::EmptyTag};
};

UCLASS(Blueprintable, BlueprintType)
class ALSXT_API UALSXTCharacterSoundSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds|Movement", Meta = (ForceInlineRow, TitleProperty = "{Sounds}"))
	TMap<TEnumAsByte<EPhysicalSurface>, FALSXTCharacterMovementSounds> MovementSounds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds|Movement", Meta = (ForceInlineRow, TitleProperty = "{Sounds}", ToolTip = "A second Movement Sound Layer for Accents only"))
	TMap<TEnumAsByte<EPhysicalSurface>, FALSXTCharacterMovementSounds> MovementAccentSounds;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds", Meta = (TitleProperty = "{Strength} {Stamina} {Sound}", AllowPrivateAccess))
	TArray<FALSXTCharacterActionSound> ActionSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds", Meta = (TitleProperty = "{Strength} {Stamina} {Sound}", AllowPrivateAccess))
	TArray<FALSXTCharacterActionSound> AttackSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds", Meta = (TitleProperty = "{Form} {Damage} {Sound}", AllowPrivateAccess))
	TArray<FALSXTCharacterDamageSound> DamageSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds", Meta = (TitleProperty = "{Form} {Damage} {Sound}", AllowPrivateAccess))
	TArray<FALSXTCharacterDamageSound> DeathSounds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (TitleProperty = "{MotionSoundArea}", ToolTip = "Set where to get Surface Types to use for each Movement Sound"))
	TArray<FMotionSoundAreaMap> SoundSourcesForMotions;
};

UCLASS(Blueprintable, BlueprintType)
class ALSXT_API UALSXTWeaponSoundSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds", Meta = (Categories = "Als.Weapon", ForceInlineRow))
	TArray<FALSXTWeaponMovementSound> WeaponMovementSounds;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds", Meta = (Categories = "Als.Weapon", ForceInlineRow))
	TArray<FALSXTWeaponActionSound> WeaponActionSounds;
	
};

USTRUCT(BlueprintType)
struct ALSXT_API FALSXTGeneralCharacterSoundSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableMovementSounds{ true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableActionSounds{ true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableAttackSounds{ true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableDamageSounds{ true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableDeathSounds{ true };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebugMode{ false };

};