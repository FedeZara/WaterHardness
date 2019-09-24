#include "Configuration.h"

extern NavigationController navigationController;
extern LinearRegression model;
extern CalibrationData calData;

class EndCalibrationPage : public Page{
    protected:
        void Setup() override{
            model = LinearRegression(CALIBRATION_POINTS, calData.data);

            SetNumButtons(2);

            buttons[0] = Button(40, 175, 110, 50, true);
            buttons[0].BorderColor = ILI9341_DARKGREEN;
            buttons[0].Color = ILI9341_GREEN;
            buttons[0].SetFontSize(2);
            buttons[0].SetTextPos(40, 17);
            buttons[0].SetTextColor(ILI9341_DARKGREEN);
            buttons[0].SetText(F("Yes"));
            
            buttons[1] = Button(170, 175, 110, 50, true);
            buttons[1].BorderColor = ILI9341_BLACK;
            buttons[1].Color = ILI9341_RED;
            buttons[1].SetFontSize(2);
            buttons[1].SetTextPos(40, 17);
            buttons[1].SetTextColor(ILI9341_BLACK);
            buttons[1].SetText(F("No"));

            SetNumLabels(2);

            labels[0] = Label(12, 30, 2);
            labels[0].TextColor = ILI9341_BLACK;
            labels[0].SetText(F("These are the results of\n the calibration.\n\n Would you like to save\n them?"));

            double m = model.getSlope(), b = model.getIntercept(), rSquared = model.getDetermination();
            m = round(m*100.0) / 100.0;
            b = round(b*100.0) / 100.0;
            rSquared = round(rSquared*1000.0) / 1000.0;

            labels[1] = Label(12, 120, 2);
            labels[1].TextColor = ILI9341_BLUE;
            labels[1].SetText("C = " + String(m, '\002') + " x F + " + String(b, '\002') + "\n\n R2 = " + String(rSquared, '\003'));
        }

        void ExecuteButton(int index) override{
            switch(index){
                case 0:
                    YesBtn_OnClick();
                    break;
                case 1:
                    NoBtn_OnClick();
                    break;
            }
        }

        void YesBtn_OnClick()
        {
            calData.calibrationExists = true;
            EEPROM.put(0, calData);
            navigationController.NavigateTo(0);
        }

        void NoBtn_OnClick()
        {
            navigationController.NavigateTo(1);
        }
};