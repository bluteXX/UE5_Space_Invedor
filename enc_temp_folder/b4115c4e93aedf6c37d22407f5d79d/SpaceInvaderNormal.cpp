#include "SpaceInvaderNormal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

void ASpaceInvaderNormal::GameOver()
{
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		PC->DisableInput(PC);

		
		APawn* PlayerPawn = PC->GetPawn();
		if (PlayerPawn)
		{
			PlayerPawn->SetActorHiddenInGame(true);
			PlayerPawn->SetActorEnableCollision(false);
		}
	}

	
	OnGameOverUI();
}