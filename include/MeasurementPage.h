extern PageController* pageController;
extern Adafruit_TCS34725 tcs;
extern Adafruit_ILI9341* tft;

void MeasurementPage_BackBtn_OnClick()
{
    pageController->NavigateTo(0);
}

void CreateMeasurementPage()
{
    // defining BackBtn
    Button *backBtn = new Button(2, 2, 60, 30, true);
    backBtn->BorderColor = ILI9341_DARKGREY;
    backBtn->Color = ILI9341_LIGHTGREY;
    backBtn->OnClick = MeasurementPage_BackBtn_OnClick;
    backBtn->SetFontSize(1);
    backBtn->SetTextPos(11, 12);
    backBtn->SetTextColor(ILI9341_DARKGREY);
    backBtn->SetText("<- Back");

    Page* measurementPage = new Page();
    measurementPage->SetNumButtons(1);
    measurementPage->AddButton(backBtn, 0);
    pageController->AddPage(measurementPage, 2);
}