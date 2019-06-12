// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	UE_LOG(LogTemp, Warning, TEXT("Grab"));

	UInputComponent* input = GetOwner()->FindComponentByClass<UInputComponent>();

	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	input->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseObject);

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	FVector viewPoint;
	FRotator viewRot;
	
	FVector lineEnd = viewPoint + viewRot.Vector() * 100.f;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(viewPoint, viewRot);

	//UE_LOG(LogTemp, Warning, TEXT("Mi posición es %s y mi rotacion es %s"), *viewPoint.ToString(), *viewRot.ToString());

	DrawDebugLine(GetWorld(), viewPoint, lineEnd, FColor::Red, false);

	FCollisionQueryParams queryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	
	FHitResult hit;

	GetWorld()->LineTraceSingleByChannel(hit, viewPoint, lineEnd, ECollisionChannel::ECC_PhysicsBody, queryParams);


}

void UGrabber::Grab()
{

	FVector viewPoint;
	FRotator viewRot;

	FVector lineEnd = viewPoint + viewRot.Vector() * 100.f;

	auto hit = HitInfo(viewPoint, viewRot);
	auto comp = hit.GetComponent();

	if (hit.GetActor())
	{
		physicsHandle->GrabComponent(comp, NAME_None, hit.GetActor()->GetActorLocation(), true);
	}
}

void UGrabber::ReleaseObject()
{
	if (physicsHandle->GrabbedComponent != nullptr)
	{
		physicsHandle->ReleaseComponent();
	}
}

FHitResult UGrabber::HitInfo(FVector pos, FRotator rot)
{
	FHitResult hit;
	FCollisionQueryParams queryParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByChannel(hit, pos, pos + rot.Vector()*100.f, ECollisionChannel::ECC_PhysicsBody, queryParams);
	return hit;
}

