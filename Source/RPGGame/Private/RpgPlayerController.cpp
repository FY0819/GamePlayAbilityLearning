#include "RpgPlayerController.h" // 包含对应的头文件
#include <EnhancedInputSubsystems.h> // 引入增强输入子系统头文件
#include <EnhancedInputComponent.h> // 引入增强输入组件头文件

void ARpgPlayerController::BeginPlay()
{
    Super::BeginPlay(); // 调用父类的BeginPlay方法
    check(RpgContext); // 检查RpgContext是否有效
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    // 从本地玩家获取增强输入本地玩家子系统
    Subsystem->AddMappingContext(RpgContext, 0); // 向子系统添加输入映射上下文，优先级为0
    bShowMouseCursor = true; // 显示鼠标光标

    FInputModeGameAndUI InputModeData; // 创建输入模式结构
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 设置鼠标锁定行为
    InputModeData.SetHideCursorDuringCapture(false); // 设置捕获时是否隐藏光标
    SetInputMode(InputModeData); // 应用输入模式设置
}

void ARpgPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent(); // 调用父类的SetupInputComponent方法
    UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
    // 强制转换输入组件到增强输入组件
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARpgPlayerController::Move);
    // 绑定MoveAction到Move函数，当触发时调用
}

void ARpgPlayerController::Move(const FInputActionValue& InputActionValue)
{
    const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>(); // 从输入动作值中获取二维向量
    const FRotator Rotation = GetControlRotation(); // 获取控制器的旋转
    const FRotator YawRotation(0.f, Rotation.Yaw, 0.f); // 创建只包含偏航的旋转器

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // 计算前进方向
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // 计算右方向
    if (APawn* ControlledPawn = GetPawn()) { // 检查是否控制了Pawn
        ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y); // 添加前进输入
        ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X); // 添加右移输入
    }
}
