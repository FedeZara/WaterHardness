class Page {
    private:
        int numButtons;
        Button** buttons;
        Adafruit_ILI9341 *tft;
        URTouch *ts;
    public:     
        int BackgroundColor = 0xFFFF;
        
        void (*Loop)();
        
        void SetNumButtons(int numButtons){
            this->numButtons = numButtons;
            buttons = new Button*[numButtons];
        }

        void SetTft(Adafruit_ILI9341 *tft){
            this->tft = tft;
            for(int i=0; i<numButtons; i++){
                if(buttons[i] != nullptr)
                    buttons[i]->SetTft(tft);
            }
        }

        void SetTs(URTouch *ts){
            this->ts = ts;
        }

        void AddButton(Button *b, int index){
            buttons[index] = b;
            buttons[index]->SetTft(tft);
        }

        void Show(){
            tft->fillScreen(BackgroundColor);
            for(int i=0; i<numButtons; i++){
                buttons[i]->Show();
            }
        }

        void OnLoop(){
            Loop();
            if (ts->dataAvailable())
            {
                int x, y;
                ts->read();
                x = ts->getX();
                y = ts->getY();
                Serial.print(x); Serial.print(" "); Serial.println(y);
                for(int i=0; i<numButtons; i++){
                    buttons[i]->ExecuteIfClicked(x, y);
                }
            }
        }
};