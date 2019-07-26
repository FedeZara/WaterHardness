extern NavigationController navigationController;

class MainPage : public Page{
    protected: 
        void Setup() override{
            Page::Setup();

            SetNumButtons(2);

            // defining CalibrationBtn
            buttons[0] = Button(40, 30, 240, 75, true);
            buttons[0].BorderColor = ILI9341_DARKGREEN;
            buttons[0].Color = ILI9341_GREEN;
            buttons[0].SetFontSize(3);
            buttons[0].SetTextPos(23, 27);
            buttons[0].SetTextColor(ILI9341_DARKGREEN);
            buttons[0].SetText(F("Calibration"));

            // defining MeasurementBtn
            buttons[1] = Button(40, 135, 240, 75, true);
            buttons[1].BorderColor = ILI9341_DARKCYAN;
            buttons[1].Color = ILI9341_CYAN;
            buttons[1].SetFontSize(3);
            buttons[1].SetTextPos(23, 27);
            buttons[1].SetTextColor(ILI9341_DARKCYAN);
            buttons[1].SetText(F("Measurement"));
        }

        void ExecuteButton(int index) override{
            switch(index){
                case 0:
                    CalibrationBtn_OnClick();
                    break;
                case 1:
                    MeasurementBtn_OnClick();
                    break;
            }
        }

        void CalibrationBtn_OnClick()
        {
            navigationController.NavigateTo(1);
        }

        void MeasurementBtn_OnClick()
        {
            navigationController.NavigateTo(4);
        }
};