// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_Sprint.h"
#include "ShooterCharacter.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"

UGA_Sprint::UGA_Sprint()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	FGameplayTag Ability1Tag = FGameplayTag::RequestGameplayTag(FName("Ability.Movement.Sprint"));
	AbilityTags.AddTag(Ability1Tag);
	ActivationOwnedTags.AddTag(Ability1Tag);
	AbilityInputID = EAbilityInput::Sprint;
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Skill")));
}

void UGA_Sprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                 const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (ActorInfo == nullptr && CurrentActorInfo == nullptr) return;

	if (ActorInfo->AvatarActor == nullptr)
	{
		EndAbility(CurrentSpecHandle,CurrentActorInfo, CurrentActivationInfo, true, true);
	}
	else
	{
		SetRunning(true);
	}
}

void UGA_Sprint::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo != nullptr && ActorInfo->AvatarActor != nullptr)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UGA_Sprint::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	SetRunning(false);
}

void UGA_Sprint::SetRunning(bool bRun) const
{
	if (CurrentActorInfo != nullptr)
	{
		if (IsValid(CurrentActorInfo->AvatarActor.Get()))
		{
			AShooterCharacter* ShooterActor = Cast<AShooterCharacter>(CurrentActorInfo->AvatarActor);
			if (IsValid(ShooterActor))
			{
				ShooterActor->SetRunning(bRun, false);
			}
		}
	}
}
