#include "Configuration.h"

extern NavigationController navigationController;
extern Adafruit_TCS34725 tcs;
extern Adafruit_ILI9341 tft;
extern LinearRegression model;
extern CalibrationData calData;

class MeasurementPage : public Page {
    protected:
        int state;

        void Setup() override{
            EEPROM.get(0, calData);
            model = LinearRegression(CALIBRATION_POINTS, calData.data);

            SetNumButtons(2);

            buttons[0] = Button(2, 2, 60, 30, true);
            buttons[0].BorderColor = ILI9341_DARKGREY;
            buttons[0].Color = ILI9341_LIGHTGREY;
            buttons[0].SetFontSize(1);
            buttons[0].SetTextPos(11, 12);
            buttons[0].SetTextColor(ILI9341_DARKGREY);
            buttons[0].SetText(F("<- Back"));

            buttons[1] = Button(172, 167, 125, 50, true);
            buttons[1].BorderColor = ILI9341_DARKGREEN;
            buttons[1].Color = ILI9341_GREEN;
            buttons[1].SetFontSize(2);
            buttons[1].SetTextPos(22, 17);
            buttons[1].SetTextColor(ILI9341_DARKGREEN);
            buttons[1].SetText(F("Measure"));

            SetNumLabels(2);


            labels[0] = Label(12, 50, 2);
            labels[0].TextColor = ILI9341_BLACK;
            labels[0].SetText(F("Press on 'Measure' in\n order to measure the\n sample."));

            labels[1] = Label(12, 120, 3);
            labels[1].TextColor = ILI9341_BLUE;
            labels[1].SetText("");

            state = 1;
        }

        void ExecuteButton(int index) override{
            switch(index){
                case 0:
                    BackBtn_OnClick();
                    break;
                case 1:
                    NextBtn_OnClick();
                    break;
            }
        }
        
        void BackBtn_OnClick()
        {
            navigationController.NavigateTo(0);
        }

        void NextBtn_OnClick(){
            if(state == 0){
                state = 1;
                labels[0].SetText(F("Press on 'Measure' in\n order to measure the\n sample."));
                labels[1].SetText("");
                buttons[1].SetText(F("Measure"));
            }
            else{
                state = 0;

                uint16_t r, g, b, c;
                tcs.getRawData(&r, &g, &b, &c);
                double hardness = model.calculateX(c) * DILUTION_COEFFICIENT;

                labels[1].SetText(String(hardness) + " F");
                
                labels[0].SetText(F("Press on 'New' and\n insert a new sample."));
                buttons[1].SetText(F("New"));
            }
        }
};
