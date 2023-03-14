// MIT

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utility/ALSXTStructs.h"
#include "ALSXTCharacter.h"
#include "AlsCharacter.h"
#include "Chaos/ChaosEngineInterface.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h" 
#include "Settings/ALSXTImpactReactionSettings.h"
#include "State/ALSXTImpactReactionState.h" 
#include "Components/TimelineComponent.h"
#include "ALSXTImpactReactionComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Physics), meta=(BlueprintSpawnableComponent) )
class ALSXT_API UALSXTImpactReactionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UALSXTImpactReactionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category = "ALS|Als Character", Meta = (AllowPrivateAccess))
	AALSXTCharacter* Character{ Cast<AALSXTCharacter>(GetOwner()) };

	AAlsCharacter* AlsCharacter{ Cast<AAlsCharacter>(GetOwner()) };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", Meta = (AllowPrivateAccess))
	FALSXTGeneralImpactReactionSettings ImpactReactionSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", Meta = (AllowPrivateAccess))
	FALSXTImpactReactionParameters ImpactReactionParameters;

	void ObstacleTrace();

	/*Curve float reference*/
	UPROPERTY(EditAnywhere, Category = "Impact Reaction Timeline")
	UCurveFloat* CurveFloat;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Vitals")
	float GetHealth();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Vitals")
	float GetStamina();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "ALS|Movement System")
	bool CanReact();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "ALS|Movement System")
	bool ShouldPerformResponse();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "ALS|Als Character")
	UNiagaraSystem* GetImpactReactionParticle(FDoubleHitResult Hit);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "ALS|Als Character")
	TSubclassOf<AActor> GetImpactReactionParticleActor(FDoubleHitResult Hit);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "ALS|Als Character")
	USoundBase* GetImpactReactionSound(FDoubleHitResult Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State|Als Character", Transient, Meta = (AllowPrivateAccess))
	FALSXTImpactReactionState ImpactReactionState;

	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	void ImpactReaction(FDoubleHitResult Hit);

	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	void AttackReaction(FAttackDoubleHitResult Hit);

	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	void SyncedAttackReaction(FAttackDoubleHitResult Hit, const FGameplayTag& Overlay, const FGameplayTag& AttackType, const FGameplayTag& Stance, const FGameplayTag& Strength, const FGameplayTag& AttackMode, int Index);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	UAnimMontage* SelectAttackReactionMontage(FAttackDoubleHitResult Hit);

	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	UAnimMontage* SelectImpactReactionMontage(FDoubleHitResult Hit);

	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	FSyncedAttackAnimation GetSyncedMontage(const FGameplayTag& Overlay, FAttackDoubleHitResult Hit, const FGameplayTag& AttackType, const FGameplayTag& Stance, const FGameplayTag& Strength, const FGameplayTag& AttackMode, int Index);

	UFUNCTION(BlueprintNativeEvent, Category = "ALS|Als Character")
	UAnimMontage* SelectResponseMontage(FAttackDoubleHitResult Hit);

	UFUNCTION(BlueprintNativeEvent, Category = "Als Character")
	UALSXTImpactReactionSettings* SelectImpactReactionSettings(const FGameplayTag& Location);

	UFUNCTION(BlueprintNativeEvent, Category = "Als Character")
	UALSXTAttackReactionSettings* SelectAttackReactionSettings(const FGameplayTag& Location);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "ALS|Als Character")
	void OnAttackReactionStarted(FAttackDoubleHitResult Hit);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "ALS|Als Character")
	void OnAttackReactionFinished(FAttackDoubleHitResult Hit, const FGameplayTag& AttackMode);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "ALS|Als Character")
	void OnImpactReactionStarted(FDoubleHitResult Hit);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "ALS|Als Character")
	void OnImpactReactionFinished(FDoubleHitResult Hit);

	// Desired UnarmedAttack

private:
	FTimeline ImpactTimeline;

	FTimerHandle TimeSinceLastRecoveryTimerHandle;
	float TimeSinceLastRecovery;

	FTimerHandle TimeSinceLastResponseTimerHandle;
	float TimeSinceLastResponse;

	UFUNCTION()
	void ImpactTimelineUpdate(float Value);

	bool IsImpactReactionAllowedToStart(const UAnimMontage* Montage) const;

	void StartAttackReaction(FAttackDoubleHitResult Hit);

	void StartSyncedAttackReaction(FAttackDoubleHitResult Hit);
	
	void StartImpactReaction(FDoubleHitResult Hit);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAttackReaction(FAttackDoubleHitResult Hit);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastAttackReaction(FAttackDoubleHitResult Hit);

	UFUNCTION(Server, Reliable)
	void ServerImpactReaction(FDoubleHitResult Hit);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastImpactReaction(FDoubleHitResult Hit);

	UFUNCTION(Server, Reliable)
	void ServerStartImpactReaction(FDoubleHitResult Hit, UAnimMontage* Montage, TSubclassOf<AActor> ParticleActor, UNiagaraSystem* Particle, USoundBase* Audio);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastStartImpactReaction(FDoubleHitResult Hit, UAnimMontage* Montage, TSubclassOf<AActor> ParticleActor, UNiagaraSystem* Particle, USoundBase* Audio);

	void StartImpactReactionImplementation(FDoubleHitResult Hit, UAnimMontage* Montage, TSubclassOf<AActor> ParticleActor, UNiagaraSystem* Particle, USoundBase* Audio);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSpawnParticleActor(FDoubleHitResult Hit, TSubclassOf<AActor> ParticleActor);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSpawnParticleActor(FDoubleHitResult Hit, TSubclassOf<AActor> ParticleActor);

	void SpawnParticleActorImplementation(FDoubleHitResult Hit, TSubclassOf<AActor> ParticleActor);

	void RefreshImpactReaction(float DeltaTime);

	void RefreshImpactReactionPhysics(float DeltaTime);

public:
	UFUNCTION(BlueprintCallable, Category = "ALS|Als Character")
	void StopImpactReaction();

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Als Character")
	void OnImpactReactionEnded();

};
