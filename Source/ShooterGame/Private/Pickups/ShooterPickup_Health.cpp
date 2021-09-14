// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "Pickups/ShooterPickup_Health.h"
#include "OnlineSubsystemUtils.h"
#include "MyAbilitySystemComponent.h"

AShooterPickup_Health::AShooterPickup_Health(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

bool AShooterPickup_Health::CanBePickedUp(class AShooterCharacter* TestPawn) const
{
	return TestPawn && (TestPawn->GetHealth() < TestPawn->GetMaxHealth());
}

void AShooterPickup_Health::GivePickupTo(class AShooterCharacter* Pawn)
{
	if(EffectToApply == nullptr) return;
	
	if (IsValid(Pawn))
	{
		if (Pawn->GetAbilitySystemComponent())
		{
			Pawn->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(EffectToApply.GetDefaultObject(),1.f,FGameplayEffectContextHandle());
		}
	}
}
