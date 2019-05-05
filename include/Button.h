class Button {
    private:
        Adafruit_ILI9341 *tft;
    public:    
        int X;
        int Y;
        int Width;
        int Height;

        int TextX;
        int TextY;
        int TextSize;

        uint16_t BorderColor;
        uint16_t TextColor;
        uint16_t Color;

        bool HasBorder;

        String Text;

        void (*OnClick)();

        Button(int x, int y, int width, int height, bool hasBorder){
            X = x;
            Y = y;
            Width = width;
            Height = height;
            Color = 0x0000;
            BorderColor = 0xFFFF;
            TextColor = 0xFFFF;
            HasBorder = hasBorder;
            TextX = 0;
            TextY = 0;
            TextSize = 2;
        }

        void SetTft(Adafruit_ILI9341 *tft){
            this->tft = tft;
        }

        bool CheckIfClicked(int x, int y){
            return x >= X && x <= X + Width && 
               y >= Y && y <= Y + Height;
        }

        void Execute(){
            OnClick();
        }

        void ExecuteIfClicked(int x, int y){
            if(CheckIfClicked(x, y))
                Execute();
        }

        void Show(){
            if(tft == nullptr){
                Serial.println("tft not defined");
                return;
            }

            tft->fillRect(X, Y, Width, Height, Color);
            if(HasBorder)
                tft->drawRect(X, Y, Width, Height, BorderColor);
            tft->setCursor(TextX, TextY);    
            tft->setTextColor(TextColor);
            tft->setTextSize(TextSize);
            tft->println(Text);
        }
};