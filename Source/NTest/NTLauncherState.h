// Fill out your copyright notice in the Description page of Project Settings.


/*
źü �߻� ��ǲ ó���� ���� FSM ���
���� Ȯ������ ��ǲ ���õ� ���⵵�� �ö� ��� ������ ������ �� �ִ� ���� �־��� ��� �۾� 

*/

#pragma once

#include "NTCommon.h"

class UNTLauncherComponent;

class FNTLauncherState
{
public:
	FNTLauncherState(UNTLauncherComponent* InOwner);
	virtual ~FNTLauncherState() = default;

	virtual void OnEnter() {}
	virtual void OnPrimary_Press() {}
	virtual void OnPrimary_Release() {}
	virtual void OnSecondary_Press() {}
	virtual void OnSecondary_Release() {}
	virtual void TickState(float DeltaTime) {}
	virtual float GetChargingProgress() const { return 0.f; }

protected:
	UNTLauncherComponent* Owner;
};


/////// concrete state classes


class FLS_Default : public FNTLauncherState
{
	using FNTLauncherState::FNTLauncherState;
	virtual void OnPrimary_Press() override;
	virtual void OnSecondary_Press() override;
};


class FLS_PrimaryCharging : public FNTLauncherState
{
public:
	using FNTLauncherState::FNTLauncherState;
	virtual void OnEnter() override;
	virtual void OnPrimary_Release() override;
	virtual void OnSecondary_Press() override;
	virtual void TickState(float DeltaTime) override;
	virtual float GetChargingProgress() const override;

private:
	bool CanFireCluster() const;

public:
	float DefaultLifeTime = 3.f;
	float DefaultClusterTime = 1.f;
	float RemainLifeTime;
	float RemainClusterTime;
};


class FLS_PrimaryCharged : public FNTLauncherState
{
public:
	using FNTLauncherState::FNTLauncherState;
	virtual void OnPrimary_Release() override;
	virtual void OnSecondary_Press() override;
	virtual float GetChargingProgress() const override;
};

class FLS_SecondaryCharging : public FNTLauncherState
{
public:
	using FNTLauncherState::FNTLauncherState;
	virtual void OnPrimary_Press() override;
	virtual void OnSecondary_Release() override;
};
