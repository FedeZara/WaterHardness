extern Adafruit_ILI9341 tft;
extern URTouch ts;

class Button {
    private:
        bool isVisible = false;
        
        int textX;
        int textY;
        int fontSize;
        int textColor;
        String text;

    public:    
        int X;
        int Y;
        int Width;
        int Height;
        
        int BorderColor;
        int Color;

        bool HasBorder;

        Button(){}

        Button(int x, int y, int width, int height, bool hasBorder){
            X = x;
            Y = y;
            Width = width;
            Height = height;
            Color = 0x0000;
            BorderColor = 0xFFFF;
            HasBorder = hasBorder;
            textX = x;
            textY = y;
            textColor = ILI9341_BLACK;
            fontSize = 1;
        }

        void SetTextPos(int x, int y){
            textX = X + x;
            textY = Y + y;
        }

        void SetFontSize(int size){
            fontSize = size;
        }

        void SetTextColor(int textColor){
            this->textColor = textColor;
        }

        void SetText(String text){
            if(isVisible){
                int prevTextColor = textColor;
                textColor = Color;
                ShowText();
                this->text = text;
                textColor = prevTextColor;
                ShowText();
            }
            else{
                this->text = text;
            }
        }

        bool CheckIfClicked(int x, int y){
            return x >= X && x <= X + Width && 
               y >= Y && y <= Y + Height;
        }

        void Show(){
            isVisible = true;
            tft.fillRect(X, Y, Width, Height, Color);
            if(HasBorder)
                tft.drawRect(X, Y, Width, Height, BorderColor);
            
            ShowText();
        }

        void ShowText(){
            tft.setTextColor(textColor);
            tft.setTextSize(fontSize);
            tft.setCursor(textX, textY);    
            tft.println(text);
        }

        void Hide(){
            isVisible = false;
        }
};