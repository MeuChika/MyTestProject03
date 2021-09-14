// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterGame.h"
#include "Pickups/ShooterPickup_Ammo.h"
#include "Weapons/ShooterWeapon.h"
#include "MyAbilitySystemComponent.h"
#include "OnlineSubsystemUtils.h"

AShooterPickup_Ammo::AShooterPickup_Ammo(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AmmoClips = 2;
}

bool AShooterPickup_Ammo::IsForWeapon(UClass* WeaponClass)
{
	return WeaponType->IsChildOf(WeaponClass);
}

bool AShooterPickup_Ammo::CanBePickedUp(AShooterCharacter* TestPawn) const
{
	AShooterWeapon* TestWeapon = (TestPawn ? TestPawn->FindWeapon(WeaponType) : NULL);
	if (bIsActive && IsValid(TestWeapon))
	{
		return TestWeapon->GetCurrentAmmo() < TestWeapon->GetMaxAmmo();
	}

	return false;
}

void AShooterPickup_Ammo::GivePickupTo(class AShooterCharacter* Pawn)
{
	if(EffectToApply == nullptr) return;
	
	AShooterWeapon* Weapon = (Pawn ? Pawn->FindWeapon(WeaponType) : NULL);
	if (IsValid(Weapon))
	{
		if(Weapon->GetAbilitySystemComponent())
		{
			Weapon->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(EffectToApply.GetDefaultObject(),1.f,FGameplayEffectContextHandle());
		}
	}
}
