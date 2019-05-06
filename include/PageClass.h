class Page {
    private:
        bool isVisible = false;

        int numButtons;
        Button** buttons;

        int numLabels;
        Label** labels;

        Adafruit_ILI9341 *tft;
        URTouch *ts;
    public:     
        int BackgroundColor = 0xFFFF;
        
        void (*Loop)();
        void (*Setup)();
        
        void SetNumButtons(int numButtons){
            this->numButtons = numButtons;
            buttons = new Button*[numButtons];
        }

        void SetNumLabels(int numLabels){
            this->numLabels = numLabels;
            labels = new Label*[numLabels];
        }

        void SetTft(Adafruit_ILI9341 *tft){
            this->tft = tft;
            for(int i=0; i<numButtons; i++){
                if(buttons[i] != nullptr)
                    buttons[i]->SetTft(tft);
            }
            for(int i=0; i<numLabels; i++){
                if(labels[i] != nullptr)
                    labels[i]->SetTft(tft);
            }
        }

        void SetTs(URTouch *ts){
            this->ts = ts;
        }

        void AddButton(Button *b, int index){
            buttons[index] = b;
            buttons[index]->SetTft(tft);
        }

        void AddLabel(Label *l, int index){
            labels[index] = l;
            labels[index]->SetTft(tft);
        }

        void OnSetup(){
            if(Setup != nullptr)
                Setup();
        }

        void Show(){
            isVisible = true;

            if(tft == nullptr){
                Serial.println("tft not defined");
                return;
            }
            tft->fillScreen(BackgroundColor);

            OnSetup();

            for(int i=0; i<numLabels; i++){
                labels[i]->Show();
            }
            for(int i=0; i<numButtons; i++){
                buttons[i]->Show();
            }
        }

        void Hide(){
            isVisible = false;
            for(int i=0; i<numLabels; i++){
                labels[i]->Hide();
            }
            for(int i=0; i<numButtons; i++){
                buttons[i]->Hide();
            }
        }

        void OnLoop(){
            if(Loop != nullptr)
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