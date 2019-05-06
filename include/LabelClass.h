class Label {
    private:
        bool isVisible = false;
        Adafruit_ILI9341 *tft;
        String text;
    public:    
        int X;
        int Y;
        int FontSize;

        int BackgroundColor;
        int TextColor;

        void (*OnClick)();

        Label(int x, int y, int fontSize){
            X = x;
            Y = y;
            TextColor = 0x0000;
            BackgroundColor = 0xFFFF;
            FontSize = fontSize;
        }

        Label() : Label(0, 0, 2){}

        void SetTft(Adafruit_ILI9341 *tft){
            this->tft = tft;
        }

        void SetText(String text){
            if(isVisible){
                int prevTextColor = TextColor;
                TextColor = BackgroundColor;
                ShowText();
                this->text = text;
                TextColor = prevTextColor;
                ShowText();
            }
            else {
                this->text = text;
            }
        }

        void Show(){
            if(tft == nullptr){
                Serial.println("tft not defined");
                return;
            }
            isVisible = true;
            ShowText();
        }

        void ShowText(){
            tft->setTextColor(TextColor);
            tft->setTextSize(FontSize);
            tft->setCursor(X, Y);    
            tft->println(text);
        }

        void Hide(){
            isVisible = false;
        }
};