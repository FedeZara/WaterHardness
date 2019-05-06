extern PageController* pageController;

void CalibrationBtn_OnClick()
{
    pageController->NavigateTo(1);
}

void MeasurementBtn_OnClick()
{
    pageController->NavigateTo(2);
}

void CreateMainPage()
{
    // defining CalibrationBtn
    Button *calibrationBtn = new Button(40, 30, 240, 75, true);
    calibrationBtn->BorderColor = ILI9341_DARKGREEN;
    calibrationBtn->Color = ILI9341_GREEN;
    calibrationBtn->OnClick = CalibrationBtn_OnClick;
    calibrationBtn->SetFontSize(3);
    calibrationBtn->SetTextPos(23, 27);
    calibrationBtn->SetTextColor(ILI9341_DARKGREEN);
    calibrationBtn->SetText("Calibration");

    // defining MeasurementBtn
    Button *measurementBtn = new Button(40, 135, 240, 75, true);
    measurementBtn->BorderColor = ILI9341_DARKCYAN;
    measurementBtn->Color = ILI9341_CYAN;
    measurementBtn->OnClick = MeasurementBtn_OnClick;
    measurementBtn->SetFontSize(3);
    measurementBtn->SetTextPos(23, 27);
    measurementBtn->SetTextColor(ILI9341_DARKCYAN);
    measurementBtn->SetText("Measurement");

    Page *mainPage = new Page();
    mainPage->SetNumButtons(2);
    mainPage->AddButton(calibrationBtn, 0);
    mainPage->AddButton(measurementBtn, 1);



    pageController->AddPage(mainPage, 0);
}