extern PageController* pageController;
extern CalibrationData calData;

void EndYesBtn_OnClick()
{
    calData.calibrationExists = true;
    EEPROM.put(0, calData);
    pageController->NavigateTo(0);
}

void EndNoBtn_OnClick()
{
    pageController->NavigateTo(1);
}

void CreateEndCalibrationPage()
{
    // defining CalibrationBtn
    Button *yesBtn = new Button(40, 30, 240, 75, true);
    yesBtn->BorderColor = ILI9341_DARKGREEN;
    yesBtn->Color = ILI9341_GREEN;
    yesBtn->OnClick = EndYesBtn_OnClick;
    yesBtn->SetFontSize(3);
    yesBtn->SetTextPos(23, 27);
    yesBtn->SetTextColor(ILI9341_DARKGREEN);
    yesBtn->SetText("Yes");

    // defining MeasurementBtn
    Button *noBtn = new Button(40, 135, 240, 75, true);
    noBtn->BorderColor = ILI9341_BLACK;
    noBtn->Color = ILI9341_RED;
    noBtn->OnClick = EndNoBtn_OnClick;
    noBtn->SetFontSize(3);
    noBtn->SetTextPos(23, 27);
    noBtn->SetTextColor(ILI9341_BLACK);
    noBtn->SetText("No");

    Page *endCalibrationPage = new Page();
    endCalibrationPage->SetNumButtons(2);
    endCalibrationPage->AddButton(yesBtn, 0);
    endCalibrationPage->AddButton(noBtn, 1);

    pageController->AddPage(endCalibrationPage, 3);
}