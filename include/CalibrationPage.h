extern PageController* pageController;
extern Adafruit_TCS34725 tcs;
extern Adafruit_ILI9341* tft;
extern CalibrationData calData;

Button *nextBtn;
Label *tipLbl;
Label *concLbl;

double currConc;
int count;

void TakeMeasure(){
    if(count == -1){        
        nextBtn->SetText("Calibrate");
        tipLbl->SetText("Insert the phial with the\n hardness written below.");
    }
    else {
        uint16_t r, g, b, c, lux;
        tcs.getRawData(&r, &g, &b, &c);
        lux = tcs.calculateLux(r, g, b);

        calData.data[count] = double(c) / double(lux);
        currConc += 0.24;

        if(count == 15){
            pageController->NavigateTo(3);
            return;
        }
    }
    
    concLbl->SetText(String(currConc) + " F");
    count++;
}

void CalibrationPage_OnSetup(){
    nextBtn->SetText("Start");
    tipLbl->SetText("Press on 'Start' in order to start calibration.");
    concLbl->SetText("");
    currConc = 2.40;
    count = -1;
}

void NextBtn_OnClick(){
    TakeMeasure();
}

void CalibrationPage_BackBtn_OnClick()
{
    pageController->NavigateTo(0);
}

void CreateCalibrationPage()
{
    // defining BackBtn
    Button *backBtn = new Button(2, 2, 60, 30, true);
    backBtn->BorderColor = ILI9341_DARKGREY;
    backBtn->Color = ILI9341_LIGHTGREY;
    backBtn->OnClick = CalibrationPage_BackBtn_OnClick;
    backBtn->SetFontSize(1);
    backBtn->SetTextPos(11, 12);
    backBtn->SetTextColor(ILI9341_DARKGREY);
    backBtn->SetText("<- Back");

    // defining NextBtn
    nextBtn = new Button(110, 155, 190, 75, true);
    nextBtn->BorderColor = ILI9341_DARKGREEN;
    nextBtn->Color = ILI9341_GREEN;
    nextBtn->OnClick = NextBtn_OnClick;
    nextBtn->SetFontSize(3);
    nextBtn->SetTextPos(22, 27);
    nextBtn->SetTextColor(ILI9341_DARKGREEN);
    nextBtn->SetText("Start");
    
    // defining Labels
    tipLbl = new Label(2, 35, 2);
    tipLbl->TextColor = ILI9341_BLACK;

    concLbl = new Label(2, 105, 2);
    concLbl->TextColor = ILI9341_BLACK;

    Page* calibrationPage = new Page();
    calibrationPage->SetNumButtons(2);
    calibrationPage->AddButton(backBtn, 0);
    calibrationPage->AddButton(nextBtn, 1);

    calibrationPage->SetNumLabels(2);
    calibrationPage->AddLabel(tipLbl, 0);
    calibrationPage->AddLabel(concLbl, 1);

    calibrationPage->Setup = CalibrationPage_OnSetup;
    pageController->AddPage(calibrationPage, 2);
}