extern PageController* pageController;
extern Adafruit_TCS34725 tcs;
extern Adafruit_ILI9341* tft;

Button *nextBtn;
Label *redLbl, *blueLbl, *greenLbl, *cLbl, *colorTempLbl, *luxLbl;

uint16_t r, g, b, c, colorTemp, lux;
void TakeMeasure(){
    uint16_t old_r = r;
    
    tcs.getRawData(&r, &g, &b, &c);
    colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
    lux = tcs.calculateLux(r, g, b);

    if(old_r == 0){        
        nextBtn->SetText("Next");
    }
    
    String temp = "Color Temp: " + String(colorTemp, DEC);
    colorTempLbl->SetText(temp + " K ");
    luxLbl->SetText("Lux: " + String(lux, DEC));
    redLbl->SetText("R: " + String(r, DEC));
    blueLbl->SetText("G: " + String(g, DEC));
    greenLbl->SetText("B: " + String(b, DEC));
    cLbl->SetText("C: " + String(c, DEC));

    Serial.print("Color Temp: ");
    Serial.print(colorTemp, DEC);
    Serial.print(" K - ");
    Serial.print("Lux: ");
    Serial.print(lux, DEC);
    Serial.print(" - ");
    Serial.print("R: ");
    Serial.print(r, DEC);
    Serial.print(" ");
    Serial.print("G: ");
    Serial.print(g, DEC);
    Serial.print(" ");
    Serial.print("B: ");
    Serial.print(b, DEC);
    Serial.print(" ");
    Serial.print("C: ");
    Serial.print(c, DEC);
    Serial.print(" ");
    Serial.println(" ");
}

void CalibrationPage_OnSetup(){
    r = 0;
    nextBtn->SetText("Start");
    colorTempLbl->SetText("");
    luxLbl->SetText("");
    redLbl->SetText("");
    greenLbl->SetText("");
    blueLbl->SetText("");
    cLbl->SetText("");
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
    nextBtn = new Button(180, 155, 120, 75, true);
    nextBtn->BorderColor = ILI9341_DARKGREEN;
    nextBtn->Color = ILI9341_GREEN;
    nextBtn->OnClick = NextBtn_OnClick;
    nextBtn->SetFontSize(3);
    nextBtn->SetTextPos(22, 27);
    nextBtn->SetTextColor(ILI9341_DARKGREEN);
    nextBtn->SetText("Start");
    
    // defining Labels
    colorTempLbl = new Label(2, 35, 2);
    colorTempLbl->TextColor = ILI9341_BLACK;

    luxLbl = new Label(2, 51, 2);
    luxLbl->TextColor = ILI9341_GREENYELLOW;

    redLbl = new Label(2, 67, 2);
    redLbl->TextColor = ILI9341_RED;

    greenLbl = new Label(2, 83, 2);
    greenLbl->TextColor = ILI9341_GREEN;

    blueLbl = new Label(2, 99, 2);
    blueLbl->TextColor = ILI9341_BLUE;

    cLbl = new Label(2, 115, 2);
    cLbl->TextColor = ILI9341_BLACK;

    Page* calibrationPage = new Page();
    calibrationPage->SetNumButtons(2);
    calibrationPage->AddButton(backBtn, 0);
    calibrationPage->AddButton(nextBtn, 1);

    calibrationPage->SetNumLabels(6);
    calibrationPage->AddLabel(colorTempLbl, 0);
    calibrationPage->AddLabel(luxLbl, 1);
    calibrationPage->AddLabel(redLbl, 2);
    calibrationPage->AddLabel(greenLbl, 3);
    calibrationPage->AddLabel(blueLbl, 4);
    calibrationPage->AddLabel(cLbl, 5);

    calibrationPage->Setup = CalibrationPage_OnSetup;
    pageController->AddPage(calibrationPage, 1);
}