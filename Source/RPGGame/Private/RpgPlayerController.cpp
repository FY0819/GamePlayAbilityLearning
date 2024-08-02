#include "RpgPlayerController.h" // ������Ӧ��ͷ�ļ�
#include <EnhancedInputSubsystems.h> // ������ǿ������ϵͳͷ�ļ�
#include <EnhancedInputComponent.h> // ������ǿ�������ͷ�ļ�

void ARpgPlayerController::BeginPlay()
{
    Super::BeginPlay(); // ���ø����BeginPlay����
    check(RpgContext); // ���RpgContext�Ƿ���Ч
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    // �ӱ�����һ�ȡ��ǿ���뱾�������ϵͳ
    Subsystem->AddMappingContext(RpgContext, 0); // ����ϵͳ�������ӳ�������ģ����ȼ�Ϊ0
    bShowMouseCursor = true; // ��ʾ�����

    FInputModeGameAndUI InputModeData; // ��������ģʽ�ṹ
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // �������������Ϊ
    InputModeData.SetHideCursorDuringCapture(false); // ���ò���ʱ�Ƿ����ع��
    SetInputMode(InputModeData); // Ӧ������ģʽ����
}

void ARpgPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent(); // ���ø����SetupInputComponent����
    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
    // ǿ��ת�������������ǿ�������
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARpgPlayerController::Move);
    // ��MoveAction��Move������������ʱ����
}

void ARpgPlayerController::Move(const FInputActionValue& InputActionValue)
{
    const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>(); // �����붯��ֵ�л�ȡ��ά����
    const FRotator Rotation = GetControlRotation(); // ��ȡ����������ת
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f); // ����ֻ����ƫ������ת��

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // ����ǰ������
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // �����ҷ���
    if (APawn* ControlledPawn = GetPawn()) { // ����Ƿ������Pawn
        ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y); // ���ǰ������
        ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X); // �����������
    }
}
