#pragma once // ȷ��ͷ�ļ�ֻ������һ��

#include "CoreMinimal.h" // ������С����ͷ�ļ�
#include "InputActionValue.h" // �������붯��ֵ���ͷ�ļ�
#include "GameFramework/PlayerController.h" // ������ҿ���������ͷ�ļ�
#include "RpgPlayerController.generated.h" // �������ɱ�׼�������

class UInputMappingContext; // ǰ������������ͷ�ļ�����
class UInputAction; // ǰ���������붯����

UCLASS() // ����һ���µ�UClass
class RPGGAME_API ARpgPlayerController : public APlayerController // ������̳���APlayerController
{
	GENERATED_BODY() // �꣬����֧�������ڲ��ķ�������л�����

protected:
	virtual void BeginPlay() override; // ��д�����BeginPlay����
	virtual void SetupInputComponent() override; // ��д�����SetupInputComponent����

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> RpgContext; // ���ڱ༭���б༭������ӳ��������

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction; // ���ڱ༭���б༭���ƶ�����

	void Move(const FInputActionValue& InputActionValue); // �ƶ��������������붯��ֵ
};
