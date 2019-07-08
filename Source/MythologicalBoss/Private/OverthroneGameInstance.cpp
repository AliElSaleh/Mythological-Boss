// Copyright Overthrone Studios 2019

#include "OverthroneGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"

UOverthroneGameInstance::UOverthroneGameInstance()
{
	MasterSoundClass = Cast<USoundClass>(StaticLoadObject(USoundClass::StaticClass(), nullptr, TEXT("SoundClass'/Game/Sounds/Classes/MasterSoundClass.MasterSoundClass'")));
	MusicSoundClass = Cast<USoundClass>(StaticLoadObject(USoundClass::StaticClass(), nullptr, TEXT("SoundClass'/Game/Sounds/Classes/MusicSoundClass.MusicSoundClass'")));
	SFXSoundClass = Cast<USoundClass>(StaticLoadObject(USoundClass::StaticClass(), nullptr, TEXT("SoundClass'/Game/Sounds/Classes/SFXSoundClass.SFXSoundClass'")));
	UISoundClass = Cast<USoundClass>(StaticLoadObject(USoundClass::StaticClass(), nullptr, TEXT("SoundClass'/Game/Sounds/Classes/UISoundClass.UISoundClass'")));
	EnvironmentSoundClass = Cast<USoundClass>(StaticLoadObject(USoundClass::StaticClass(), nullptr, TEXT("SoundClass'/Game/Sounds/Classes/EnvironmentSoundClass.EnvironmentSoundClass'")));

	MasterMix = Cast<USoundMix>(StaticLoadObject(USoundMix::StaticClass(), nullptr, TEXT("SoundMix'/Game/Sounds/Mixes/MasterSoundMix.MasterSoundMix'")));
}

void UOverthroneGameInstance::OnStart()
{
	UGameplayStatics::SetBaseSoundMix(this, MasterMix);
}

void UOverthroneGameInstance::ChangeMasterVolume(const float SliderValue)
{
	MasterVolume = int32(FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(float(0), float(100)), SliderValue));

	UGameplayStatics::SetSoundMixClassOverride(this, MasterMix, MasterSoundClass, SliderValue);
}

void UOverthroneGameInstance::ChangeMusicVolume(const float SliderValue)
{
	MusicVolume = int32(FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(float(0), float(100)), SliderValue));

	UGameplayStatics::SetSoundMixClassOverride(this, MasterMix, MusicSoundClass, SliderValue);
}

void UOverthroneGameInstance::ChangeSFXVolume(const float SliderValue)
{
	SFXVolume = int32(FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(float(0), float(100)), SliderValue));

	UGameplayStatics::SetSoundMixClassOverride(this, MasterMix, SFXSoundClass, SliderValue);
}

void UOverthroneGameInstance::ChangeUIVolume(const float SliderValue)
{
	UIVolume = int32(FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(float(0), float(100)), SliderValue));

	UGameplayStatics::SetSoundMixClassOverride(this, MasterMix, UISoundClass, SliderValue);
}

void UOverthroneGameInstance::ChangeEnvironmentVolume(const float SliderValue)
{
	EnvironmentVolume = int32(FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 1.0f), FVector2D(float(0), float(100)), SliderValue));

	UGameplayStatics::SetSoundMixClassOverride(this, MasterMix, EnvironmentSoundClass, SliderValue);
}
