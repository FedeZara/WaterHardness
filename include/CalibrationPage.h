#include "Configuration.h"

extern NavigationController navigationController;
extern Adafruit_TCS34725 tcs;
extern Adafruit_ILI9341 tft;
extern CalibrationData calData;

class CalibrationPage : public Page{
    protected:
        double currConc;
        int count;
        double offset;

        void Setup() override{
            Page::Setup();

            SetNumButtons(2);

            buttons[0] = Button(2, 2, 60, 30, true);
            buttons[0].BorderColor = ILI9341_DARKGREY;
            buttons[0].Color = ILI9341_LIGHTGREY;
            buttons[0].SetFontSize(1);
            buttons[0].SetTextPos(11, 12);
            buttons[0].SetTextColor(ILI9341_DARKGREY);
            buttons[0].SetText(F("<- Back"));

            buttons[1] = Button(137, 167, 150, 50, true);
            buttons[1].BorderColor = ILI9341_DARKGREEN;
            buttons[1].Color = ILI9341_GREEN;
            buttons[1].SetFontSize(2);
            buttons[1].SetTextPos(22, 17);
            buttons[1].SetTextColor(ILI9341_DARKGREEN);
            buttons[1].SetText(F("Start"));

            SetNumLabels(2);

            labels[0] = Label(12, 50, 2);
            labels[0].TextColor = ILI9341_BLACK;
            labels[0].SetText(F("Press on 'Start' in order to start calibration."));

            labels[1] = Label(12, 182, 3);
            labels[1].TextColor = ILI9341_BLACK;
            labels[1].SetText("");

            currConc = CALIBRATION_START_VALUE;
            offset = (CALIBRATION_END_VALUE - CALIBRATION_START_VALUE) / (double)CALIBRATION_POINTS;
            offset = round(offset*100.0) / 100.0;
            count = -1;
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

        void NextCalibration(){
            if(count == -1){        
                buttons[1].SetText(F("Calibrate"));
                labels[0].SetText(F("Insert the phial with the\n hardness written below.\n\n Then click 'Calibrate'."));
            }
            else {
                uint16_t r, g, b, c;
                tcs.getRawData(&r, &g, &b, &c);

                calData.data[count].x = currConc;
                calData.data[count].y = double(c);

                currConc += offset;

                if(count == CALIBRATION_POINTS-1){
                    navigationController.NavigateTo(3);
                    return;
                }
            }
            
            labels[1].SetText(String(currConc) + " F");
            count++;
        }

        void NextBtn_OnClick(){
            NextCalibration();
        }

        void BackBtn_OnClick()
        {
            navigationController.NavigateTo(1);
        }
};

