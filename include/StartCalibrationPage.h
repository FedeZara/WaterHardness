extern PageController* pageController;
extern CalibrationData calData;

Page *startCalibrationPage;

void StartYesBtn_OnClick()
{
    pageController->NavigateTo(2);
}

void StartNoBtn_OnClick()
{
    pageController->NavigateTo(0);
}

void StartCalibrationPage_OnSetup(){
    EEPROM.get(0, calData);

    if(calData.calibrationExists){
        // defining YesBtn
        Button *yesBtn = new Button(40, 30, 240, 75, true);
        yesBtn->BorderColor = ILI9341_DARKGREEN;
        yesBtn->Color = ILI9341_GREEN;
        yesBtn->OnClick = StartYesBtn_OnClick;
        yesBtn->SetFontSize(3);
        yesBtn->SetTextPos(23, 27);
        yesBtn->SetTextColor(ILI9341_DARKGREEN);
        yesBtn->SetText("Yes");

        // defining NoBtn
        Button *noBtn = new Button(40, 135, 240, 75, true);
        noBtn->BorderColor = ILI9341_BLACK;
        noBtn->Color = ILI9341_RED;
        noBtn->OnClick = StartNoBtn_OnClick;
        noBtn->SetFontSize(3);
        noBtn->SetTextPos(23, 27);
        noBtn->SetTextColor(ILI9341_BLACK);
        noBtn->SetText("No");

        startCalibrationPage->SetNumButtons(2);
        startCalibrationPage->AddButton(yesBtn, 0);
        startCalibrationPage->AddButton(noBtn, 1);
    }
    else{
        // defining OkBtn
        Button *okBtn = new Button(40, 135, 240, 75, true);
        okBtn->BorderColor = ILI9341_DARKGREEN;
        okBtn->Color = ILI9341_GREEN;
        okBtn->OnClick = StartYesBtn_OnClick;
        okBtn->SetFontSize(3);
        okBtn->SetTextPos(23, 27);
        okBtn->SetTextColor(ILI9341_DARKGREEN);
        okBtn->SetText("OK");

        startCalibrationPage->SetNumButtons(1);
        startCalibrationPage->AddButton(okBtn, 0);
    }
}

void CreateStartCalibrationPage()
{
    startCalibrationPage = new Page();
    startCalibrationPage->Setup = StartCalibrationPage_OnSetup;

    pageController->AddPage(startCalibrationPage, 1);
}